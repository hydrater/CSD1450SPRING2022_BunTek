/*!*****************************************************************************
\file UI_Menu.cpp
\author: Bryan Boh Tai Hong (80%)
\co-authors: Algene Tan Chuan Hong (5%), Isaiah Lim Ji Rong (5%), Steven Koe (5%), Goh Kiat Beng (5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Menu behaviour
*******************************************************************************/
#include "UI_Menu.h"
#include "Devtools.h"
#include "Slider.h"
#include "Button.h"
#include "AudioEngine.h"
#include "MapGenerator.h"
#include "UI_DialogueHandler.h"
#include "DialogueDatabase.h"
#include "GameManager.h"
#include "SaveManager.h"
#include "Scene_MainMenu.h"

void Options(Button* button);
void FullScreen(Button* button);
void MusicSlider(Slider* slider);
void SoundSlider(Slider* slider);

void PauseOptions(Button* button);

void Resume(Button* button);
void Surrender(Button* button);
void Quit(Button* button);
void SurrenderUnhover(Button* button);
void QuitUnhover(Button* button);

void HowToPlay(Button* button);
void PauseHowToPlay(Button* button);


UI_OptionMenu::UI_OptionMenu(void)
{
}

UI_OptionMenu::~UI_OptionMenu(void)
{
}

