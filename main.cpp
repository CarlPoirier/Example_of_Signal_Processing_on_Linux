#include <string>
#include <initializer_list>
#include <fstream>
#include <iostream>

#include "MicRecorder.hpp"
#include "SignalProcessor.hpp"
#include "SoundPlayer.hpp"
#include "Mp3Decoder.hpp"


#define BUFSIZE 1024


// Function to print any number of buffers to file
void printToFile(int samplesQty, std::initializer_list<int16_t*> buffers)
{
//    //int len = sizeof...(tail);
//    unsigned char *vals[] = {buffers...};
//    
//    for (unsigned int i = 0; i < 5; i++) {
//
//        for ( unsigned int j = 0; j < 2; j++ ) {
//            //std::cout << vals[i][j] << " ";
//        }
//        std::cout << std::endl;
//
//    }
    
    std::ofstream myfile;
    myfile.open ("data.txt");
    
    // Output to file
    for (unsigned int i = 0; i < samplesQty; i++) {

        for ( auto buffer: buffers ) {
            myfile << buffer[i] << " ";
        }
        myfile << std::endl;

    }
    
    myfile.close();
}


int main() {
    
    SoundPlayer soundPlayer = SoundPlayer();
    Mp3Decoder mp3Decoder = Mp3Decoder();
    MicRecorder micRecorder = MicRecorder();
    
    unsigned char buffer[BUFSIZE*50] = {};
    unsigned char recBuffer[BUFSIZE*50] = {};
    
    // Put path to file here
    std::string path = "smw_coin.mp3";
    // TODO: Manage more than int16_t encoding format, mono and 44.1kHz
    Mp3Format mp3Format = mp3Decoder.Open(path);
    //std::cout << "encoding: " << mp3Format.encoding << std::endl;
    //std::cout << "channels: " << mp3Format.channels << std::endl;
    //std::cout << "rate: " << mp3Format.rate << std::endl;

    int decodeNumber = 0;

    int decodedQty = 0;
    while ((decodedQty = mp3Decoder.Decode(buffer+decodeNumber*BUFSIZE, BUFSIZE)) > 0) {      

        soundPlayer.Play(buffer+decodeNumber*BUFSIZE, decodedQty);

        // Record some data in the buffer
        micRecorder.Record(recBuffer+decodeNumber*BUFSIZE, decodedQty);   

        decodeNumber++;
    }
    unsigned int samplesQty = (decodeNumber-1)*BUFSIZE/sizeof(int16_t)+decodedQty;
    
    mp3Decoder.Close();

    // Process the signals as wanted here
    int delay = SignalProcessor::GetDelay((int16_t*)buffer, (int16_t*)recBuffer, samplesQty);
    SignalProcessor::Delay((int16_t*)buffer, samplesQty, delay);
    SignalProcessor::Scale((int16_t*)buffer, samplesQty, 1, 2);
    SignalProcessor::Subtract((int16_t*)recBuffer, (int16_t*)buffer, samplesQty);

    // Play back for more fun
    for (unsigned int i = 0; i < decodeNumber; i++) {      

        soundPlayer.Play(recBuffer+i*BUFSIZE, BUFSIZE);

    }

    printToFile(samplesQty, {(int16_t*)buffer, (int16_t*)recBuffer});
    
}