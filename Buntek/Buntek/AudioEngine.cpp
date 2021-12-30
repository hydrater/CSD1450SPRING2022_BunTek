#include "AudioEngine.h"
_audioManager* _audioManager::instance = 0;

_audioManager::_audioManager()
{
    // Create the main system object.
    System_Create(&fmodSystem);

    // Initialize FMOD.
    fmodSystem->init(512, FMOD_INIT_NORMAL, nullptr);

    // Create the channel group.
    //fmodSystem->createChannelGroup("inGameSoundEffects", &channelGroup);

    // Load sounds here
    LoadSound("splash.mp3");

    // Load Music here
    LoadMusic("Test.wav");
}

_audioManager::~_audioManager()
{
}

void _audioManager::PlayAudio(string clipName)
{
    // Create the sound.
    Sound* audioClip = 0;
    auto search = soundDatabase.find(clipName);
    if (search != soundDatabase.end())
        audioClip = search->second;

    // Play the sound.
    fmodSystem->playSound(audioClip, nullptr, false, &channel);

    // Assign the channel to the group.
    //channel->setChannelGroup(channelGroup);

	// Set a callback on the channel.
	//channel->setCallback(&channelGroupCallback);
}

void _audioManager::PlayMusic(string musicTrack)
{
    // Create the sound.
    Sound* audioClip = 0;
    auto search = musicDatabase.find(musicTrack);
    if (search != musicDatabase.end())
        audioClip = search->second;

    // Play the sound.
    musicChannel->stop();
    fmodSystem->playSound(audioClip, nullptr, false, &musicChannel);
}

//https://documentation.help/FMOD-Studio-API/FMOD_System_Update.html
//void _audioManager::LoopPlaying()
//{
//    //std::this_thread::sleep_for(std::chrono::milliseconds(10));
//
//    fmodSystem->update();
//}

void _audioManager::CleanPlaying()
{
    // Clean up.
    map<string, Sound*>::iterator start;
    for (start = soundDatabase.begin(); start != soundDatabase.end(); start++)
        start->second->release();

    for (start = musicDatabase.begin(); start != musicDatabase.end(); start++)
        start->second->release();
    //channelGroup->release();
    fmodSystem->release();
}

void _audioManager::LoadSound(string name)
{
    string pathString = "./Assets/" + name + '\0';
    char* pathName = new char[pathString.length() + 1];
    copy(pathString.begin(), pathString.end(), pathName);
    Sound* sound = 0;
    fmodSystem->createSound(pathName, FMOD_DEFAULT, nullptr, &sound);
    soundDatabase[name] = sound;
}

void _audioManager::LoadMusic(string name)
{
    string pathString = "./Assets/" + name + '\0';
    char* pathName = new char[pathString.length() + 1];
    copy(pathString.begin(), pathString.end(), pathName);
    Sound* music = 0;
    fmodSystem->createSound(pathName, FMOD_LOOP_NORMAL, nullptr, &music);
    musicDatabase[name] = music;
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
        return *instance;
    instance = new _audioManager();
    return *instance;
}