void UI_OptionMenu::CreateOptionMenu(short sortingLayer) {
    GameObject* OptionMenu = this->Owner();

    // Background
    tempBckgrnd = devTools.CreateSpriteGameObject("WhiteTexture.png", (float)AEGetWindowWidth() / 3, (float)AEGetWindowHeight() / 1.5f, AE_GFX_BM_BLEND, Vector2(0.f, 100.f), (short)(sortingLayer), 0.8f);
    tempBckgrnd->GetComponent<SpriteRenderer>()->SetColor(0, 0, 0);
    OptionMenu->AddChild(tempBckgrnd);

    header = devTools.CreateSpriteGameObject("WhiteTexture.png", 200, 100, AE_GFX_BM_BLEND, Vector2(0.f, 400.f), (short)(sortingLayer + 1), 0);
    TextRenderer* tempHeadertxtRenderer = devTools.AddTextToSpriteGameObject(header, "Ayar.ttf", "Options", TextRenderer::xAlignmentTypes::Mid, TextRenderer::yAlignmentTypes::Mid, 48.f, (short)(sortingLayer)+2);
    tempHeadertxtRenderer->SetTextColor(1, 1, 1);
    OptionMenu->AddChild(header);

    musicSliderHeader = devTools.CreateSpriteGameObject("WhiteTexture.png", 100, 60, AE_GFX_BM_BLEND, Vector2(0.f, 250.f), (short)(sortingLayer + 1), 0);
    TextRenderer* tempmusicSliderHeaderRenderer = devTools.AddTextToSpriteGameObject(musicSliderHeader, "Ayar.ttf", "Music", TextRenderer::xAlignmentTypes::Mid, TextRenderer::yAlignmentTypes::Mid, 28.f, (short)(sortingLayer)+2);
    OptionMenu->AddChild(musicSliderHeader);

    musicSlider = new GameObject();
    musicSlider->transform->SetPosition(Vector2(0.f,200.f));
    musicSlider->AddComponent<Slider>()->GenerateSlider(*AudioManager.GetMusicVolume(), sortingLayer + 1, 1.0f);
    musicSlider->GetComponent<Slider>()->SliderEffect = &MusicSlider;
    OptionMenu->AddChild(musicSlider);

    soundSliderHeader = devTools.CreateSpriteGameObject("WhiteTexture.png", 100, 60, AE_GFX_BM_BLEND, Vector2(0.f, 100.f), (short)(sortingLayer + 1), 0);
    TextRenderer* tempsoundSliderHeadertxtRenderer = devTools.AddTextToSpriteGameObject(soundSliderHeader, "Ayar.ttf", "Sound", TextRenderer::xAlignmentTypes::Mid, TextRenderer::yAlignmentTypes::Mid, 28, (short)(sortingLayer)+2);
    OptionMenu->AddChild(soundSliderHeader);

    soundSlider = new GameObject();
    soundSlider->transform->SetPosition(Vector2(0.f,50.f));
    soundSlider->AddComponent<Slider>()->GenerateSlider(*AudioManager.GetAudioVolume(), sortingLayer + 1,1.0f);
    soundSlider->GetComponent<Slider>()->SliderEffect = &SoundSlider;
    OptionMenu->AddChild(soundSlider);

    fullScreenBtn = devTools.CreateSpriteGameObject("Menu/Button.png", 380, 40, AE_GFX_BM_BLEND, Vector2(0.f, -50.f), (short)(sortingLayer + 1));
    TextRenderer* tempfullScreentxtRenderer = devTools.AddTextToSpriteGameObject(fullScreenBtn, "Ayar.ttf", "Toggle fullscreen", TextRenderer::xAlignmentTypes::Mid, TextRenderer::yAlignmentTypes::Mid, 24.f, (short)(sortingLayer)+2);
    tempfullScreentxtRenderer->SetTextColor(0, 0, 0);
    Button* tempfullScreenBtn = fullScreenBtn->AddComponent<Button>();
    tempfullScreenBtn->sr = fullScreenBtn->GetComponent<SpriteRenderer>();
    tempfullScreenBtn->tr = tempfullScreentxtRenderer;
    tempfullScreenBtn->affectedObject = OptionMenu;
    tempfullScreenBtn->ButtonEffect = &FullScreen;
    OptionMenu->AddChild(fullScreenBtn);

    LeaveBtn = devTools.CreateSpriteGameObject("Menu/Button.png", 380, 40, AE_GFX_BM_BLEND, Vector2(0.f, -150.f), (short)(sortingLayer + 1));
    TextRenderer* tempLeavetxtRenderer = devTools.AddTextToSpriteGameObject(LeaveBtn, "Ayar.ttf", "Back", TextRenderer::xAlignmentTypes::Mid, TextRenderer::yAlignmentTypes::Mid, 24.f, (short)(sortingLayer)+2);
    tempLeavetxtRenderer->SetTextColor(0, 0, 0);
    Button* tempLeaveBtn = LeaveBtn->AddComponent<Button>();
    tempLeaveBtn->sr = LeaveBtn->GetComponent<SpriteRenderer>();
    tempLeaveBtn->tr = tempLeavetxtRenderer;
    tempLeaveBtn->affectedObject = OptionMenu;
    if (GameManager.pauseMenuOpen) {
        tempLeaveBtn->ButtonEffect = &PauseOptions;
    }
    else {
        tempLeaveBtn->ButtonEffect = &Options;
    }
    OptionMenu->AddChild(LeaveBtn);

}
void FullScreen(Button* button) {
    GameManager.isFullScreen = !GameManager.isFullScreen;
    AEToogleFullScreen(GameManager.isFullScreen);
}
void MusicSlider(Slider* slider) {
    AudioManager.SetMusicVolume(slider->currentAmount);
}
void SoundSlider(Slider* slider) {
    AudioManager.SetAudioVolume(slider->currentAmount);
}
void Options(Button* button) {
    GameManager.DisplayOptionMenu();
}
void PauseOptions(Button* button) {
    GameManager.DisplayPauseOptionMenu();
}
UI_PauseMenu::UI_PauseMenu(void)
{
}

UI_PauseMenu::~UI_PauseMenu(void)
{
}

