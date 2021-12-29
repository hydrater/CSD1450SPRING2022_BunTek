#pragma warning(disable:26812)
#include <iostream>
#include <chrono>
#include <thread>
#include <fmod.hpp>
#include <fmod_errors.h>
using namespace std;

bool succeededOrWarn(const std::string& message, FMOD_RESULT result)
{
    if (result != FMOD_OK) {
        std::cerr << message << ": " << result << " " << FMOD_ErrorString(result) << std::endl;
        return false;
    }
    return true;
}

FMOD_RESULT F_CALLBACK channelGroupCallback(FMOD_CHANNELCONTROL* channelControl,
    FMOD_CHANNELCONTROL_TYPE controlType, FMOD_CHANNELCONTROL_CALLBACK_TYPE callbackType,
    void* commandData1, void* commandData2)
{
    std::cout << "Callback called for " << controlType << std::endl;
    return FMOD_OK;
}

void SoundTest(FMOD::System* system, FMOD::Channel* channel, FMOD::ChannelGroup* channelGroup, FMOD::Sound* sound)
{
    FMOD_RESULT result;

    // Create the main system object.
    result = FMOD::System_Create(&system);
    if (!succeededOrWarn("FMOD: Failed to create system object", result))
        return;
    if (result != FMOD_OK)
        cout << "FMOD broke at one" << endl;

        // Initialize FMOD.
    result = system->init(512, FMOD_INIT_NORMAL, nullptr);
    if (!succeededOrWarn("FMOD: Failed to initialise system object", result))
        return;
    if (result == FMOD_OK)
        cout << "yes" << endl;

        // Create the channel group.
    result = system->createChannelGroup("inGameSoundEffects", &channelGroup);
    if (!succeededOrWarn("FMOD: Failed to create in-game sound effects channel group", result))
        return;

        // Create the sound.
    //system->createSound("./Resources/Art/Test.wav", FMOD_DEFAULT, nullptr, &sound);
    system->createSound("./Assets/Test.wav", FMOD_DEFAULT, nullptr, &sound);

    // Play the sound.
    result = system->playSound(sound, nullptr, false, &channel);
    if (result == FMOD_OK)
        cout << "yes" << endl;

    if (!succeededOrWarn("FMOD: Failed to play sound", result))
        return;

        // Assign the channel to the group.
    result = channel->setChannelGroup(channelGroup);
    if (!succeededOrWarn("FMOD: Failed to set channel group on", result))
        return;

        // Set a callback on the channel.
        channel->setCallback(&channelGroupCallback);
        if (!succeededOrWarn("FMOD: Failed to set callback for sound", result))
            return;
}

void LoopPlaying(bool* isPlaying, FMOD::System* system, FMOD::Channel* channel)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    FMOD_RESULT result = system->update();
}

void CleanPlaying(FMOD::System* system, FMOD::ChannelGroup* channelGroup, FMOD::Sound* sound)
{
    // Clean up.
    sound->release();
    channelGroup->release();
    system->release();
}