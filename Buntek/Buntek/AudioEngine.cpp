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

    //Load sounds here
    LoadSound("Test.wav");
    LoadSound("splash.mp3");
}

_audioManager::~_audioManager()
{
}

void _audioManager::PlayAudio(string clipName)
{
    FMOD_RESULT result;

    // Create the sound.
    Sound* audioClip;
    auto search = soundDatabase.find(clipName);
    if (search != soundDatabase.end())
    {
        audioClip = search->second;
    }

	fmodSystem->createSound("./Assets/Test.wav", FMOD_DEFAULT, nullptr, &audioClip);

    // Play the sound.
    result = fmodSystem->playSound(audioClip, nullptr, false, &channel);
    if (result == FMOD_OK)
    //    cout << "yes" << endl;

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
    map<string, Sound*>::iterator start;
    for (start = soundDatabase.begin(); start != soundDatabase.end(); start++)
        start->second->release();
    channelGroup->release();
    fmodSystem->release();
}

void _audioManager::LoadSound(string name)
{
    string pathString = "./Assets/" + name;
    char* pathName = new char[pathString.length() + 1];
    copy(pathString.begin(), pathString.end(), pathName);
    Sound* sound;
    fmodSystem->createSound(pathName, FMOD_DEFAULT, nullptr, &sound);
    cout << sound << endl;
    soundDatabase[name] = sound;
}

Sound* _audioManager::GetSound(string name)
{
    auto search = soundDatabase.find(name);
    if (search != soundDatabase.end())
    {
        return search->second;
    }
    return NULL;
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