#include "EnemyNodeBox.h"
#include <fstream>
#include <sstream>

EnemyNodeBox::EnemyNodeBox(void)
{

}

EnemyNodeBox::~EnemyNodeBox(void)
{
}

void EnemyNodeBox::Start(void)
{

}

void EnemyNodeBox::Update(void)
{

}

void EnemyNodeBox::CreateEnemyNode(GameObject* button, int sortingLayer, int ArtifactTypes) {

	GameObject* enemynode = this->Owner();
	enemynode->transform->SetPosition(button->transform->worldposition);

	SpriteRenderer* tempBckgdRenderer = 0;
	tempBckgdRenderer = enemynode->AddComponent<SpriteRenderer>();
	tempBckgdRenderer->Size(300, 300);
	tempBckgdRenderer->SetTexture("WhiteTexture.png");
	tempBckgdRenderer->SetLayer(sortingLayer - 2);

	enemynode->transform->SetPosition(button->transform->worldposition);
	Vector2 enemynodepos = enemynode->transform->worldposition;

	//Name
	GameObject* tempEnemyname = new GameObject();
	SpriteRenderer* tempEnemynameRenderer = 0;
	tempEnemynameRenderer = tempEnemyname->AddComponent<SpriteRenderer>();
	tempEnemynameRenderer->Size(tempBckgdRenderer->GetHalfWidth() * 2, tempBckgdRenderer->GetHalfHeight() * 2 / 5);
	tempEnemynameRenderer->SetTexture("paddle.png");
	tempEnemynameRenderer->SetLayer(sortingLayer - 1);
	tempEnemynameRenderer->SetColor(0, 1, 0);
	tempEnemyname->transform->SetPosition(Vector2(enemynodepos.x, enemynodepos.y + tempBckgdRenderer->GetHalfHeight() - tempEnemynameRenderer->GetHalfHeight()));

	//nametext
	TextRenderer* tempEnemynameTxtRenderer = 0;
	tempEnemynameTxtRenderer = tempEnemyname->AddComponent<TextRenderer>();
	tempEnemynameTxtRenderer->SetFont("Astral.ttf");
	tempEnemynameTxtRenderer->SetTextColor(0, 0, 0);
	tempEnemynameTxtRenderer->SetText("Test name");
	tempEnemynameTxtRenderer->SetScale(0.5f);
	tempEnemynameTxtRenderer->SetLayer(sortingLayer);
	tempEnemynameTxtRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Left);
	tempEnemynameTxtRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Top);
	//tempEnemynameTxtRenderer->SetXBuffer(70);

	enemynode->AddChild(tempEnemyname);

	//EnemyDescription
	GameObject* tempEnemyDescription = new GameObject();
	SpriteRenderer* tempEnemyDescriptionRenderer = 0;
	tempEnemyDescriptionRenderer = tempEnemyDescription->AddComponent<SpriteRenderer>();
	tempEnemyDescriptionRenderer->Size(tempBckgdRenderer->GetHalfWidth() * 2, tempBckgdRenderer->GetHalfHeight() * 8 / 5);
	tempEnemyDescriptionRenderer->SetTexture("paddle.png");
	tempEnemyDescriptionRenderer->SetLayer(sortingLayer - 1);
	tempEnemyDescriptionRenderer->SetColor(0, 1, 0);
	tempEnemyDescription->transform->SetPosition(Vector2(enemynodepos.x, tempEnemyname->transform->worldposition.y - tempEnemynameRenderer->GetHalfHeight() - tempEnemyDescriptionRenderer->GetHalfHeight()));

	//EnemyDescriptionText
	TextRenderer* tempEnemyDescriptionTxtRenderer = 0;
	tempEnemyDescriptionTxtRenderer = tempEnemyDescription->AddComponent<TextRenderer>();
	tempEnemyDescriptionTxtRenderer->SetFont("Astral.ttf");
	tempEnemyDescriptionTxtRenderer->SetTextColor(0, 0, 0);
	tempEnemyDescriptionTxtRenderer->SetText("Test des");
	tempEnemyDescriptionTxtRenderer->SetScale(0.5f);
	tempEnemyDescriptionTxtRenderer->SetLayer(sortingLayer);
	tempEnemyDescriptionTxtRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Left);
	tempEnemyDescriptionTxtRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Top);
	//tempEnemyDescriptionTxtRenderer->SetXBuffer(70);
	enemynode->AddChild(tempEnemyDescription);

	// Ball artifact
	GameObject* tempBallArtifact = new GameObject();
	SpriteRenderer* tempBallArtifactRenderer = 0;
	tempBallArtifactRenderer = tempBallArtifact->AddComponent<SpriteRenderer>();
	tempBallArtifactRenderer->Size(tempBckgdRenderer->GetHalfWidth() * 2 / 5, tempBckgdRenderer->GetHalfHeight() * 2 / 5);
	tempBallArtifactRenderer->SetTexture("Steven.jpg");
	tempBallArtifactRenderer->SetLayer(sortingLayer - 1);
	tempBallArtifact->transform->SetPosition(Vector2(enemynodepos.x - tempBckgdRenderer->GetHalfWidth() + tempBallArtifactRenderer->GetHalfWidth(), tempEnemyDescription->transform->worldposition.y - tempEnemyDescriptionRenderer->GetHalfHeight() - tempBallArtifactRenderer->GetHalfHeight()));
	enemynode->AddChild(tempBallArtifact);

	float artifactGridWidth = tempBallArtifactRenderer->GetHalfWidth() * 2;
	float artifactGridHeight = tempBallArtifactRenderer->GetHalfHeight() * 2;
	int artifactGridRowCount = 1;
	for (int i = 1; i <= ArtifactTypes + 1; i++) {
		////artifact
		GameObject* tempArtifact = new GameObject();
		SpriteRenderer* tempArtifactRenderer = 0;
		tempArtifactRenderer = tempArtifact->AddComponent<SpriteRenderer>();
		tempArtifactRenderer->Size(artifactGridWidth, artifactGridHeight);
		tempArtifactRenderer->SetTexture("Steven.jpg");
		tempArtifactRenderer->SetLayer(sortingLayer - 1);
		tempArtifact->transform->SetPosition(Vector2(tempBallArtifact->transform->worldposition.x + artifactGridWidth * (i % 5), tempBallArtifact->transform->worldposition.y - artifactGridHeight * (i / 5)));

		//artifactText
		TextRenderer* tempArtifactTxtRenderer = 0;
		tempArtifactTxtRenderer = tempArtifact->AddComponent<TextRenderer>();
		tempArtifactTxtRenderer->SetFont("Astral.ttf");
		tempArtifactTxtRenderer->SetTextColor(0, 0, 0);
		tempArtifactTxtRenderer->SetText("3");
		tempArtifactTxtRenderer->SetScale(0.5f);
		tempArtifactTxtRenderer->SetLayer(sortingLayer);
		tempArtifactTxtRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Right);
		tempArtifactTxtRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Bottom);
		enemynode->AddChild(tempArtifact);
		if (!(i % 5)) {
			artifactGridRowCount++;
		}
	}
	GameObject* tempArtifactBckgd = new GameObject();
	SpriteRenderer* tempArtifactBckgdRenderer = 0;
	tempArtifactBckgdRenderer = tempArtifactBckgd->AddComponent<SpriteRenderer>();
	tempArtifactBckgdRenderer->Size(tempBckgdRenderer->GetHalfWidth() * 2, artifactGridHeight * artifactGridRowCount);
	tempArtifactBckgdRenderer->SetTexture("WhiteTexture.png");
	tempArtifactBckgdRenderer->SetLayer(sortingLayer - 2);
	tempArtifactBckgd->transform->SetPosition(Vector2(enemynodepos.x, enemynodepos.y - tempBckgdRenderer->GetHalfHeight() - tempArtifactBckgdRenderer->GetHalfHeight()));
	enemynode->AddChild(tempArtifactBckgd);
}
void EnemyNodeBox::LoadFromFile(string flag)
{
	string path = "./Assets/Dialogue.txt";

	ifstream input_file(path);
	if (!input_file.is_open()) {
		cerr << "Could not open the file - '"
			<< path << "'" << endl;
		exit(EXIT_FAILURE);
	}

	string input = string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());

	vector<string> inputList;
	stringstream ss = stringstream{ input };
	bool canAdd = false;

	for (string line; getline(ss, line, '\n');)
		inputList.push_back(line);

	for (int i = 0; i < inputList.size(); ++i)
	{
		if (canAdd)
		{
			if (inputList[i] == "")
			{
				descriptNo = 0;
				return;
			}
			else
				descriptList.push_back(inputList[i]);
		}

		if (inputList[i] == flag)
			canAdd = true;
	}
}