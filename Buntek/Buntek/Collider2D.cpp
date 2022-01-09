#include "CollisionManager2D.h"
#include "Collider2D.h"

Collider2D::Collider2D(void)
{
}


Collider2D::~Collider2D(void)
{

}

void Collider2D::UpdateDimension(void)
{
	if (this != NULL)
	{
		transform = this->Owner()->transform;
		if (transform != NULL) {
			angle = transform->worldrotation;
		}
		else {
			angle = 0.0f;
		}

		SpriteRenderer* _sr = this->Owner()->GetComponent<SpriteRenderer>();
		if (_sr != NULL) {
			width = _sr->GetHalfWidth() * 2;
			height = _sr->GetHalfHeight() * 2;
			radius = _sr->GetHalfWidth() + _sr->GetHalfHeight();
		}
		else {
			width = 100;
			height = 100;
			radius = 50;
		}
	}
}

bool Collider2D::Collide(Collider2D col)
{
	return false;
}

// ============ BOX COLLIDER ============ 
BoxCollider::BoxCollider()
{
	CollisionManager2D.AddToList(this);
}

bool BoxCollider::Collide(Collider2D* col)
{
	//Box-Circle collision
	if (typeid(*col) == typeid(CircleCollider)) {
		CircleCollider* CirCol = (CircleCollider*)col;

		if (col->transform == NULL || transform == NULL)
			return false;

		Vector2 boxPos = transform->worldposition;
		Vector2 vecDist = boxPos.operator-(CirCol->transform->worldposition);

		// Rotate Circle according to boxPos
		vecDist.Rotate(-angle);
		Vector2 rotCircle = boxPos.operator+(vecDist);

		// Check Collision
		if (abs(rotCircle.x - boxPos.x) < CirCol->radius + width / 2 && abs(rotCircle.y - boxPos.y) < CirCol->radius + height / 2)
			return true;
	}
	//Box-Box collision
	else if (typeid(*col) == typeid(BoxCollider)) {
		if (col->transform == NULL || transform == NULL)
			return false;

		// Box 1
		Vector2 box1Pos = transform->worldposition;
		BoxCollider* box2Col = (BoxCollider*)col;
		Vector2 box2Pos = box2Col->transform->worldposition;
		// Corners
		// Rotate box1 to angle 0
		Vector2 box1Offset = Vector2(-width / 2, height / 2);
		Vector2 box1TopLeft = Vector2(box1Pos.x + box1Offset.x, box1Pos.y + box1Offset.y);
		box1Offset = Vector2(width / 2, height / 2);
		Vector2 box1TopRight = Vector2(box1Pos.x + box1Offset.x, box1Pos.y + box1Offset.y);
		box1Offset = Vector2(-width / 2, -height / 2);
		Vector2 box1BottomLeft = Vector2(box1Pos.x + box1Offset.x, box1Pos.y + box1Offset.y);
		box1Offset = Vector2(width / 2, -height / 2);
		Vector2 box1BottomRight = Vector2(box1Pos.x + box1Offset.x, box1Pos.y + box1Offset.y);

		// Box 2
		// Rotate box2 according box1 angle
		box2Pos = box2Pos.operator-(box1Pos);
		box2Pos.Rotate(angle);
		box2Pos = box1Pos.operator+(box2Pos);
		// Corners
		Vector2 box2Offset = Vector2(-box2Col->width / 2, box2Col->height / 2);
		box2Offset.Rotate(-box2Col->angle + angle);
		Vector2 box2TopLeft = Vector2(box2Pos.x + box2Offset.x, box2Pos.y + box2Offset.y);
		box2Offset = Vector2(box2Col->width / 2, box2Col->height / 2);
		box2Offset.Rotate(-box2Col->angle + angle);
		Vector2 box2TopRight = Vector2(box2Pos.x + box2Offset.x, box2Pos.y + box2Offset.y);
		box2Offset = Vector2(-box2Col->width / 2, -box2Col->height / 2);
		box2Offset.Rotate(-box2Col->angle + angle);
		Vector2 box2BottomLeft = Vector2(box2Pos.x + box2Offset.x, box2Pos.y + box2Offset.y);
		box2Offset = Vector2(box2Col->width / 2, -box2Col->height / 2);
		box2Offset.Rotate(-box2Col->angle + angle);
		Vector2 box2BottomRight = Vector2(box2Pos.x + box2Offset.x, box2Pos.y + box2Offset.y);

		// Get each box corners for length (Seperating Axis Theorem)
		// Box 1 Axis
		Vector2 box1TopNorm = (box1TopRight.operator-(box1TopLeft)).Normalize();
		Vector2 box1SideNorm = (box1BottomLeft.operator-(box1TopLeft)).Normalize();
		bool box1axis1 = false;
		bool box1axis2 = false;
		// Get box 2 coord projected on axis 1 (box1TopVec); Check for min and max vec
		Vector2 box1TopVec = box1TopRight.operator-(box1TopLeft);
		Vector2 box2TopLeftVec = box2TopLeft;// box1TopVec.operator*(box2TopLeft.Dot(box1TopNorm));
		Vector2 minvec = box2TopLeftVec;
		Vector2 maxvec = box2TopLeftVec;
		Vector2 box2TopRightVec = box2TopRight;// box1TopVec.operator*(box2TopRight.Dot(box1TopNorm));
		minvec = minvec.x > box2TopRightVec.x ? box2TopRightVec : minvec;
		maxvec = maxvec.x < box2TopRightVec.x ? box2TopRightVec : maxvec;
		Vector2 box2BottomLeftVec = box2BottomLeft;// box1TopVec.operator*(box2BottomLeft.Dot(box1TopNorm));
		minvec = minvec.x > box2BottomLeftVec.x ? box2BottomLeftVec : minvec;
		maxvec = maxvec.x < box2BottomLeftVec.x ? box2BottomLeftVec : maxvec;
		Vector2 box2BottomRightVec = box2BottomRight;// box1TopVec.operator*(box2BottomRight.Dot(box1TopNorm));
		minvec = minvec.x > box2BottomRightVec.x ? box2BottomRightVec : minvec;
		maxvec = maxvec.x < box2BottomRightVec.x ? box2BottomRightVec : maxvec;
		// Check if the box 1 vectors x value is within min and max vec
		Vector2 MinCoord = box1TopLeft;
		Vector2 MaxCoord = box1TopRight;
		if (MinCoord.x > MaxCoord.x)
		{
			Vector2 tempvec = MinCoord;
			MinCoord = MaxCoord;
			MaxCoord = tempvec;
		}
		if (MinCoord.x >= minvec.x && MinCoord.x <= maxvec.x || MaxCoord.x >= minvec.x && MaxCoord.x <= maxvec.x
			|| MinCoord.x < minvec.x && MaxCoord.x >= minvec.x || MinCoord.x <= maxvec.x && MaxCoord.x > maxvec.x)
			box1axis1 = true;
		else
		{
			if (angle != 1 && box2Col->angle != 1)
			{
				cout << "box1axis1 false" << endl;
			}
			return false;
		}

		// Get box 2 coord projected on axis 2 (box1SideVec); Check for min and max vec
		Vector2 box1SideVec = box1BottomLeft.operator-(box1TopLeft);
		box2TopLeftVec = box2TopLeft;// box1SideVec.operator*(box2TopLeft.Dot(box1SideNorm));
		minvec = box2TopLeftVec;
		maxvec = box2TopLeftVec;
		box2TopRightVec = box2TopRight;// box1SideVec.operator*(box2TopRight.Dot(box1SideNorm));
		minvec = minvec.y > box2TopRightVec.y ? box2TopRightVec : minvec;
		maxvec = maxvec.y < box2TopRightVec.y ? box2TopRightVec : maxvec;
		box2BottomLeftVec = box2BottomLeft;// box1SideVec.operator*(box2BottomLeft.Dot(box1SideNorm));
		minvec = minvec.y > box2BottomLeftVec.y ? box2BottomLeftVec : minvec;
		maxvec = maxvec.y < box2BottomLeftVec.y ? box2BottomLeftVec : maxvec;
		box2BottomRightVec = box2BottomRight;// box1SideVec.operator*(box2BottomRight.Dot(box1SideNorm));
		minvec = minvec.y > box2BottomRightVec.y ? box2BottomRightVec : minvec;
		maxvec = maxvec.y < box2BottomRightVec.y ? box2BottomRightVec : maxvec;
		// Check if the box 1 vectors y value is within min and max vec
		MinCoord = box1TopLeft;
		MaxCoord = box1BottomLeft;
		if (MinCoord.y > MaxCoord.y)
		{
			Vector2 tempvec = MinCoord;
			MinCoord = MaxCoord;
			MaxCoord = tempvec;
		}
		if (MinCoord.y >= minvec.y && MinCoord.y <= maxvec.y || MaxCoord.y >= minvec.y && MaxCoord.y <= maxvec.y
			|| MinCoord.y < minvec.y && MaxCoord.y >= minvec.y || MinCoord.y <= maxvec.y && MaxCoord.y > maxvec.y)
			box1axis2 = true;
		else
		{
			if (angle != 1 && box2Col->angle != 1)
			{
				cout << "box1axis2 false" << endl;
			}
			return false;
		}

		// Box 1
		box1Pos = transform->worldposition;
		box2Pos = box2Col->transform->worldposition;
		//===
		box1Pos = box1Pos.operator-(box2Pos);
		box1Pos.Rotate(box2Col->angle);
		box1Pos = box2Pos.operator+(box1Pos);

		// Corners
		// Rotate box1 according box2 angle
		box1Offset = Vector2(-width / 2, height / 2);
		box1Offset.Rotate(-angle + box2Col->angle);
		box1TopLeft = Vector2(box1Pos.x + box1Offset.x, box1Pos.y + box1Offset.y);
		box1Offset = Vector2(width / 2, height / 2);
		box1Offset.Rotate(-angle + box2Col->angle);
		box1TopRight = Vector2(box1Pos.x + box1Offset.x, box1Pos.y + box1Offset.y);
		box1Offset = Vector2(-width / 2, -height / 2);
		box1Offset.Rotate(-angle + box2Col->angle);
		box1BottomLeft = Vector2(box1Pos.x + box1Offset.x, box1Pos.y + box1Offset.y);
		box1Offset = Vector2(width / 2, -height / 2);
		box1Offset.Rotate(-angle + box2Col->angle);
		box1BottomRight = Vector2(box1Pos.x + box1Offset.x, box1Pos.y + box1Offset.y);

		// Box 2
		box2Pos = box2Col->transform->worldposition;
		// Rotate box2 angle to 0
		// Corners
		box2Offset = Vector2(-box2Col->width / 2, box2Col->height / 2);
		box2TopLeft = Vector2(box2Pos.x + box2Offset.x, box2Pos.y + box2Offset.y);
		box2Offset = Vector2(box2Col->width / 2, box2Col->height / 2);
		box2TopRight = Vector2(box2Pos.x + box2Offset.x, box2Pos.y + box2Offset.y);
		box2Offset = Vector2(-box2Col->width / 2, -box2Col->height / 2);
		box2BottomLeft = Vector2(box2Pos.x + box2Offset.x, box2Pos.y + box2Offset.y);
		box2Offset = Vector2(box2Col->width / 2, -box2Col->height / 2);
		box2BottomRight = Vector2(box2Pos.x + box2Offset.x, box2Pos.y + box2Offset.y);

		// Get each box corners for length (Seperating Axis Theorem)
		// Box 2 Axis
		Vector2 box2TopNorm = (box2TopRight.operator-(box2TopLeft)).Normalize();
		Vector2 box2SideNorm = (box2BottomLeft.operator-(box2TopLeft)).Normalize();
		bool box2axis1 = false;
		bool box2axis2 = false;
		// Get box 1 coord projected on axis 1 (box2TopVec); Check for min and max vec
		Vector2 box2TopVec = box2TopRight.operator-(box2TopLeft);
		Vector2 box1TopLeftVec = box1TopLeft;// box2TopVec.operator*(box1TopLeft.Dot(box2TopNorm));
		minvec = box1TopLeftVec;
		maxvec = box1TopLeftVec;
		Vector2 box1TopRightVec = box1TopRight;// box2TopVec.operator*(box1TopRight.Dot(box2TopNorm));
		minvec = minvec.x > box1TopRightVec.x ? box1TopRightVec : minvec;
		maxvec = maxvec.x < box1TopRightVec.x ? box1TopRightVec : maxvec;
		Vector2 box1BottomLeftVec = box1BottomLeft;// box2TopVec.operator*(box1BottomLeft.Dot(box2TopNorm));
		minvec = minvec.x > box1BottomLeftVec.x ? box1BottomLeftVec : minvec;
		maxvec = maxvec.x < box1BottomLeftVec.x ? box1BottomLeftVec : maxvec;
		Vector2 box1BottomRightVec = box1BottomRight;// box2TopVec.operator*(box1BottomRight.Dot(box2TopNorm));
		minvec = minvec.x > box1BottomRightVec.x ? box1BottomRightVec : minvec;
		maxvec = maxvec.x < box1BottomRightVec.x ? box1BottomRightVec : maxvec;
		// Check if the box 2 vectors x value is within min and max vec
		MinCoord = box2TopLeft;
		MaxCoord = box2TopRight;
		if (MinCoord.x > MaxCoord.x)
		{
			Vector2 tempvec = MinCoord;
			MinCoord = MaxCoord;
			MaxCoord = tempvec;
		}
		if (MinCoord.x >= minvec.x && MinCoord.x <= maxvec.x || MaxCoord.x >= minvec.x && MaxCoord.x <= maxvec.x
			|| MinCoord.x < minvec.x && MaxCoord.x >= minvec.x || MinCoord.x <= maxvec.x && MaxCoord.x > maxvec.x)
		{
			box2axis1 = true;
			//if (angle != 1 && box2Col->angle != 1)
			//	{
			//		//cout << "box2axis1 true" << endl;
			//		box1Offset = Vector2(transform->worldposition.operator-(box2Col->transform->worldposition));
			//		printf("box1box2vec: %f | %f\n", box1Offset.x, box1Offset.y);
			//		printf("Angle: %f\n", -box2Col->angle);
			//		box1Offset.Rotate(-box2Col->angle);
			//		printf("box1Offset: %f | %f\n", box1Offset.x, box1Offset.y);
			//		printf("Oribox1Pos: %f | %f\n", transform->worldposition.x, transform->worldposition.y);
			//		printf("Oribox2Pos: %f | %f\n", box2Col->transform->worldposition.x, box2Col->transform->worldposition.y);
			//		printf("box1Pos: %f | %f\n", box1Pos.x, box1Pos.y);
			//		printf("box2Pos: %f | %f\n", box2Pos.x, box2Pos.y);
			//		printf("box2TopLeft: %f | %f\n", box2TopLeft.x, box2TopLeft.y);
			//		printf("box2TopRight: %f | %f\n", box2TopRight.x, box2TopRight.y);
			//		printf("MinCoord: %f | %f\n", MinCoord.x, MinCoord.y);
			//		printf("MaxCoord: %f | %f\n", MaxCoord.x, MaxCoord.y);
			//		printf("minvec: %f | %f\n", minvec.x, minvec.y);
			//		printf("maxvec: %f | %f\n", maxvec.x, maxvec.y);
			//		printf("box1TopLeftVec: %f | %f\n", box1TopLeftVec.x, box1TopLeftVec.y);
			//		printf("box1TopRightVec: %f | %f\n", box1TopRightVec.x, box1TopRightVec.y);
			//		printf("box1BottomLeftVec: %f | %f\n", box1BottomLeftVec.x, box1BottomLeftVec.y);
			//		printf("box1BottomRightVec: %f | %f\n", box1BottomRightVec.x, box1BottomRightVec.y);
			//	}
		}
		else
		{
			if (angle != 1 && box2Col->angle != 1)
			{
				cout << "box2axis1 false" << endl;
			}
			return false;
		}

		// Get box 2 coord projected on axis 2 (box1SideVec); Check for min and max vec
		Vector2 box2SideVec = box2BottomLeft.operator-(box2TopLeft);
		box1TopLeftVec = box1TopLeft;// box2SideVec.operator*(box1TopLeft.Dot(box2SideNorm));
		minvec = box1TopLeftVec;
		maxvec = box1TopLeftVec;
		box1TopRightVec = box1TopRight;// box2SideVec.operator*(box1TopRight.Dot(box2SideNorm));
		minvec = minvec.y > box1TopRightVec.y ? box1TopRightVec : minvec;
		maxvec = maxvec.y < box1TopRightVec.y ? box1TopRightVec : maxvec;
		box1BottomLeftVec = box1BottomLeft;// box2SideVec.operator*(box1BottomLeft.Dot(box2SideNorm));
		minvec = minvec.y > box1BottomLeftVec.y ? box1BottomLeftVec : minvec;
		maxvec = maxvec.y < box1BottomLeftVec.y ? box1BottomLeftVec : maxvec;
		box1BottomRightVec = box1BottomRight;// box2SideVec.operator*(box1BottomRight.Dot(box2SideNorm));
		minvec = minvec.y > box1BottomRightVec.y ? box1BottomRightVec : minvec;
		maxvec = maxvec.y < box1BottomRightVec.y ? box1BottomRightVec : maxvec;
		// Check if the box 1 vectors y value is within min and max vec
		MinCoord = box2TopLeft;
		MaxCoord = box2BottomLeft;
		if (MinCoord.y > MaxCoord.y)
		{
			Vector2 tempvec = MinCoord;
			MinCoord = MaxCoord;
			MaxCoord = tempvec;
		}
		if (MinCoord.y >= minvec.y && MinCoord.y <= maxvec.y || MaxCoord.y >= minvec.y && MaxCoord.y <= maxvec.y
			|| MinCoord.y < minvec.y && MaxCoord.y >= minvec.y || MinCoord.y <= maxvec.y && MaxCoord.y > maxvec.y)
		{
			box2axis2 = true;
			cout << "~~~~~~~~" << endl;
			cout << "meet" << endl;
			return true;
		}
		else
		{
			if (angle != 1 && box2Col->angle != 1)
			{
				cout << "box2axis2 false" << endl;
			}
			return false;
		}
	}

	return false;
}


