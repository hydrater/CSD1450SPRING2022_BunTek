#include "Cursor.h"
#include "BallBehavior.h"
#include "Vector2.h"
#include <stdlib.h>
#include <algorithm>

Cursor::Cursor()
{

}

Cursor::~Cursor()
{

}

void Cursor::Start(void)
{
	
}

void Cursor::Update(void)
{
	//if (AEInputCheckTriggered(AEVK_LBUTTON) == true)
	//{
	//	Clicked = true;
	//}
	//ValidClick = false;
	//signed int X = 0;
	//signed int Y = 0;
	//signed int *x = &X;
	//signed int *y = &Y;
	//if (Clicked == true)
	//{
	//	
	//	//offfset to center
	//	

	//	CursorPosition.Set((float)*x, (float)*y);
	//	BallBehavior* temp = this->Owner()->GetComponent<BallBehavior>();

	//	Vector2 comparisonVector = (CursorPosition - temp->position);
	//	float comparingAngle = comparisonVector.AngleBetween(Vector2(0, 1));	
	//	if (comparisonVector.Length() <= temp->radius)
	//	{
	//		if (comparingAngle <= (temp->clickableAngleRight / 2 + 45 ) && comparingAngle>= (temp->clickableAngleRight / 2 - 45))
	//		{
	//			ValidClick = true;
	//			temp->velocity.x = -temp->velocity.x;
	//		}
	//		else if (comparingAngle <= (temp->clickableAngleLeft / 2 + 45) && comparingAngle >= (temp->clickableAngleLeft / 2 - 45))
	//		{
	//			ValidClick = true;
	//			temp->velocity.x = -temp->velocity.x;
	//		}
	//	}
	//}

	if (AEInputCheckTriggered(AEVK_LBUTTON) == true)
	{
		Vector2 mousePos = GetWorldPosition();

		for (int i = 0; i < ballList.size(); ++i)
		{
			if (ballList[i]->listCheck != 0)
			{
				ballList.erase(ballList.begin() + i);
				--i;
				continue;
			}

			Transform* tempTransform = ballList[i]->Owner()->transform;
			float xDelta = mousePos.x - tempTransform->worldposition.x, yDelta = mousePos.y - tempTransform->worldposition.y;

			

			if (abs(xDelta) <= 50 && abs(yDelta) <= 50)
			{
				float mag = Vector2(xDelta, yDelta).Length();

				if (mag <= 50) {

					cout << "X: " << (mousePos.x - tempTransform->worldposition.x) / mag << " Y: " << (mousePos.y - tempTransform->worldposition.y) / mag << endl;

					ballList[i]->velocity.Set(Vector2(-(mousePos.x - tempTransform->worldposition.x) / mag, -(mousePos.y - tempTransform->worldposition.y) / mag));
				}


			}
		}
	}
}

Vector2 Cursor::GetWorldPosition(void)
{
	AEInputGetCursorPosition(&worldPosition.x, &worldPosition.y);
	return Vector2(worldPosition.x - (float)AEGetWindowWidth() / 2, -(worldPosition.y - (float)AEGetWindowHeight() / 2));
}
