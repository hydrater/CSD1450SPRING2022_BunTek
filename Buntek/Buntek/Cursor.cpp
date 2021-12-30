#include "Cursor.h"
#include "BallBehavior.h"
#include "Vector2.h"

#define ballbehavior this->Owner()->GetComponent<BallBehavior>()
Cursor::Cursor()
{

}

Cursor::~Cursor()
{

}


void Cursor::Test()
{

}

void Cursor::Start(void)
{
	cout << "monkaS" << endl;
}

void Cursor::Update(void)
{
	ValidClick = false;
	signed int X = 0;
	signed int Y = 0;
	signed int *x = &X;
	signed int *y = &Y;
	if (Clicked == true)
	{
		AEInputGetCursorPosition(x,y);
		CursorPosition.Set((float)*x, (float)*y);
		Vector2 comparisonVector = (CursorPosition - ballbehavior->position);
		float comparingAngle = comparisonVector.AngleBetween(Vector2(0, 1));	
		if (comparisonVector.Length() <= ballbehavior->radius)
		{
			if (comparingAngle <= (ballbehavior->clickableAngleRight / 2 + 90 ) && comparingAngle>= (ballbehavior->clickableAngleRight / 2 - 90))
			{
				ballbehavior->velocity.x = -ballbehavior->velocity.x;
			}
			else if (comparingAngle <= (ballbehavior->clickableAngleLeft / 2 + 270) && comparingAngle >= (ballbehavior->clickableAngleLeft / 2 - 270))
			{
				ballbehavior->velocity.x = -ballbehavior->velocity.x;
			}
		}
	}
}