void UI_PauseMenu::CreatePauseMenu(short sortingLayer) {
    GameObject* PauseMenu = this->Owner();

    // Background
    tempBckgrnd = devTools.CreateSpriteGameObject("WhiteTexture.png", (float)AEGetWindowWidth() / 3, (float)AEGetWindowHeight() / 1.5f, AE_GFX_BM_BLEND, Vector2(0.f, 100.f), (short)(sortingLayer), 0.8f);
    tempBckgrnd->GetComponent<SpriteRenderer>()->SetColor(0, 0, 0);
    PauseMenu->AddChild(tempBckgrnd);

    Header = devTools.CreateSpriteGameObject("WhiteTexture.png", 200, 100, AE_GFX_BM_BLEND, Vector2(0.f, 400.f), (short)(sortingLayer + 1), 0);
    TextRenderer* tempHeadertxtRenderer = devTools.AddTextToSpriteGameObject(Header, "Ayar.ttf", "Pause", TextRenderer::xAlignmentTypes::Mid, TextRenderer::yAlignmentTypes::Mid, 48.f, (short)(sortingLayer)+2);
    tempHeadertxtRenderer->SetTextColor(1, 1, 1);
    PauseMenu->AddChild(Header);

    resumeBtn = devTools.CreateSpriteGameObject("Menu/Button.png", 380, 40, AE_GFX_BM_BLEND, Vector2(0.f, 200.f), (short)(sortingLayer + 1));
    TextRenderer* tempResumetxtRenderer = devTools.AddTextToSpriteGameObject(resumeBtn, "Ayar.ttf", "Resume", TextRenderer::xAlignmentTypes::Mid, TextRenderer::yAlignmentTypes::Mid, 24.f, (short)(sortingLayer)+2);
    tempResumetxtRenderer->SetTextColor(0, 0, 0);
    Button* tempResumeBtn = resumeBtn->AddComponent<Button>();
    tempResumeBtn->sr = resumeBtn->GetComponent<SpriteRenderer>();
    tempResumeBtn->tr = tempResumetxtRenderer;
    tempResumeBtn->affectedObject = PauseMenu;
    tempResumeBtn->ButtonEffect = &Resume;
    PauseMenu->AddChild(resumeBtn);

    optionBtn = devTools.CreateSpriteGameObject("Menu/Button.png", 380, 40, AE_GFX_BM_BLEND, Vector2(0.f, 100.f), (short)(sortingLayer + 1));
    TextRenderer* tempOptiontxtRenderer = devTools.AddTextToSpriteGameObject(optionBtn, "Ayar.ttf", "Options", TextRenderer::xAlignmentTypes::Mid, TextRenderer::yAlignmentTypes::Mid, 24.f, (short)(sortingLayer)+2);
    tempOptiontxtRenderer->SetTextColor(0, 0, 0);
    Button* tempOptionBtn = optionBtn->AddComponent<Button>();
    tempOptionBtn->sr = optionBtn->GetComponent<SpriteRenderer>();
    tempOptionBtn->tr = tempOptiontxtRenderer;
    tempOptionBtn->affectedObject = PauseMenu;
    tempOptionBtn->ButtonEffect = &PauseOptions;
    PauseMenu->AddChild(optionBtn);

    howToPlayBtn = devTools.CreateSpriteGameObject("Menu/Button.png", 380, 40, AE_GFX_BM_BLEND, Vector2(0.f, 0.f), (short)(sortingLayer + 1));
    TextRenderer* tempHowToPlaytxtRenderer = devTools.AddTextToSpriteGameObject(howToPlayBtn, "Ayar.ttf", "How to play", TextRenderer::xAlignmentTypes::Mid, TextRenderer::yAlignmentTypes::Mid, 24.f, (short)(sortingLayer)+2);
    tempHowToPlaytxtRenderer->SetTextColor(0, 0, 0);
    Button* tempHowToPlayBtn = howToPlayBtn->AddComponent<Button>();
    tempHowToPlayBtn->sr = howToPlayBtn->GetComponent<SpriteRenderer>();
    tempHowToPlayBtn->tr = tempHowToPlaytxtRenderer;
    tempHowToPlayBtn->affectedObject = PauseMenu;
    tempHowToPlayBtn->ButtonEffect = &PauseHowToPlay;
    PauseMenu->AddChild(howToPlayBtn);

    surrenderBtn = devTools.CreateSpriteGameObject("Menu/Button.png", 380, 40, AE_GFX_BM_BLEND, Vector2(0.f,-100.f), (short)(sortingLayer + 1));
    TextRenderer* tempSurrendertxtRenderer = devTools.AddTextToSpriteGameObject(surrenderBtn, "Ayar.ttf", "Abandon run", TextRenderer::xAlignmentTypes::Mid, TextRenderer::yAlignmentTypes::Mid, 24.f, (short)(sortingLayer)+2);
    tempSurrendertxtRenderer->SetTextColor(0, 0, 0);
    Button* tempSurrenderBtn = surrenderBtn->AddComponent<Button>();
    tempSurrenderBtn->sr = surrenderBtn->GetComponent<SpriteRenderer>();
    tempSurrenderBtn->tr = tempSurrendertxtRenderer;
    tempSurrenderBtn->affectedObject = PauseMenu;
    tempSurrenderBtn->ButtonEffect = &Surrender;
    tempSurrenderBtn->NotHoverEffect = &SurrenderUnhover;
    PauseMenu->AddChild(surrenderBtn);

    quitBtn = devTools.CreateSpriteGameObject("Menu/Button.png", 380, 40, AE_GFX_BM_BLEND, Vector2(0.f, -200.f), (short)(sortingLayer + 1));
    TextRenderer* tempQuittxtRenderer = devTools.AddTextToSpriteGameObject(quitBtn, "Ayar.ttf", "Quit to Main Menu", TextRenderer::xAlignmentTypes::Mid, TextRenderer::yAlignmentTypes::Mid, 24.f, (short)(sortingLayer)+2);
    tempQuittxtRenderer->SetTextColor(0, 0, 0);
    Button* tempQuitBtn = quitBtn->AddComponent<Button>();
    tempQuitBtn->sr = quitBtn->GetComponent<SpriteRenderer>();
    tempQuitBtn->tr = tempQuittxtRenderer;
    tempQuitBtn->affectedObject = PauseMenu;
    tempQuitBtn->ButtonEffect = &Quit;
    tempQuitBtn->NotHoverEffect = &QuitUnhover;
    PauseMenu->AddChild(quitBtn);
}

