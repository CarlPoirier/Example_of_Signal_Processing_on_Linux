#include <ao/ao.h>


class SoundPlayer {

    int driver;
    ao_device *dev = nullptr;
    ao_sample_format format;

public:

    SoundPlayer() {
        
        ao_initialize();
        driver = ao_default_driver_id();
        
        // set the output format
        format.bits = 16;
        format.rate = 44100;
        format.channels = 1;
        format.byte_format = AO_FMT_NATIVE;
        format.matrix = 0;
        
        // open libao output device
        if (!(dev = ao_open_live(driver, &format, NULL)))
        {
            fprintf(stderr, "Error opening ao device %d\n", driver);
        }

    }


    void Play(unsigned char* buffer, int buffer_size) {

        ao_play(dev, (char*)buffer, buffer_size);

    }    


    ~SoundPlayer() {
        
        // clean up
        ao_close(dev);
        ao_shutdown();
        
    }

};
