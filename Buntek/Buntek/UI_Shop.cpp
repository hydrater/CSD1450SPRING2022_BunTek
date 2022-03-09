#include "MapGenerator.h"
#include "SaveManager.h"
#include "UI_Shop.h"
#include "Devtools.h"
#include "System.h"

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
    GameObject* tempBckgrnd = devTools.CreateSpriteGameObject("ShopBackground.png", AEGetWindowWidth(), AEGetWindowHeight(), AE_GFX_BM_BLEND, Vector2(0.f, 0.f), (short)(sortingLayer), 1.f);
    shopUI->AddChild(tempBckgrnd);

    // Header
    GameObject* tempHeader = devTools.CreateSpriteGameObject("Encounter.png", 600, 100, AE_GFX_BM_BLEND, Vector2(0.f, AEGetWindowHeight() / 2.25f),(short)(sortingLayer + 1), 0.5f);
   

    // HeaderText
    TextRenderer* tempHeaderTxtRenderer = 0;
    tempHeaderTxtRenderer = tempHeader->AddComponent<TextRenderer>();
    tempHeaderTxtRenderer->SetFont("Gabriola.ttf");
    tempHeaderTxtRenderer->SetTextColor(1, 1, 1);
    tempHeaderTxtRenderer->SetText("Shop");
    tempHeaderTxtRenderer->SetLayer(sortingLayer);
    tempHeaderTxtRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
    tempHeaderTxtRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);
    tempHeaderTxtRenderer->SetXBuffer(50);
    shopUI->AddChild(tempHeader);

    // StarDust Display
    GameObject* tempCurrencyDisplay = devTools.CreateSpriteGameObject("WhiteTexture.png", 300, 100, AE_GFX_BM_BLEND, Vector2(-AEGetWindowWidth()/ 2.5f, AEGetWindowHeight() / 2.25f), (short)(sortingLayer + 1), 1);
    SpriteRenderer* tempCurrencySprite = tempCurrencyDisplay->GetComponent<SpriteRenderer>();
    tempCurrencySprite->SetColor(0.85f, 0.5f, 0.5f);
    GameObject* tempCurrencyIcon = devTools.CreateSpriteGameObject("UI/Stardust.png", 80, 80, AE_GFX_BM_BLEND,
        Vector2(tempCurrencyDisplay->transform->worldposition.x - 100, tempCurrencyDisplay->transform->worldposition.y), (short)(sortingLayer + 2), 1);
    GameObject* tempCurrencyTextObj = devTools.CreateSpriteGameObject("UI/Stardust.png", 180, 80, AE_GFX_BM_BLEND, Vector2(tempCurrencyDisplay->transform->worldposition.x + 50, tempCurrencyDisplay->transform->worldposition.y), (short)(sortingLayer) + 3, 0);
    TextRenderer* tempCurrencyText = devTools.AddTextToSpriteGameObject(tempCurrencyTextObj, "Gabriola.ttf", to_string(GameManager.playerProfile.stardust), TextRenderer::xAlignmentTypes::Left, TextRenderer::yAlignmentTypes::Mid, 72.f, (short)(sortingLayer) + 3);
    tempCurrencyText->SetTextColor(0, 0, 0);
    shopUI->AddChild(tempCurrencyDisplay);
    shopUI->AddChild(tempCurrencyIcon);
    shopUI->AddChild(tempCurrencyTextObj);

    // Leave Button
    GameObject* tempLeave = devTools.CreateSpriteGameObject("Buttons.png", 500, 100, AE_GFX_BM_BLEND, Vector2(0.f, -AEGetWindowHeight() / 2.5f), (short)(sortingLayer + 2));
    TextRenderer* tempLeaveTxtRenderer = 0;
    tempLeaveTxtRenderer = tempLeave->AddComponent<TextRenderer>();
    tempLeaveTxtRenderer->SetFont("Gabriola.ttf");
    tempLeaveTxtRenderer->SetTextColor(1, 1, 1);
    tempLeaveTxtRenderer->SetText("Leave");
    tempLeaveTxtRenderer->SetLayer((short)(sortingLayer + 2));
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
            GameObject* tempButtonObj = devTools.CreateArtifactUIGameObject(shop.ArtifactsOnDisplay[i],
                Vector2(buttonArtifactPos[i].x, buttonArtifactPos[i].y), sortingLayer + 2);

            Button* tempButton = tempButtonObj->AddComponent<Button>();
            tempButton->sr = tempButtonObj->GetComponent<SpriteRenderer>();
            tempButton->tr = tempButtonObj->GetComponent<TextRenderer>();
            tempButton->affectedObject = shopUI;
            tempButton->ButtonEffect = &PurchaseArtifact;
            if (shop.ArtifactsPurchased[i] == true)
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
                Vector2(buttonArtifactPos[i].x + tempButton->sr->GetHalfWidth() * 1.1f, buttonArtifactPos[i].y + tempButton->sr->GetHalfHeight() / 2.f), sortingLayer + 2);
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

void UI_Shop::SetClickable(bool _canClick)
{
    for (int i = 0; i < buttonArtifactList.size(); ++i)
    {
        if (ArtifactOnSale[i].purchased == true)
        {
            buttonArtifactList[i]->Owner()->GetComponent<Button>()->SetClickable(false);
        }
        else
        {
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
        MapData.shopUI->GetComponent<UI_Shop>()->ArtifactOnSale.clear();
        MapData.shopUI->Delete();
    }
    MapData.shopUI = 0;
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
            }
        }
        selGood->DisplayArtifactOwner->GetComponent<SpriteRenderer>()->SetOpacity(0.5f);
        selGood->DisplayArtifactOwner->GetComponent<Button>()->SetClickable(false);
        SaveManager.AddToArtifactList(ID);
    }
}