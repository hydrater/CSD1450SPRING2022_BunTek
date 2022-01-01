#include "Cursor.h"
#include "BallBehavior.h"
#include "Vector2.h"

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
}

Vector2 Cursor::GetWorldPosition(void)
{
	AEInputGetCursorPosition(&worldPosition.x, &worldPosition.y);
	return Vector2(worldPosition.x - (float)AEGetWindowWidth() / 2, worldPosition.y - (float)AEGetWindowHeight() / 2);
}
