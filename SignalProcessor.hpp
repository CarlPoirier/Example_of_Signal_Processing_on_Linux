

class SignalProcessor {


public:

    SignalProcessor() {
        
    }
    
    
    // Find out delay between two signals using cross-correlation
    // We assume delay is positive
    static int GetDelay(int16_t* buffer1, int16_t* buffer2, size_t samplesQty) {
        
        long long* correlation = new long long[samplesQty]();
        
        for (unsigned int i = 0; i < samplesQty; i++) {
            
            for (unsigned int j = 0; j < samplesQty; j++) {
                
                //std::cout << buffer1[j] << " ";
                correlation[i] += buffer1[j] * buffer2[(i+j < samplesQty)*(i+j)];
            
            }
            
        }
        
        // Find correlation peak
        unsigned int peak = 0;
        long long maxValue = 0;
        for (unsigned int i = 0; i < samplesQty; i++) {
            
            if (correlation[i] > maxValue) {
                maxValue = correlation[i];
                peak = i;
            }
            
        }
                
        delete[] correlation;
        
        return peak;

    }
    
    
    // We assume delay is positive
    static void Delay(int16_t* buffer, unsigned int samplesQty, int delay) {
        
        for (int i = samplesQty-1; i >= 0; i--) {
            
            buffer[i] = (i-delay >= 0)*buffer[(i-delay)];
            
        }

    }
    
    
    // Scale a signal using integer math, with numerator and denumerator of scale
    static void Scale(int16_t* buffer, size_t samplesQty, int num, int denum) {
        
        for (int i = 0; i < samplesQty; i++) {
            
            buffer[i] = buffer[i]*num/denum;
            
        }

    }
    
    
    // Subtract buffer 2 from buffer 1
    static void Subtract(int16_t* buffer1, int16_t* buffer2, size_t samplesQty) {
        
        for (int i = 0; i < samplesQty; i++) {
            
            buffer1[i] -= buffer2[i];
            
        }

    }
    

    ~SignalProcessor() {
        
    }

};
