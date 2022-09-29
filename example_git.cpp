#include <iostream>
#include <cmath>
#include "AudioFile.h"

using namespace std;

 //=======================================================================
 namespace examples
 {
    //void writeSineWaveToAudioFile();
    // void loadAudioFileAndPrintSummary();
    // void loadAudioFileAndProcessSamples();
    void loadAudioFileInformation();
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

    examples::loadAudioFileInformation();
        
    return 0;
}

//=======================================================================
namespace examples
{
    //=======================================================================
    void writeSineWaveToAudioFile()
    {
        //---------------------------------------------------------------
        cout << "**********************" << endl;
        cout << "Running Example: Write Sine Wave To Audio File" << endl;
        cout << "**********************" << endl << endl;
        
        //---------------------------------------------------------------
        // 1. Let's setup our AudioFile instance
        
        AudioFile<float> a;
        a.setNumChannels (2);
        a.setNumSamplesPerChannel (44100);

        //---------------------------------------------------------------
        // 2. Create some variables to help us generate a sine wave
        
        const float sampleRate = 44100.f;
        const float frequencyInHz = 440.f;
        
        //---------------------------------------------------------------
        // 3. Write the samples to the AudioFile sample buffer
        
        for (int i = 0; i < a.getNumSamplesPerChannel(); i++)
        {
            for (int channel = 0; channel < a.getNumChannels(); channel++)
            {
                a.samples[channel][i] = sin ((static_cast<float> (i) / sampleRate) * frequencyInHz * 2.f * M_PI);
                if(abs(a.samples[channel][i])>0.9995)
                    cout << "a.sample (channel, i): " << channel << ","<<i<< "|| 요소" << a.samples[channel][i] << endl;
                //식) A * sin (2 * M_PI * f * t)
                //static_cast<float> : 명시적 형식 변환 
                //f: frequencyInHz
            }
        }
        
        //---------------------------------------------------------------
        // 4. Save the AudioFile
        
        string filePath = "sine-wave.wav"; // change this to somewhere useful for you
        a.save ("audiosample/sine-wave.wav", AudioFileFormat::Wave);
    }
    
    //=======================================================================
    void loadAudioFileAndPrintSummary()
    {
        //---------------------------------------------------------------
        cout << "**********************" << endl;
        cout << "Running Example: Load Audio File and Print Summary" << endl;
        cout << "**********************" << endl << endl;
        
        //---------------------------------------------------------------
        // 1. Set a file path to an audio file on your machine
        const string filePath = "audiosample/test-audio.wav";
        
        //---------------------------------------------------------------
        // 2. Create an AudioFile object and load the audio file
        
        AudioFile<float> a;
        bool loadedOK = a.load (filePath);
        
        /** If you hit this assert then the file path above
         probably doesn't refer to a valid audio file */
        assert (loadedOK);
        
        //---------------------------------------------------------------
        // 3. Let's print out some key details
        
        cout << "Bit Depth: " << a.getBitDepth() << endl;
        cout << "Sample Rate: " << a.getSampleRate() << endl;
        cout << "Num Channels: " << a.getNumChannels() << endl;
        cout << "Length in Seconds: " << a.getLengthInSeconds() << endl;
        cout << endl;
    }
    
    //=======================================================================
    void loadAudioFileAndProcessSamples()
    {
        //---------------------------------------------------------------
        cout << "**********************" << endl;
        cout << "Running Example: Load Audio File and Process Samples" << endl;
        cout << "**********************" << endl << endl;
        
        //---------------------------------------------------------------
        // 1. Set a file path to an audio file on your machine
        const string inputFilePath = "audiosample/test-audio.wav";
        
        //---------------------------------------------------------------
        // 2. Create an AudioFile object and load the audio file
        
        AudioFile<float> a;
        bool loadedOK = a.load (inputFilePath);
        
        /** If you hit this assert then the file path above
         probably doesn't refer to a valid audio file */
        assert (loadedOK);
        
        //---------------------------------------------------------------
        // 3. Let's apply a gain to every audio sample
        
        float gain = 0.5f; //multiple the volume of the sound

        for (int i = 0; i < a.getNumSamplesPerChannel(); i++)
        {
            for(int channel=0; channel<a.getNumChannels();channel++)
            {
                cout<<"channel: " << channel << ", sample: " << i << ", data: " << a.samples[channel][i]<< endl;
            }
            // for (int channel = 0; channel < a.getNumChannels(); channel++)
            // {
            //     a.samples[channel][i] = a.samples[channel][i] * gain;
            // }
        }
        
        //---------------------------------------------------------------
        // 4. Write audio file to disk
        
        string outputFilePath = "audiosample/quieter-audio-filer.wav"; // change this to somewhere useful for you
        a.save (outputFilePath, AudioFileFormat::Aiff);
    }

