#include <pulse/simple.h>
#include <pulse/error.h>
#include <iostream>

class MicRecorder {

    int error;
    pa_simple *s;

public:

    MicRecorder() : error(0), s(nullptr) {
        
        // The sample type to use
        static const pa_sample_spec ss = {
            .format = PA_SAMPLE_S16LE,
            .rate = 44100,
            .channels = 1
        };
        
        // Create the recording stream
        if (!(s = pa_simple_new(NULL, "SigProc", PA_STREAM_RECORD, NULL, "record", &ss, NULL, NULL, &error))) {
            std::cerr << ": pa_simple_new() failed: " << pa_strerror(error) << std::endl;
        }
        
    }


    void Record(unsigned char* buffer, int buffer_size) {

        // Record some data
        if (pa_simple_read(s, buffer, buffer_size, &error) < 0) {
            std::cerr << ": pa_simple_read() failed: " << pa_strerror(error) << std::endl;
        }

    }    


    ~MicRecorder() {
        pa_simple_free(s);
    }

};