BoxCollider::~BoxCollider(void)
{

}
// ============ BOX COLLIDER END ============ 

// ============ CIRCLE COLLIDER ============ 
CircleCollider::CircleCollider(void)
{
	CollisionManager2D.AddToList(this);
}

bool CircleCollider::Collide(Collider2D* col)
{
	//Circle-Circle collision
	if (typeid(*col) == typeid(CircleCollider)) {
		CircleCollider* other = (CircleCollider*)col;
		
		float Dist2 = (radius + other->radius)* (radius + other->radius);

		if ((this->Owner()->transform->worldposition- other->Owner()->transform->worldposition).LengthSquared() <= Dist2 ) {
			
			return true;
		}
		
	}
	//Circle-Box collision
	else if (typeid(*col) == typeid(BoxCollider)) {

		BoxCollider* boxCol = (BoxCollider*)col;

		if (col->transform == NULL || transform == NULL)
			return false;

		Vector2 boxPos = boxCol->transform->worldposition;
		Vector2 vecDist = boxPos.operator-(transform->worldposition);

		// Rotate Circle according to boxPos
		vecDist.Rotate(-boxCol->angle);
		Vector2 rotCircle = boxPos.operator+(vecDist);

		// Check Collision
		if (abs(rotCircle.x - boxPos.x) < radius + boxCol->width / 2 && abs(rotCircle.y - boxPos.y) < radius + boxCol->height / 2)
			return true;
	}

	return false;
}
CircleCollider::~CircleCollider(void)
{

}

