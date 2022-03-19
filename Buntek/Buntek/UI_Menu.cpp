#include "UI_Menu.h"
#include "Devtools.h"
#include "Slider.h"
#include "Button.h"
#include "AudioEngine.h"
#include "GameManager.h"
void CloseOptionMenu(Button* button);
void FullScreen(Button* button);
void MusicSlider(Slider* button);
void SoundSlider(Slider* button);


UI_OptionMenu::UI_OptionMenu(void)
{
}

UI_OptionMenu::~UI_OptionMenu(void)
{
}

void UI_OptionMenu::CreateOptionMenu(short sortingLayer) {
    GameObject* OptionMenu = this->Owner();

    // Background
    tempBckgrnd = devTools.CreateSpriteGameObject("Background.jpg", (float)AEGetWindowWidth(), (float)AEGetWindowHeight(), AE_GFX_BM_BLEND, Vector2(0.f, 0.f), (short)(sortingLayer), 1.f);
    OptionMenu->AddChild(tempBckgrnd);

    Header = devTools.CreateSpriteGameObject("WhiteTexture.png", 200, 100, AE_GFX_BM_BLEND, Vector2(0.f, 400.f), (short)(sortingLayer + 1));
    TextRenderer* tempHeadertxtRenderer = devTools.AddTextToSpriteGameObject(Header, "Gabriola.ttf", "Options", TextRenderer::xAlignmentTypes::Mid, TextRenderer::yAlignmentTypes::Mid, 48.f, (short)(sortingLayer)+2);
    tempHeadertxtRenderer->SetTextColor(0, 0, 0);
    OptionMenu->AddChild(Header);

    musicSliderHeader = devTools.CreateSpriteGameObject("WhiteTexture.png", 100, 40, AE_GFX_BM_BLEND, Vector2(0.f, 250.f), (short)(sortingLayer + 1));
    TextRenderer* tempmusicSliderHeaderRenderer = devTools.AddTextToSpriteGameObject(musicSliderHeader, "Gabriola.ttf", "Music", TextRenderer::xAlignmentTypes::Mid, TextRenderer::yAlignmentTypes::Mid, 24.f, (short)(sortingLayer)+2);
    tempmusicSliderHeaderRenderer->SetTextColor(0, 0, 0);
    OptionMenu->AddChild(musicSliderHeader);

    musicSlider = new GameObject();
    musicSlider->transform->SetPosition(Vector2(0.f,200.f));
    musicSlider->AddComponent<Slider>()->GenerateSlider(*AudioManager.GetMusicVolume(), sortingLayer + 1, 1.0f);
    musicSlider->GetComponent<Slider>()->SliderEffect = &MusicSlider;
    OptionMenu->AddChild(musicSlider);

    soundSliderHeader = devTools.CreateSpriteGameObject("WhiteTexture.png", 100, 40, AE_GFX_BM_BLEND, Vector2(0.f, 100.f), (short)(sortingLayer + 1));
    TextRenderer* tempsoundSliderHeadertxtRenderer = devTools.AddTextToSpriteGameObject(soundSliderHeader, "Gabriola.ttf", "Sound", TextRenderer::xAlignmentTypes::Mid, TextRenderer::yAlignmentTypes::Mid, 24.f, (short)(sortingLayer)+2);
    tempsoundSliderHeadertxtRenderer->SetTextColor(0, 0, 0);
    OptionMenu->AddChild(soundSliderHeader);

    soundSlider = new GameObject();
    soundSlider->transform->SetPosition(Vector2(0.f,50.f));
    soundSlider->AddComponent<Slider>()->GenerateSlider(*AudioManager.GetAudioVolume(), sortingLayer + 1,1.0f);
    soundSlider->GetComponent<Slider>()->SliderEffect = &SoundSlider;
    OptionMenu->AddChild(soundSlider);

    fullScreenBtn = devTools.CreateSpriteGameObject("UI/Button.png", 500, 40, AE_GFX_BM_BLEND, Vector2(0.f, -50.f), (short)(sortingLayer + 1));
    TextRenderer* tempfullScreentxtRenderer = devTools.AddTextToSpriteGameObject(fullScreenBtn, "Gabriola.ttf", "Fullscreen", TextRenderer::xAlignmentTypes::Mid, TextRenderer::yAlignmentTypes::Mid, 24.f, (short)(sortingLayer)+2);
    Button* tempfullScreenBtn = fullScreenBtn->AddComponent<Button>();
    tempfullScreenBtn->sr = fullScreenBtn->GetComponent<SpriteRenderer>();
    tempfullScreenBtn->tr = tempfullScreentxtRenderer;
    tempfullScreenBtn->affectedObject = OptionMenu;
    tempfullScreenBtn->ButtonEffect = &FullScreen;
    OptionMenu->AddChild(fullScreenBtn);

    LeaveBtn = devTools.CreateSpriteGameObject("UI/Button.png", 500, 40, AE_GFX_BM_BLEND, Vector2(0.f, -150.f), (short)(sortingLayer + 1));
    TextRenderer* tempLeavetxtRenderer = devTools.AddTextToSpriteGameObject(LeaveBtn, "Gabriola.ttf", "Leave", TextRenderer::xAlignmentTypes::Mid, TextRenderer::yAlignmentTypes::Mid, 24.f, (short)(sortingLayer)+2);
    Button* tempLeaveBtn = LeaveBtn->AddComponent<Button>();
    tempLeaveBtn->sr = LeaveBtn->GetComponent<SpriteRenderer>();
    tempLeaveBtn->tr = tempLeavetxtRenderer;
    tempLeaveBtn->affectedObject = OptionMenu;
    tempLeaveBtn->ButtonEffect = &CloseOptionMenu;
    OptionMenu->AddChild(LeaveBtn);

}
void FullScreen(Button* button) {
    GameManager.fullScreen = !GameManager.fullScreen;
    AEToogleFullScreen(GameManager.fullScreen);
}
void MusicSlider(Slider* slider) {
    AudioManager.SetMusicVolume(slider->currentAmount);
}
void SoundSlider(Slider* slider) {
    AudioManager.SetAudioVolume(slider->currentAmount);
}
void CloseOptionMenu(Button* button) {
    GameManager.DisplayOptionMenu();
}

UI_PauseMenu::UI_PauseMenu(void)
{
}

UI_PauseMenu::~UI_PauseMenu(void)
{
}

void UI_PauseMenu::CreatePauseMenu(short sortingLayer) {
    GameObject* OptionMenu = this->Owner();

}
