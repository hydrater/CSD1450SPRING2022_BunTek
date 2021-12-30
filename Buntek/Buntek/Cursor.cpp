#include "Cursor.h"
#include "BallBehavior.h"
#include "Vector2.h"
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
	signed int* x;
	signed int* y;
	*x = 0;
	*y = 0;
	if (Clicked == true)
	{
		AEInputGetCursorPosition(x,y);
		CursorPosition.Set(*x, *y);
		Vector2 comparisonVector = (CursorPosition - BallBehavior().position);
		float comparingAngle = comparisonVector.AngleBetween(Vector2(0, 1));	
		if (comparisonVector.Length() <= BallBehavior().radius)
		{
			if (comparingAngle <= BallBehavior().clickableAngleRight + 45  && comparingAngle>= BallBehavior().clickableAngleRight - 45)
			{
				=
			}
			else if (comparingAngle <= BallBehavior().clickableAngleLeft + 35 && comparingAngle >= BallBehavior().clickableAngleLeft - 45)
			{

			}
		}
	}
}
