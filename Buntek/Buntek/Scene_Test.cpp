#include "Scene_Test.h"
#include "AudioEngine.h"
#include "Parallaxer.h"
#include "AlphaChanger.h"
#include "ParticleSystem.h"
#include "Button.h"

void Scene_Test::Start(void)
{
	//AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	//splashimage1 = devTools.CreateSpriteGameObject("Static Stars 1.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0));
	//splashimage1->AddComponent<AlphaChanger>()->SetOscillation(5.0f, 1.0f, 0.5f, 0);
	//splashimage2 = devTools.CreateSpriteGameObject("Static Stars 2.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0));
	//splashimage2->AddComponent<AlphaChanger>()->SetOscillation(5.0f, 1.0f, 0.5f, PI);
	//splashimage3 = devTools.CreateSpriteGameObject("More Stars 1.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0));
	//splashimage3->AddComponent<AlphaChanger>()->SetOscillation(5.0f, 1.0f, 0.5f, 3*PI/2);
	//splashimage4 = devTools.CreateSpriteGameObject("More Stars 2.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0));
	//splashimage4->AddComponent<AlphaChanger>()->SetOscillation(5.0f, 1.0f, 0.5f, PI/2);
	//splashimage5 = devTools.CreateSpriteGameObject("NebulaBig.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0));
	//splashimage5->AddComponent<AlphaChanger>()->SetOscillation(6.0f, 1.0f, 0.8f, PI / 2);
	////splashimage6 = devTools.CreateSpriteGameObject("NebulaCloudBig.png", 3960, 1080, AE_GFX_BM_BLEND, Vector2(0, 0),(short)1);
	////splashimage1->AddComponent<Parallaxer>()->distance = 50;

	//spawner = new GameObject();
	//spawner->transform->worldposition = Vector2(0, 0);
	//ParticleSystem* _spawnerPs = spawner->AddComponent<ParticleSystem>();

	//_spawnerPs->SetScrollingParticle(
	//	Vector2(-1, 0), 60.0f,
	//	3960, 1080, "NebulaCloudBig.png",
	//	Vector2(-3960, 0),1,(short)AE_GFX_BM_ADD);

	//testrun1 = new GameObject;
	GameObject* freaktest = devTools.CreateSpriteGameObject("UI/DialogueBox.png", 1000, 1000,
		AE_GFX_BM_BLEND, Vector2(0.f, 0.f), 2);
	/*testrun2 = freaktest->GetComponent<SpriteRenderer>();
	freaktest->AddComponent<Button>();*/
	//testrun1->AddChild(freaktest);

    GameObject* freaktest2 = devTools.CreateSpriteGameObject("UI/DialogueBox.png", 1000, 1000,
        AE_GFX_BM_BLEND, Vector2(0.f, 0.f));
    /*freaktest2->AddComponent<TextRenderer>();
    testrun3 = freaktest2->GetComponent<TextRenderer>();*/
	//cout << "Im created: " << testrun1 << endl;
    
	//testrun1->Delete();
    freaktest->Delete();
    freaktest2->Delete();
    /*testrun2->Owner()->Delete();
    testrun3->Owner()->Delete();*/
	//cout << "Im destroyed: " << testrun1 << endl;
    /*
    //Create main dialogue box
    dialogueBox = new GameObject;
    GameObject* tempdialogue = devTools.CreateSpriteGameObject("UI/DialogueBox.png", 1900, 303,
        AE_GFX_BM_BLEND, Vector2(0, -370), 2);
    SpriteRenderer* tempRenderer = tempdialogue->GetComponent<SpriteRenderer>();
    TextRenderer* tempTextRenderer = tempdialogue->AddComponent<TextRenderer>();/*
    tempTextRenderer->SetFont("GothicA1.ttf");
    tempTextRenderer->SetFontScale(0.6f);
    tempTextRenderer->SetTextColor(1, 1, 1);
    tempTextRenderer->SetLayer(2);*/
    //dialogueBox->AddChild(tempdialogue);

    // Create actor box
    //GameObject* tempGameObject = devTools.CreateSpriteGameObject("UI/DialogueBox.png", tempRenderer->GetHalfWidth() * 2 / 4.5f, tempRenderer->GetHalfHeight() / 2,
    //    AE_GFX_BM_BLEND, Vector2(0.f, 0.f), 2);
    /*
    SpriteRenderer* tempRenderer2 = tempGameObject->GetComponent<SpriteRenderer>();
    tempRenderer2->SetOpacity(0);
    tempRenderer2->Owner()->transform->SetPosition(Vector2(
        0.0f,
        tempRenderer->GetTransform()->worldposition.y + tempRenderer2->GetHalfHeight() + 20)
    );*/

    //TextRenderer* tempTxtRenderer2 = tempGameObject->AddComponent<TextRenderer>();
    /*
    tempTxtRenderer2->SetFont("Gabriola.ttf");
    tempTxtRenderer2->SetTextColor(1.0f, 0.29f, 0.89f);
    tempTxtRenderer2->SetLayer(1);
    tempTxtRenderer2->SetLayer(2);*/

    //dialogueBox->AddChild(tempGameObject);

    //// Buttons (Max 3)
    //vector<Button*> buttonList;
    //for (int i = 0; i < 3; ++i) {
    //    GameObject* tempButtonObj = devTools.CreateSpriteGameObject("UI/Button.png", 785, 70,
    //        AE_GFX_BM_BLEND, Vector2(0.f, AEGfxGetWinMaxY() / 3 - (i * AEGfxGetWinMaxY() / 4)), 2);
    //    SpriteRenderer* tempButtonRenderer = tempButtonObj->GetComponent<SpriteRenderer>();
    //    tempButtonRenderer->SetOpacity(0.8f);

    //    TextRenderer* tempButtonTxtRenderer = tempButtonObj->AddComponent<TextRenderer>();
    //    tempButtonTxtRenderer->SetFont("Gabriola.ttf");
    //    tempButtonTxtRenderer->SetTextColor(1, 1, 1);
    //    tempButtonTxtRenderer->SetFontScale(0.75f);
    //    tempButtonTxtRenderer->SetLayer(2);
    //    tempButtonTxtRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
    //    tempButtonTxtRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);

    //    Button* tempButton = tempButtonObj->AddComponent<Button>();
    //    tempButton->sr = tempButtonRenderer;
    //    tempButton->tr = tempButtonTxtRenderer;
    //    tempButton->affectedObject = dialogueBox;

    //    //dialogueBox->AddChild(tempButtonObj);
    //    buttonList.push_back(tempButton);
    //}


    //// Rewards Choices (3 selection and 1 skip)
    //vector<Button*> tempbuttonList;
    //for (int i = 0; i < 4; ++i) {

    //    GameObject* tempButtonObj = devTools.CreateSpriteGameObject("paddle.png", 350, 500, AE_GFX_BM_BLEND,
    //        Vector2(0.f, -AEGfxGetWinMaxY() / 3.f), 2);

    //    TextRenderer* tempButtonTxtRenderer = devTools.AddTextToSpriteGameObject(tempButtonObj, "Gabriola.ttf", "I am a Reward", TextRenderer::xAlignmentTypes::Mid, TextRenderer::yAlignmentTypes::Mid, 36.f, 2);
    //    tempButtonTxtRenderer->SetTextColor(0, 0, 0);

    //    Button* tempButton = tempButtonObj->AddComponent<Button>();
    //    tempButton->sr = tempButtonObj->GetComponent<SpriteRenderer>();
    //    tempButton->tr = tempButtonTxtRenderer;
    //    tempButton->affectedObject = dialogueBox;

    //    //dialogueBox->AddChild(tempButtonObj);
    //    tempbuttonList.push_back(tempButton);
    //    switch (i)
    //    {
    //    case 0:
    //        tempButtonObj->transform->SetPosition(Vector2(0.f, tempButton->sr->GetHalfHeight() / 1.5f));
    //        break;
    //    case 1:
    //        tempButtonObj->transform->SetPosition(Vector2(-tempButton->sr->GetHalfWidth() * 3, tempButton->sr->GetHalfHeight() / 1.5f));
    //        break;
    //    case 2:
    //        tempButtonObj->transform->SetPosition(Vector2(tempButton->sr->GetHalfWidth() * 3, tempButton->sr->GetHalfHeight() / 1.5f));
    //        break;
    //    case 3:
    //        tempButton->sr->SetTexture("Buttons.png");
    //        tempButtonTxtRenderer->SetText("Skip to get sum guud seedz");
    //        tempButtonTxtRenderer->SetTextColor(1, 1, 0);
    //        tempButton->sr->Size(500, 150);
    //        break;
    //    }
    //}

    // Assign ObjReferences
    /*selectedFlag = "";
    actorTxt = tempTxtRenderer2;
    dialogueTxt = tempTextRenderer;*/
    /*dialogueButtonList = buttonList;
    rewardButtonList = tempbuttonList;*/

    /*if (actorTxt && dialogueTxt && dialogueButtonList[0])
    {
        actorTxt->Owner()->Deactivate();
        dialogueTxt->Owner()->Deactivate();
        for (int i = 0; i < dialogueButtonList.size(); ++i) {
            dialogueButtonList[i]->Owner()->Deactivate();
            dialogueButtonList[i]->Owner()->GetComponent<Button>()->SetClickable(false);
        }
    }*/

    /*if (dialogueButtonList.size() > 0)
    {
        for (int i = 0; i < dialogueButtonList.size(); i++)
            dialogueButtonList[i]->Owner()->Delete();
        dialogueButtonList.clear();
    }*/

    /*if (rewardButtonList.size() > 0)
    {
        for (int i = 0; i < rewardButtonList.size(); i++)
            rewardButtonList[i]->Owner()->Delete();
        rewardButtonList.clear();
    }*/

    /*if (dialogueBox)
    {
        dialogueBox->Delete();
        dialogueBox = nullptr;
    }*/

    /*if (actorTxt)
    {
        actorTxt->Owner()->Delete();
        actorTxt = nullptr;
    }

    if (dialogueTxt)
    {
        dialogueTxt->Owner()->Delete();
        dialogueTxt = nullptr;
    }*/
    /*
    actorTxt->Owner()->Delete();
    dialogueTxt->Owner()->Delete();*/
}

void Scene_Test::Update(void)
{
	//Vector2 addPos = Vector2((float)(50.0f * DeltaTime), (float)0);
	//splashimage6->transform->worldposition += addPos;
	
}