    //======================================================================
    void loadAudioFileInformation()
    {
        //---------------------------------------------------------------
        cout << "**********************" << endl;
        cout << "Running Example: load Audio File Information What I need" << endl;
        cout << "**********************" << endl << endl;
        
        //---------------------------------------------------------------
        // 1. Set a file path to an audio file on your machine
        const string filePath = "audiosample/coyote.wav";
        
        //---------------------------------------------------------------
        // 2. Create an AudioFile object and load the audio file
        
        AudioFile<float> a;
        bool loadedOK = a.load (filePath);
        
        /** If you hit this assert then the file path above
         probably doesn't refer to a valid audio file */
        assert (loadedOK);
        
        //---------------------------------------------------------------
        // 3. Let's print out some key details
        
        cout << "Bit Depth: " << a.getBitDepth() << endl;
        cout << "Sample Rate: " << a.getSampleRate() << endl;
        cout << "Num Channels: " << a.getNumChannels() << endl;
        cout << "Length in Seconds: " << a.getLengthInSeconds() << endl;
        a.printSummary();
        cout<<endl<<endl;

        float maxfreq = 0.0f; 
        for(int i = 0; i < a.getNumSamplesPerChannel(); i++)
        {
            for(int channel=0; channel < a.getNumChannels(); channel++)
            {
                float freq = 0.0f;
                freq = (asin(a.samples[channel][i])*a.getSampleRate())/(2.f*M_PI*static_cast<float> (i));
                if(abs(freq)>maxfreq)
                    maxfreq = freq;
                if(abs(freq)>0.008)
                    cout << "i:" << i << ", freq: " << freq << endl;
                // if(abs(freq)>400)
                //     cout << i << ". " <<a.samples[channel][i] << "."<< " freq : " << freq << endl;
                //a.samples[channel][i] = sin ((static_cast<float> (i) / sampleRate) * frequencyInHz * 2.f * M_PI); 를 역으로 풀어서 사용.
            }
        }
        cout << "maxfreq: " << maxfreq << endl;
        cout << "|================================|" << endl; 

        // 4. Let's apply a gain to every audio sample
    
        for (int i = 0; i < a.getNumSamplesPerChannel(); i++)
        {
            // for(int channel=0; channel<a.getNumChannels();channel++)
            // {
            //     cout<<"channel: " << channel << ", sample: " << i << ", data: " << a.samples[channel][i]<< endl;
            // }
            for (int channel = 0; channel < a.getNumChannels(); channel++)
            {   
                float frequencyInHz = (asin(a.samples[channel][i])*a.getSampleRate())/(2.f*M_PI*static_cast<float> (i));
                frequencyInHz*=0.1f;
                a.samples[channel][i] = sin ((static_cast<float> (i) / a.getSampleRate()) * frequencyInHz * 2.f * M_PI);
            }
        }
        
        //---------------------------------------------------------------
        // 5. Write audio file to disk
        
        string outputFilePath = "audiosample/quieter-coyote-audio-filer.wav"; // change this to somewhere useful for you
        a.save (outputFilePath, AudioFileFormat::Aiff);

        // for (int i = 0; i < a.getNumSamplesPerChannel(); i++)
        // {
        //     for (int channel = 0; channel < a.getNumChannels(); channel++)
        //     {
        //         if(abs(a.samples[channel][i])>0.9999)
        //             cout << "a.sample (channel, i): " << channel << ","<<i<< "|| 요소" << a.samples[channel][i] << endl;
        //         float freq = 0.0f;
        //         freq = (asin(a.samples[channel][i])*a.getSampleRate())/(2.f*M_PI*static_cast<float> (i));
        //         if(abs(freq)>0.249)
        //         {
        //             cout << "freq: " << freq << endl;
        //         }

        //         //a.samples[channel][i] = a.samples[channel][i] * gain;
        //     }
        // }
    }
}
