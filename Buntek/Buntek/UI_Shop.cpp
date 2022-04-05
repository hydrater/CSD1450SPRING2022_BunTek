/*!*****************************************************************************
\file UI_Shop.cpp
\author: Isaiah Lim Ji Rong (90%)
\co-authors: Algene Tan Chuan Hong (2.5%), Steven Koe (2.5%), Bryan Boh Tai Hong (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Shop UI
*******************************************************************************/

#include "MapGenerator.h"
#include "SaveManager.h"
#include "UI_Shop.h"
#include "Devtools.h"
#include "System.h"
#include "UI_DialogueHandler.h"
#include "AudioEngine.h"

void RemoveShop(Button* button);
void PurchaseArtifact(Button* button);

UI_Shop::UI_Shop(void)
{
}

UI_Shop::~UI_Shop(void)
{
}

void UI_Shop::CreateShop(short sortingLayer, _mapData::ShopArtifacts shop)
{
    GameObject* shopUI = this->Owner();
    DisplayedShop = shop;

    // Background
    GameObject* tempBckgrnd = devTools.CreateSpriteGameObject("ShopBackground.png", (float)AEGetWindowWidth(), (float)AEGetWindowHeight(), AE_GFX_BM_BLEND, Vector2(0.f, 0.f), (short)(sortingLayer), 1.f);
    shopUI->AddChild(tempBckgrnd);
    
    // Header
    GameObject* tempHeader = devTools.CreateSpriteGameObject("UI/Button.png", headerXSize, headerYSize, AE_GFX_BM_BLEND, headerPos, sortingLayer + headerOffset);

    // HeaderText
    TextRenderer* tempHeaderTxtRenderer = 0;
    tempHeaderTxtRenderer = tempHeader->AddComponent<TextRenderer>();
    tempHeaderTxtRenderer->SetFont("Gabriola.ttf");
    tempHeaderTxtRenderer->SetTextColor(1, 1, 1);
    tempHeaderTxtRenderer->SetText("Shop");
    tempHeaderTxtRenderer->SetLayer(sortingLayer + 2);
    tempHeaderTxtRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
    tempHeaderTxtRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);
    tempHeaderTxtRenderer->SetXBuffer(50);
    shopUI->AddChild(tempHeader);

    // StarDust Display
    GameObject* tempCurrencyDisplay = devTools.CreateSpriteGameObject("WhiteTexture.png", currencyXSize, currencyYSize, AE_GFX_BM_BLEND, currencyPos, sortingLayer + currencyOffset, 1);
    SpriteRenderer* tempCurrencySprite = tempCurrencyDisplay->GetComponent<SpriteRenderer>();
    tempCurrencySprite->SetColor(0.85f, 0.5f, 0.5f);
    GameObject* tempCurrencyIcon = devTools.CreateSpriteGameObject("UI/Stardust.png", currencyIconXSize, currencyIconYSize, AE_GFX_BM_BLEND,
        Vector2(tempCurrencyDisplay->transform->worldposition.x + currencyIconXOffset, tempCurrencyDisplay->transform->worldposition.y), sortingLayer + currencyIconOffset, 1);
    GameObject* tempCurrencyTextObj = devTools.CreateSpriteGameObject("UI/Stardust.png", currencyPriceXSize, currencyPriceYSize, AE_GFX_BM_BLEND, Vector2(tempCurrencyDisplay->transform->worldposition.x + currencyPriceXOffset, tempCurrencyDisplay->transform->worldposition.y), sortingLayer + currencyPriceOffset, 0);
    currencyTxt = devTools.AddTextToSpriteGameObject(tempCurrencyTextObj, "Gabriola.ttf", to_string(GameManager.playerProfile.stardust), TextRenderer::xAlignmentTypes::Left, TextRenderer::yAlignmentTypes::Mid, 72.f, sortingLayer + currencyPriceOffset);
    currencyTxt->SetTextColor(0, 0, 0);
    shopUI->AddChild(tempCurrencyDisplay);
    shopUI->AddChild(tempCurrencyIcon);
    shopUI->AddChild(tempCurrencyTextObj);

    // Leave Button
    GameObject* tempLeave = devTools.CreateSpriteGameObject("UI/Button.png", leaveXSize, leaveYSize, AE_GFX_BM_BLEND, leavePos, sortingLayer + leaveOffset);
    TextRenderer* tempLeaveTxtRenderer = 0;
    tempLeaveTxtRenderer = tempLeave->AddComponent<TextRenderer>();
    tempLeaveTxtRenderer->SetFont("Gabriola.ttf");
    tempLeaveTxtRenderer->SetTextColor(1, 1, 1);
    tempLeaveTxtRenderer->SetText("Exit");
    tempLeaveTxtRenderer->SetLayer((short)(sortingLayer + 3));
    Button* tempLeaveButton = tempLeave->AddComponent<Button>();
    tempLeaveButton->sr = tempLeave->GetComponent<SpriteRenderer>();
    tempLeaveButton->tr = tempLeaveTxtRenderer;
    tempLeaveButton->affectedObject = shopUI;
    tempLeaveButton->ButtonEffect = &RemoveShop;
    shopUI->AddChild(tempLeave);

    // Shop Artifacts Buttons
    vector<Button*> tempbuttonArtifactList;
    for (int i = 0; i < shop.ArtifactsOnDisplay.size(); ++i) {
        if (i < buttonArtifactPos.size())
        {
            GameObject* tempButtonObj = devTools.CreateArtifactRewardCard(shop.ArtifactsOnDisplay[i],
                Vector2(buttonArtifactPos[i].x, buttonArtifactPos[i].y), sortingLayer + artifactButtonSpriteOffset);

            Button* tempButton = tempButtonObj->AddComponent<Button>();
            tempButton->sr = tempButtonObj->GetComponent<SpriteRenderer>();
            tempButton->tr = tempButtonObj->GetComponent<TextRenderer>();
            tempButton->affectedObject = shopUI;
            tempButton->ButtonEffect = &PurchaseArtifact;
            if (shop.ArtifactsPurchased[i])
            {
                tempButton->sr->SetOpacity(0.5f);
                tempButton->SetClickable(false);
            }

            // Get Price
            int price = 0;
            switch (ArtifactDatabase.GetRarity(shop.ArtifactsOnDisplay[i]))
            {
            case RarityTypes::Uncommon:
                price = RP_Uncommon;
                    break;
            case RarityTypes::Rare:
                price = RP_Rare;
                    break;
            default:
                price = RP_Common;
                break;
            }
            
            GameObject* tempPriceObj = devTools.CreatePriceTagGameObject(price, AE_GFX_BM_BLEND,
                Vector2(buttonArtifactPos[i].x + tempButton->sr->GetHalfWidth() * 1.1f, buttonArtifactPos[i].y + tempButton->sr->GetHalfHeight() / 2.f), sortingLayer + artifactButtonTextOffset);
            tempButtonObj->AddChild(tempPriceObj);

            shopUI->AddChild(tempButtonObj);
            tempbuttonArtifactList.push_back(tempButton);

            ArtifactGoods newGood;
            newGood.DisplayArtifactOwner = tempButtonObj;
            newGood.ArtifactID = shop.ArtifactsOnDisplay[i];
            newGood.purchased = shop.ArtifactsPurchased[i];
            newGood.price = price;
            ArtifactOnSale.push_back(newGood);
        }
    }

    header = tempHeader->GetComponent<SpriteRenderer>();
    headerText = tempHeaderTxtRenderer;
    leaveButton = tempLeaveButton;
    buttonArtifactList = tempbuttonArtifactList;

    CloseShop();

    StartShop();

    SetClickable(false);
}

