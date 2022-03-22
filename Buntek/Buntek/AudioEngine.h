/*!*****************************************************************************
\file AudioEngine.h
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Engine of the Audio
*******************************************************************************/
#pragma warning(disable:26812)
#include <iostream>
#include <fmod.hpp>
#include <fmod_errors.h>
#include <map>
using namespace std;
using namespace FMOD;

#define AudioManager _audioManager::Instance()

class _audioManager
{
private:
    _audioManager(void);
    ~_audioManager(void);
    System* fmodSystem = NULL;
    Channel* audioClipChannel = nullptr;
    Channel* musicChannel = nullptr;
    ChannelGroup* channelGroup = nullptr;
    map<string, Sound*> soundDatabase;
    map<string, Sound*> musicDatabase;
    bool isActive = true;
    float soundVol = .5f, musicVol = .5f;
    const float  musicVolOffset = 0.1f;
    
public:
    static _audioManager& Instance(void);
    //bool succeededOrWarn(const std::string& message, FMOD_RESULT result);
    //Channel* GetMusicChannel(void);
    //void Clean(void);
    void PlayClip(string audiClip);
    void PlayMusic(string musicTrack);
    void StopMusic(void);
    void SetAudioVolume(float volume);
    float* GetAudioVolume(void);
    void SetMusicVolume(float volume);
    float* GetMusicVolume(void);
    void Update(void);
    void LoadSound(string name);
    void LoadMusic(string name);
    void UnloadSound(string name);
    void UnloadMusic(string name);
    void Free(void);
    //Sound* GetSound(string name);
};
//
//FMOD_RESULT F_CALLBACK channelGroupCallback(FMOD_CHANNELCONTROL* channelControl,
//    FMOD_CHANNELCONTROL_TYPE controlType,
//    FMOD_CHANNELCONTROL_CALLBACK_TYPE callbackType,
//    void* commandData1,
//    void* commandData2);
