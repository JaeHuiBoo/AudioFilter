#include <iostream>
#include <cmath>
#include "AudioFile.h"

using namespace std;

 //=======================================================================
 namespace examples
 {
    void loadAudioFiltering();
 }

//=======================================================================
int main()
{
    // //---------------------------------------------------------------
    // /** Writes a sine wave to an audio file */
    //examples::writeSineWaveToAudioFile();
    
    // //---------------------------------------------------------------
    // /** Loads an audio file and prints key details to the console*/
    // examples::loadAudioFileAndPrintSummary();
    
    // //---------------------------------------------------------------
    // /** Loads an audio file and processess the samples */
    // examples::loadAudioFileAndProcessSamples();
    examples::loadAudioFiltering();
            
    return 0;
}

//=======================================================================
namespace examples
{
    void loadAudioFiltering(){
        //1. set a file path to an audio file on your machine
        const string filePath = "audiosample/coyote.wav";

        //2. create an AudioFile object and load the audio file
        AudioFile<float> a;
        bool loadedOK = a.load (filePath);

        /*
        If you hit this assert, then the file path above
        probably doesn't refer to a valid audio file*/
        assert (loadedOK);

        //3. Let's print out some key details
        cout << "|=========================================================|" << endl;
        cout << "Bit Depth: " << a.getBitDepth() << endl;
        cout << "Length in Seconds: " << a.getLengthInSeconds() << endl;
        cout << "Num Channels: " << a.getNumChannels() << endl;
        cout << "Num Samples per Channel: " << a.getNumSamplesPerChannel() << endl;
        cout << "Sample Rate: " << a.getSampleRate() << endl;
        cout << "|=========================================================|" << endl;
        cout << "print summary" << endl;
        a.printSummary();
        cout << endl;

        float maxfreq = 0.0f;
        float maxvalue = 0.0f;
        for(int i = 0; i < a.getNumSamplesPerChannel(); i++)
        {
            for(int channel=0; channel < a.getNumChannels(); channel++)
            {
                float freq = 0.0f;
                freq = (asin(a.samples[channel][i])*a.getSampleRate())/(2.f*M_PI*static_cast<float> (i));
                //a.samples[channel][i] = sin ((static_cast<float> (i) / sampleRate) * frequencyInHz * 2.f * M_PI); 를 역으로 풀어서 사용.
                if(abs(freq)>maxfreq)
                    maxfreq=freq;
                /* freq가 범위내에 있으면 출력하도록. 범위는 엑셀파일 참고해서 짤 것. 
                    if(abs(freq)>_____)
                        ~~~
                */
            }
        }
        cout << "maxfreq: " << maxfreq << endl;
        cout << "|=========================================================|" << endl;
        
        //4. Write audio file to disk
        string outputFilePath = "audiosample/writingFile.wav";
        a.save(outputFilePath, AudioFileFormat::Aiff);
    }
}
