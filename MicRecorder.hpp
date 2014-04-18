#include <pulse/simple.h>
#include <pulse/error.h>


class MicRecorder {

    int error;
    pa_simple *s;

public:

    MicRecorder() : error(0), s(nullptr) {
        
        // The sample type to use
        static const pa_sample_spec ss = {
            .format = PA_SAMPLE_S16LE,
            .rate = 44100,
            .channels = 2
        };
        
        // Create the recording stream
        if (!(s = pa_simple_new(NULL, "SigProc", PA_STREAM_RECORD, NULL, "record", &ss, NULL, NULL, &error))) {
            fprintf(stderr, __FILE__": pa_simple_new() failed: %s\n", pa_strerror(error));
        }
        
    }


    void Record(int16_t* buffer, int buffer_size) {

        // Record some data
        if (pa_simple_read(s, buffer, buffer_size, &error) < 0) {
            fprintf(stderr, __FILE__": pa_simple_read() failed: %s\n", pa_strerror(error));
        }

    }    


    ~MicRecorder() {
        pa_simple_free(s);
    }

};