void Resume(Button* button) {
    GameManager.DisplayPauseMenu();
}
void Surrender(Button* button) {
    if (button->Owner()->GetComponent<TextRenderer>()->GetText() == "Are you sure?") {
        GameManager.DisplayPauseMenu();
        GameManager.GameOver();
    }
    else {
        button->Owner()->GetComponent<TextRenderer>()->SetText("Are you sure?");
        button->Owner()->GetComponent<SpriteRenderer>()->SetColor(0.7f, 0.31f, 0.96f);
    }
    AudioManager.LoadSound("ButtonHover.wav");
    AudioManager.PlayClip("ButtonHover.wav");
    button->hoverplay = false;
}
void Quit(Button* button) {
    if (button->Owner()->GetComponent<TextRenderer>()->GetText() == "Are you sure?") {
        GameManager.DisplayPauseMenu();
        SceneManager.LoadScene(new Scene_MainMenu, TransitionType::FadeTransition, true);
        if (MapData.shopUI)
        {
            MapData.shopUI->Delete();
            MapData.shopUI = 0;
        }
        DialogueDatabase.ClearDialogueSceneObjs();
        UIDialogueManager.DeleteDialogueEvent();
    }
    else {
        button->Owner()->GetComponent<TextRenderer>()->SetText("Are you sure?");
        button->Owner()->GetComponent<SpriteRenderer>()->SetColor(0.7f, 0.31f, 0.96f);
    }
    AudioManager.LoadSound("ButtonHover.wav");
    AudioManager.PlayClip("ButtonHover.wav");

    button->hoverplay = false;
}
void SurrenderUnhover(Button* button) {
    if (!button->Owner()->remove) {
        if (button->Owner()->GetComponent<TextRenderer>()->GetText() == "Are you sure?") {
            button->Owner()->GetComponent<TextRenderer>()->SetText("Abandon run");
            button->Owner()->GetComponent<SpriteRenderer>()->SetColor(1, 1, 1);
            if (MapData.shopUI)
            {
                MapData.shopUI->Delete();
                MapData.shopUI = 0;
            }
            DialogueDatabase.ClearDialogueSceneObjs();
            UIDialogueManager.DeleteDialogueEvent();
        }
        if (!button->hoverplay) {
            AudioManager.UnloadSound("ButtonHover.wav");
            button->sr->Size(button->sr->GetHalfWidth() * 2 / 6 * 5, button->sr->GetHalfHeight() * 2 / 6 * 5);
            button->tr->SetFontSize(button->tr->GetFontSize() / 6 * 5);
            button->hoverplay = true;
        }
    }
}
void QuitUnhover(Button* button) {
    if (!button->Owner()->remove) {
        if (button->Owner()->GetComponent<TextRenderer>()->GetText() == "Are you sure?") {
            button->Owner()->GetComponent<TextRenderer>()->SetText("Quit to Main Menu");
            button->Owner()->GetComponent<SpriteRenderer>()->SetColor(1, 1, 1);
        }
        if (!button->hoverplay) {
            AudioManager.UnloadSound("ButtonHover.wav");
            button->sr->Size(button->sr->GetHalfWidth() * 2 / 6 * 5, button->sr->GetHalfHeight() * 2 / 6 * 5);
            button->tr->SetFontSize(button->tr->GetFontSize() / 6 * 5);
            button->hoverplay = true;
        }
    }

}

