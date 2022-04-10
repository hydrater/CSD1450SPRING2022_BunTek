/*!*****************************************************************************
\file AudioEngine.cpp
\project Beyond Aurorean Skies
\author: Algene Tan Chuan Hong (90%)
\co-authors: Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Bryan Boh Tai Hong (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Engine of the Audio
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*******************************************************************************/
#include "AudioEngine.h"
#include "SaveManager.h"

_audioManager::_audioManager(void)
{
    // Create the main system object.
    System_Create(&fmodSystem);

    // Initialize FMOD.
    fmodSystem->init(512, FMOD_INIT_NORMAL, nullptr);

    // Create the channel group.
    fmodSystem->createChannelGroup("inGameSoundEffects", &channelGroup);

    audioClipChannel->setChannelGroup(channelGroup);
    musicChannel->setChannelGroup(channelGroup);

    // Set a callback on the channel.
    /*musicChannel->setCallback(&channelGroupCallback);
    audioChannel->setCallback(&channelGroupCallback);*/
}

_audioManager::~_audioManager(void)
{
}

void _audioManager::PlayClip(string clipName)
{
    // Create the sound.
    Sound* audioClip = 0;
    auto search = soundDatabase.find(clipName);
    if (search != soundDatabase.end())
        audioClip = search->second;

    // Play the sound.
    fmodSystem->playSound(audioClip, channelGroup, true, &audioClipChannel);
    audioClipChannel->setVolume(soundVol*soundVolMultiplier);
    audioClipChannel->setPaused(false);
}

void _audioManager::PlayMusic(string musicTrack)
{
    // Create the sound.
    Sound* audioClip = 0;
    auto search = musicDatabase.find(musicTrack);
    if (search != musicDatabase.end())
        audioClip = search->second;

    // Play the music.
    musicChannel->stop();
    FMOD_RESULT result;
    result = fmodSystem->playSound(audioClip, channelGroup, false, &musicChannel);
    musicChannel->setVolume(musicVol * musicVolMultiplier);
    //musicChannel->setPaused(false);
}

void _audioManager::StopMusic()
{
    // Play the sound.
    musicChannel->stop();
}

void _audioManager::PauseMusic(bool playMusic)
{
    if (playMusic == true)
    {
        musicChannel->setPaused(true);
    }
    else
    {
        musicChannel->setPaused(false);
    }
}

void _audioManager::SetAudioVolume(float volume)
{
    soundVol = volume;
    SaveManager.SaveData();
}

float* _audioManager::GetAudioVolume(void)
{
    return &soundVol;
}

void _audioManager::SetMusicVolume(float volume)
{
    musicVol = volume;
    musicChannel->setVolume(volume * musicVolMultiplier);
    SaveManager.SaveData();
}

float* _audioManager::GetMusicVolume(void)
{
    return &musicVol;
}

void _audioManager::Update()
{
    fmodSystem->update();
}

//void _audioManager::Clean()
//{
//    // Clean up.
//    map<string, Sound*>::iterator start;
//    for (start = soundDatabase.begin(); start != soundDatabase.end(); start++)
//        start->second->release();
//
//    for (start = musicDatabase.begin(); start != musicDatabase.end(); start++)
//        start->second->release();
//    //channelGroup->release();
//    fmodSystem->release();
//}

void _audioManager::LoadSound(string name)
{
    if (soundDatabase.count(name))
        return;

    string pathString = "./Assets/Sound/" + name + '\0';
    char* pathName = new char[pathString.length()];
    copy(pathString.begin(), pathString.end(), pathName);
    Sound* sound = 0;
    fmodSystem->createSound(pathName, FMOD_DEFAULT, nullptr, &sound);
    soundDatabase[name] = sound;
    delete[] pathName;
}

void _audioManager::LoadMusic(string name)
{
    if (musicDatabase.count(name))
        return;

    string pathString = "./Assets/Music/" + name + '\0';
    char* pathName = new char[pathString.length()];
    copy(pathString.begin(), pathString.end(), pathName);
    Sound* music = 0;
    fmodSystem->createSound(pathName, FMOD_LOOP_NORMAL, nullptr, &music);
    musicDatabase[name] = music;
    delete[] pathName;
}

void _audioManager::UnloadSound(string name)
{
    if (isActive && soundDatabase.find(name) != soundDatabase.end())
        soundDatabase[name]->release();
    soundDatabase.erase(name);
}

void _audioManager::UnloadMusic(string name)
{
    if (isActive && musicDatabase.find(name) != musicDatabase.end())
        musicDatabase[name]->release();
    musicDatabase.erase(name);
}

void _audioManager::Free(void)
{
    fmodSystem->release();
    isActive = false;
}

//Sound* _audioManager::GetSound(string name)
//{
//    auto search = soundDatabase.find(name);
//    if (search != soundDatabase.end())
//        return search->second;
//    return NULL;
//}

//bool _audioManager::succeededOrWarn(const std::string& message, FMOD_RESULT result)
//{
//    if (result != FMOD_OK) {
//        std::cerr << message << ": " << result << " " << FMOD_ErrorString(result) << std::endl;
//        return false;
//    }
//    return true;
//}

_audioManager& _audioManager::Instance(void)
{
    static _audioManager instance;
    return instance;
}

//Channel* _audioManager::GetMusicChannel(void)
//{
//    return musicChannel;
//}

//FMOD_RESULT F_CALLBACK channelGroupCallback(FMOD_CHANNELCONTROL* channelControl,
//    FMOD_CHANNELCONTROL_TYPE controlType, FMOD_CHANNELCONTROL_CALLBACK_TYPE callbackType,
//    void* commandData1, void* commandData2)
//{
//    if (controlType == FMOD_CHANNELCONTROL_CHANNEL 
//        && AudioManager.GetMusicChannel() == (Channel*)channelControl 
//        && callbackType == FMOD_CHANNELCONTROL_CALLBACK_END)
//    {
//        // music ended
//    }
//
//    return FMOD_OK;
//}
