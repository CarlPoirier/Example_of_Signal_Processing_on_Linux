

class SignalProcessor {

    

public:

    SignalProcessor() {
        
    }


    static void Process(int16_t* buffer, size_t sampleQty) {
        
        for (unsigned int i = 0; i < buffer_size; i++) {
            buffer[i]=buffer[i]/4;
        }

    }

    ~SignalProcessor() {
        
    }

};