void UI_Shop::StartShop(void)
{
    header->Owner()->Activate();
    headerText->Owner()->Activate();
    leaveButton->Owner()->Activate();
    for (int i = 0; i < buttonArtifactList.size(); ++i)
        buttonArtifactList[i]->Owner()->Activate();
}

void UI_Shop::CloseShop(void)
{
    header->Owner()->Deactivate();
    headerText->Owner()->Deactivate();
    leaveButton->Owner()->Deactivate();
    for (int i = 0; i < buttonArtifactList.size(); ++i)
        buttonArtifactList[i]->Owner()->Deactivate();
}

void UI_Shop::DeleteShop(void)
{
    // Delete ArtifactOnSale
    for (ArtifactGoods selArtifact : ArtifactOnSale)
        selArtifact.DisplayArtifactOwner->Delete();
    ArtifactOnSale.clear();

    header->Owner()->Delete();
    headerText->Owner()->Delete();
    leaveButton->Owner()->Delete();
    currencyTxt->Owner()->Delete();
    for (int i = 0; i < buttonArtifactList.size(); ++i)
        buttonArtifactList[i]->Owner()->Delete();
    buttonArtifactList.clear();

    buttonArtifactPos.clear();

    header = 0;
    headerText = 0;
    leaveButton = 0;
    currencyTxt = 0;
}

