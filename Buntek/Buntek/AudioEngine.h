#pragma warning(disable:26812)
#include <iostream>
#include <chrono>
#include <thread>
#include <fmod.hpp>
#include <fmod_errors.h>
#include <map>
using namespace std;
using namespace FMOD;

#define AudioManager _audioManager::Instance()

class _audioManager
{
private:
    static _audioManager* instance;
    _audioManager();
    ~_audioManager();
    void SoundTest(string audiClip);
    System* fmodSystem = NULL;
    Channel* channel = nullptr;
    ChannelGroup* channelGroup = nullptr;
    map<string, Sound*> soundDatabase;
    
public:
    static _audioManager& Instance(void);
    //bool succeededOrWarn(const std::string& message, FMOD_RESULT result);
    /*FMOD_RESULT F_CALLBACK channelGroupCallback(FMOD_CHANNELCONTROL* channelControl,
        FMOD_CHANNELCONTROL_TYPE controlType, FMOD_CHANNELCONTROL_CALLBACK_TYPE callbackType,
        void* commandData1, void* commandData2);*/
    //void LoopPlaying();
    void CleanPlaying();
    void PlayAudio(string audiClip);
    void LoadSound(string name);
    Sound* GetSound(string name);
};
