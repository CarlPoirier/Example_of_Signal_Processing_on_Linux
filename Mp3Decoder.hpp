#include <mpg123.h>

#include <string>

#define BITS 8
#define VORBIS_TAG_LEN 30
#define VORBIS_YEAR_LEN 4

#include <iostream>

using namespace std;


struct Mp3Format {
    int channels, encoding;
    long rate;
};


class Mp3Decoder {

    mpg123_handle *mh;
    int err;

public:

    Mp3Decoder() {

        mpg123_init();
        mh = mpg123_new(NULL, &err);
        mpg123_outblock(mh);
    }


    Mp3Format Open(string& file) {
        
        Mp3Format mp3Format;
        
        unsigned periodPosition = file.rfind(".");
        string fileExtension = file.substr(periodPosition, string::npos);

        // ----- PLAY MP3 ------
        if (fileExtension.compare(".mp3") == 0) {
            /* open the file and get the decoding format */
            mpg123_open(mh, file.c_str());
            mpg123_getformat(mh, &mp3Format.rate, &mp3Format.channels, &mp3Format.encoding);            

        }

        return mp3Format;
    }
    
    
    int Decode(unsigned char* buffer, unsigned int buffer_size) {
        size_t samplesQty;
        int mpg123Error = mpg123_read(mh, buffer, buffer_size, &samplesQty);
        return samplesQty > 0 ? samplesQty : mpg123Error;
    }
    
    
    void Close() {
        mpg123_close(mh);
    }
    

    ~Mp3Decoder() {
        // clean up
        mpg123_delete(mh);
        mpg123_exit();

    }

};
