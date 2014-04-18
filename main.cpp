#include "MicRecorder.hpp"
#include "SignalProcessor.hpp"
#include "SoundPlayer.hpp"


#define BUFSIZE 1024


int main() {
    
    SoundPlayer soundPlayer = SoundPlayer();
    MicRecorder micRecorder = MicRecorder();
    
    for (unsigned int i=0; i<100; i++) {
        int16_t buf[BUFSIZE];
        
        // Record some data in the buffer
        micRecorder.Record(buf, sizeof(buf));

        // Process the data
        SignalProcessor::Process(buf, BUFSIZE);
        
        // Play it back
        soundPlayer.Play(buf, sizeof(buf));
    }

}