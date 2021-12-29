#pragma warning(disable:26812)
#include <iostream>
#include <chrono>
#include <thread>
#include <fmod.hpp>
#include <fmod_errors.h>
using namespace std;
using namespace FMOD;

#define AudioManager _audioManager::Instance()

class _audioManager
{
private:
    static _audioManager* instance;
    _audioManager();
    ~_audioManager();
    System* fmodSystem = NULL;
    Channel* channel = nullptr;
    ChannelGroup* channelGroup = nullptr;
    Sound* sound = nullptr;
    
public:
    static _audioManager& Instance(void);
    //bool succeededOrWarn(const std::string& message, FMOD_RESULT result);
    /*FMOD_RESULT F_CALLBACK channelGroupCallback(FMOD_CHANNELCONTROL* channelControl,
        FMOD_CHANNELCONTROL_TYPE controlType, FMOD_CHANNELCONTROL_CALLBACK_TYPE callbackType,
        void* commandData1, void* commandData2);*/
    void SoundTest(bool lmao);
    void LoopPlaying();
    void CleanPlaying();
};