void UI_Shop::SetClickable(bool _canClick)
{
    for (int i = 0; i < buttonArtifactList.size(); ++i)
    {
        if (ArtifactOnSale[i].purchased == true)
        {
            buttonArtifactList[i]->Owner()->GetComponent<Button>()->SetHoverable(false);
            buttonArtifactList[i]->Owner()->GetComponent<Button>()->SetClickable(false);
        }
        else
        {
            buttonArtifactList[i]->Owner()->GetComponent<Button>()->SetHoverable(_canClick);
            buttonArtifactList[i]->Owner()->GetComponent<Button>()->SetClickable(_canClick);
        }
    }
}

void RemoveShop(Button* button)
{
    SaveManager.SaveData();
    GameObject* tmp = button->affectedObject;
    tmp->GetComponent<UI_Shop>()->CloseShop();
    MapData.SetClickable(true);
    MapData.SetHoverable(true);
    MapData.DisplayNodeRoutes(MapData.playerTravelDistance);
    if (MapData.shopUI)
    {
        MapData.shopUI->GetComponent<UI_Shop>()->DeleteShop();
        MapData.shopUI->Delete();
        MapData.shopUI = 0;
    }
}

void PurchaseArtifact(Button* button)
{
    // Add artifact to the player's Artifact List
    GameObject* owner = button->Owner();
    UI_Shop::ArtifactGoods* selGood = 0;
    unsigned long ID = 0;
    int index = 0;
    bool isPurchased = false;
    int price = 0;
    for (; index < MapData.shopUI->GetComponent<UI_Shop>()->ArtifactOnSale.size(); ++index)
    {
        selGood = &(MapData.shopUI->GetComponent<UI_Shop>()->ArtifactOnSale[index]);
        if (owner == selGood->DisplayArtifactOwner)
        {
            ID = selGood->ArtifactID;
            isPurchased = selGood->purchased;
            price = selGood->price;
            break;
        }
    }
    // Assign to allocated vector
    if (selGood && !isPurchased && GameManager.playerProfile.stardust >= price)
    {
        GameManager.playerProfile.stardust -= price;
        selGood->purchased = true;
        // Update Shop purchased
        for (int i{ 0 }; i < MapData.Shops.size(); ++i)
        {
            if (MapData.shopUI->GetComponent<UI_Shop>()->DisplayedShop.ID == MapData.Shops[i].ID)
            {
                MapData.Shops[i].ArtifactsPurchased[index] = true;
                AudioManager.PlayClip("MakePurchase.wav");
            }
        }
        MapData.shopUI->GetComponent<UI_Shop>()->currencyTxt->SetText(to_string(GameManager.playerProfile.stardust));
        selGood->DisplayArtifactOwner->GetComponent<SpriteRenderer>()->SetOpacity(0.5f);
        selGood->DisplayArtifactOwner->GetComponent<Button>()->SetClickable(false);
        SaveManager.AddToArtifactList(ID);
    }
}