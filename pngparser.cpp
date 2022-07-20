#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//
// https://en.wikipedia.org/wiki/Portable_Network_Graphics
//

struct PngChunkStart
{
    uint32_t Length;
    uint32_t Type;
};

struct PngChunk : PngChunkStart
{
    vector<uint8_t> data;
    uint32_t crc;
};

struct IhdrChunkBody
{
    uint32_t width;
    uint32_t height;
    uint8_t bit_depth;
    uint8_t color_type;
    uint8_t compression_method;
    uint8_t filter_method;
    uint8_t interlace_method;
};

uint32_t swap_bytes(uint32_t word)
{
    union __dword__
    {
        uint32_t w;
        uint8_t b[4];
    } t;

    t.w = word;
    return (t.b[0] << 24) | (t.b[1] << 16) | (t.b[2] << 8) | t.b[3];
}

inline const char *interlace(uint8_t method)
{
    if (0 == method) return "no interlace";
    else if (1 == method) return "Adam7";
    return "?";
}

void show_ihdr_chunk(uint8_t *data)
{
    IhdrChunkBody *body = reinterpret_cast<IhdrChunkBody*>(data);

   cout << "      width : " << swap_bytes(body->width) << endl;
   cout << "      height: " << swap_bytes(body->height) << endl;
   cout << "      depth : " << (int)body->bit_depth << endl;
   cout << "      color : " << (int)body->color_type << endl;
   cout << "      compr : " << (int)body->compression_method << endl;
   cout << "      filter: " << (int)body->filter_method << endl;
   cout << "      interl: " << interlace(body->interlace_method) << endl;
}

int main(int argc, char **argv)
{
    fstream ipng;
    if (argc > 1)
    {
        ipng.open(argv[1], ios_base::in | ios_base::binary);
        if (!ipng.is_open())
        {
            cerr << "Failed opening file '" << argv[1] << "'" << endl;
            return -1;
        }
    }

    // Creates a vector with 8 bytes
    vector<uint8_t> hdr(8);

    // Reads from file at the buffer of vector 'hdr'
    ipng.read(reinterpret_cast<char*>(hdr.data()), 8);

    cout << "HDR:";
    for (auto i = hdr.begin(); i != hdr.end(); ++i)
    {
        cout << " " << static_cast<int>(*i);
    }
    cout << endl;

    PngChunk chunk;

    while (ipng.good())
    {
        ipng.read(reinterpret_cast<char*>(&chunk), sizeof(PngChunkStart));
        chunk.Type = swap_bytes(chunk.Type);
        chunk.Length = swap_bytes(chunk.Length);

        if (chunk.data.size() < chunk.Length)
        {
            // Will only increase the size of 'data' as necessary
            chunk.data.resize(chunk.Length);
        }

        ipng.read(reinterpret_cast<char*>(chunk.data.data()), chunk.Length);
        ipng.read(reinterpret_cast<char*>(&chunk.crc), sizeof(PngChunk::crc));
        chunk.crc = swap_bytes(chunk.crc);

        char type[5] = { (char)(chunk.Type >> 24),
                         (char)((chunk.Type >> 16) & 0xff),
                         (char)((chunk.Type >> 8) & 0xff),
                         (char)(chunk.Type & 0xff),
                         '\0' };

        cout << endl;
        cout << "Chunk type  : " << type << endl;
        cout << "      lenght: " << chunk.Length << endl;

        if (chunk.Type == 0x49484452 /* IHDR */)
        {
            show_ihdr_chunk(chunk.data.data());
        }
        else if (chunk.Type == 0x67414d41 /* gAMA */)
        {
            uint32_t gamma = swap_bytes(*reinterpret_cast<uint32_t*>(chunk.data.data()));
            cout << "      gamma : " << (float)(gamma) / 100000.f << endl;
        }
        else if (chunk.Type == 0x74455874 /* tEXt */)
        {
            string text(reinterpret_cast<char*>(chunk.data.data()), chunk.Length);
            cout << "      data  : " << text << endl;
        }
        else if (chunk.Type == 0x49454e44 /* IEND */)
        {
            // Found the end of image
            break;
        }
        else
        {
            cout << "      data  :";

            int i;
            for (i = 0; i < 4 && i < chunk.Length; i++)
            {
                cout << " ";
                cout.width(2);
                cout.fill('0');
                cout << hex << (int)chunk.data[i];
            }
            if (i < chunk.Length)
            {
                cout << " ...";
            }
            cout << endl;
        }

        cout << hex << "      crc   : " << chunk.crc << endl;

        // Go back to decimal mode
        cout << dec;
    }

    ipng.close();

    return 0;
}
