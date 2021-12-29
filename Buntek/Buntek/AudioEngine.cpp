#include "AudioEngine.h"
_audioManager* _audioManager::instance = 0;

_audioManager::_audioManager()
{
    // Create the main system object.
    System_Create(&fmodSystem);

    // Initialize FMOD.
    fmodSystem->init(512, FMOD_INIT_NORMAL, nullptr);

    // Create the channel group.
    fmodSystem->createChannelGroup("inGameSoundEffects", &channelGroup);
}

_audioManager::~_audioManager()
{
}

void _audioManager::SoundTest(bool lmao)
{
    FMOD_RESULT result;

    // Create the sound.
    if (lmao)
        fmodSystem->createSound("./Assets/splash.mp3", FMOD_DEFAULT, nullptr, &sound);
    else
        fmodSystem->createSound("./Assets/Test.wav", FMOD_DEFAULT, nullptr, &sound);

    // Play the sound.
    result = fmodSystem->playSound(sound, nullptr, false, &channel);
    if (result == FMOD_OK)
        cout << "yes" << endl;

    // Assign the channel to the group.
    result = channel->setChannelGroup(channelGroup);
    /*if (!succeededOrWarn("FMOD: Failed to set channel group on", result))
        return;*/

    // Set a callback on the channel.
    /*channel->setCallback(&channelGroupCallback);
    if (!succeededOrWarn("FMOD: Failed to set callback for sound", result))
        return;*/
}

void _audioManager::LoopPlaying()
{
    //std::this_thread::sleep_for(std::chrono::milliseconds(10));

    fmodSystem->update();
}

void _audioManager::CleanPlaying()
{
    // Clean up.
    sound->release();
    channelGroup->release();
    fmodSystem->release();
}

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
    if (instance != 0)
    {
        return *instance;
    }
    instance = new _audioManager();
    return *instance;
}