#include <iostream>
#include <cmath>
#include "AudioFile.h"
#include <ctime>
#include <list>
#include <functional>

using namespace std;

 //=======================================================================
 namespace examples
 {
    void loadAudioFiltering();
    void writingFile(list<float> valueList, int sampleRate, double lengthTime, int count);
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
        //1. Set a file path to an audio file on your machine 
        const string filePath = "audiosample/coyote.wav";

        //2. Create An AudioFile Object and load the Audio file
        AudioFile<float> origin;
        bool loadedOK = origin.load(filePath);

        //if you hit this assert then the file path above probably doesn't refer to a valie audio file
        assert(loadedOK);

        //3. Print some details
        origin.printSummary();
        
        //4. Function 
        /*
            1) origin에서 freq추출하면서, freq가 범위에 들어가는지 확인
            2) freq가 범위에 속하면, extractList에 해당 값들 추출 & 추출하기 시작했다는 신호 보내기 
            3) freq가 범위를 벗어나는 순간, 새로운 AudioFIle<float> 에 값들 저장하여 wav파일로 추출 
        */
       
        float maxfreq = 0.0f;
        bool recording = false;
        clock_t startTime, finishTime;
        double lengthTime;
        list<float> recordList;
        int count = 0;
        for(int i = 0; i<origin.getNumSamplesPerChannel();i++)
        {
                for(int channel=0; channel < origin.getNumChannels(); channel++){
                    float freq = 0.0f;
                    freq = (asin(origin.samples[channel][i])*origin.getSampleRate())/(2.f*M_PI*static_cast<float> (i));
                    //origin.samples[channel][i] = sin ((static_cast<float> (i) / sampleRate) * frequencyInHz * 2.f * M_PI); 를 역으로 풀어서 사용.
                    if(abs(freq)>maxfreq)
                        maxfreq = freq;
                    //cout << "freq : " << freq << endl;
                    
                    if(abs(freq)>0.003&& !recording) //시작할 때,
                    {
                        recording = true;
                        startTime = clock();
                        recordList.clear();
                    }
                    if(recording) 
                    {
                        if(abs(freq)>0.003)//도중 - 값 넣기 
                        {
                            cout << "recording ... freq: " << abs(freq) << endl;
                            recordList.push_back(origin.samples[channel][i]);
                        }
                        else{ //끝 - wav파일 추출 메소드 돌리기 
                            recording = false;
                            finishTime = clock();
                            lengthTime = (double) (finishTime-startTime)/CLOCKS_PER_SEC;
                            cout << "finish. length time : " << (double)lengthTime << endl;
                            examples::writingFile(recordList, origin.getSampleRate(), lengthTime, count);
                            recordList.clear();
                            count++;
                        }
                    }
                    
                }
        }
        string path = "audiosample/copy_coyote.wav";
        origin.save(path, AudioFileFormat::Wave);
    }
    
    void writingFile(list<float> valueList, int sampleRate, double lengthTime, int count){
        cout << "|========== Writing File ==========|" << endl;
        list<float>::iterator iter;
        AudioFile<float> filteredAudio;
        filteredAudio.setNumChannels(2);
        filteredAudio.setNumSamplesPerChannel((int)(sampleRate*lengthTime));
        int i =0;
        for(iter = valueList.begin(); iter!=valueList.end();iter++)
        {
            cout << "value of iter: " << *iter << endl;
            if(i%2==0)
                filteredAudio.samples[0][i/2] = *iter;
            else
                filteredAudio.samples[1][i/2] = *iter;
            i++;
        }
        string newFilePath = "audiosample/extract_"+ to_string(count) +".wav";
        filteredAudio.save(newFilePath, AudioFileFormat::Aiff);
        cout << "|==================================|"<< endl;
    }
}