// ============ CIRCLE COLLIDER END ============ 

// ============ LINE COLLIDER ============ 
LineCollider::LineCollider(void)
{
	/*
	SpriteRenderer* _sr = this->gameObject->GetComponent<SpriteRenderer>();
	if (_sr != NULL) {
		radius = _sr->GetHalfWidth() + _sr->GetHalfHeight();
	}
	else {
		radius = 50;
	}
	*/
	
	CollisionManager2D.AddToList(this);
}

bool LineCollider::Collide(Collider2D* col)
{
	//Line-Line collision
	if (typeid(*col) == typeid(LineCollider)) {
		LineCollider* other = (LineCollider*)col;
		Vector2 a = point1;
		Vector2 b = point2;

		Vector2 c = other->point1;
		Vector2 d = other->point2;

		float denominator = ((b.x - a.x) * (d.y - c.y)) - ((b.y - a.y) * (d.x - c.x));
		float numerator1 = ((a.y - c.y) * (d.x - c.x)) - ((a.x - c.x) * (d.y - c.y));
		float numerator2 = ((a.y - c.y) * (b.x - a.x)) - ((a.x - c.x) * (b.y - a.y));

		// Detect coincident lines (has a problem, read below)
		if (denominator == 0) return numerator1 == 0 && numerator2 == 0;

		float r = numerator1 / denominator;
		float s = numerator2 / denominator;

		return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);

	}
	//Circle-Box collision
	else if (typeid(*col) == typeid(BoxCollider)) {

	}

	return false;
}
LineCollider::~LineCollider(void)
{

}