UI_HowToPlayMenu::UI_HowToPlayMenu(void)
{
}

UI_HowToPlayMenu::~UI_HowToPlayMenu(void)
{
}

void UI_HowToPlayMenu::CreateHowToPlayMenu(short sortingLayer) {
    GameObject* HowToPlayMenu = this->Owner();

    // Background
    tempBckgrnd = devTools.CreateSpriteGameObject("PlayGuide.png", (float)AEGetWindowWidth(), (float)AEGetWindowHeight(), AE_GFX_BM_BLEND, Vector2(0.f, 0.f), (short)(sortingLayer), 1.0f);
    HowToPlayMenu->AddChild(tempBckgrnd);


    backBtn = devTools.CreateSpriteGameObject("Menu/Button.png", 300, 40, AE_GFX_BM_BLEND, Vector2(750.0f, -400.0f), (short)(sortingLayer + 1));
    TextRenderer* tempBacktxtRenderer = devTools.AddTextToSpriteGameObject(backBtn, "Ayar.ttf", "Back", TextRenderer::xAlignmentTypes::Mid, TextRenderer::yAlignmentTypes::Mid, 24.f, (short)(sortingLayer)+2);
    tempBacktxtRenderer->SetTextColor(0, 0, 0);
    Button* tempBackBtn = backBtn->AddComponent<Button>();
    tempBackBtn->sr = backBtn->GetComponent<SpriteRenderer>();
    tempBackBtn->tr = tempBacktxtRenderer;
    tempBackBtn->affectedObject = HowToPlayMenu;
    if (GameManager.pauseMenuOpen) {
        tempBackBtn->ButtonEffect = &PauseHowToPlay;
    }
    else {
        tempBackBtn->ButtonEffect = &HowToPlay;
    }
    HowToPlayMenu->AddChild(backBtn);

}
void HowToPlay(Button* button) {
    GameManager.DisplayHowToPlayMenu();
}
void PauseHowToPlay(Button* button) {
    GameManager.DisplayPauseHowToPlayMenu();
}