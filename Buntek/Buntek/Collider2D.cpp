#include "CollisionManager2D.h"
#include "Collider2D.h"

Collider2D::Collider2D(void)
{
}


Collider2D::~Collider2D(void)
{

}

vector<Vector2> Collider2D::SortMinMax(vector<Vector2> vectors, bool xaxis)
{
	if (vectors.size() <= 0)
	{
		vector<Vector2> nullvec{ Vector2(0,0), Vector2(0,0) };
		return nullvec;
	}
	vector<Vector2> minmax{ vectors[0], vectors[0] };
	for (int i = 1; i < vectors.size(); ++i)
	{
		// check min max for x axis
		if (xaxis)
		{
			minmax[0] = minmax[0].x > vectors[i].x ? vectors[i] : minmax[0];
			minmax[1] = minmax[1].x < vectors[i].x ? vectors[i] : minmax[1];
		}
		// check min max for y axis
		else
		{
			minmax[0] = minmax[0].y > vectors[i].y ? vectors[i] : minmax[0];
			minmax[1] = minmax[1].y < vectors[i].y ? vectors[i] : minmax[1];
		}
	}
	return minmax;
}

vector<Vector2> Collider2D::GetRectCorners(Vector2 pos, float width, float height, float angle)
{
	Vector2 Offset = Vector2(-width / 2, height / 2);
	Offset.RotateAC(angle);
	Vector2 TopLeft = Vector2(pos.x + Offset.x, pos.y + Offset.y);
	Offset = Vector2(width / 2, height / 2);
	Offset.RotateAC(angle);
	Vector2 TopRight = Vector2(pos.x + Offset.x, pos.y + Offset.y);
	Offset = Vector2(-width / 2, -height / 2);
	Offset.RotateAC(angle);
	Vector2 BottomLeft = Vector2(pos.x + Offset.x, pos.y + Offset.y);
	Offset = Vector2(width / 2, -height / 2);
	Offset.RotateAC(angle);
	Vector2 BottomRight = Vector2(pos.x + Offset.x, pos.y + Offset.y);
	vector<Vector2>corners{TopLeft, TopRight, BottomLeft, BottomRight};
	return corners;
}

//void Collider2D::UpdateDimension(void)
//{
//	if (this != NULL)
//	{
//		transform = this->Owner()->transform;
//		if (transform != NULL) {
//			angle = transform->worldrotation;
//		}
//		else {
//			angle = 0.0f;
//		}
//		
//		if (this->Owner()->transform != NULL) {
//			scale.x = this->Owner()->transform->localscale.x;
//			scale.y = this->Owner()->transform->localscale.y;
//		}
//		else {
//			scale.x = 1;
//			scale.y = 1;
//		}
//	}
//}







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

		// Update dimensions of the width, height, angle and/or radius
		SpriteRenderer* thissr = this->Owner()->GetComponent<SpriteRenderer>();
		SpriteRenderer* othersr = CirCol->Owner()->GetComponent<SpriteRenderer>();
		width = thissr->GetHalfWidth() * 2;
		height = thissr->GetHalfHeight() * 2;
		angle = this->Owner()->transform->worldrotation;
		CirCol->radius = othersr->GetHalfWidth() + othersr->GetHalfHeight();
		CirCol->angle = CirCol->Owner()->transform->worldrotation;

		Vector2 boxPos = transform->worldposition;
		Vector2 vecDist = boxPos.operator-(CirCol->transform->worldposition);

		// Rotate Circle according to boxPos
		vecDist.RotateAC(angle);
		Vector2 rotCircle = boxPos.operator+(vecDist);

		// Check Collision
		if (abs(rotCircle.x - boxPos.x) < (CirCol->radius + width / 2) && abs(rotCircle.y - boxPos.y) < (CirCol->radius + height / 2))
			return true;
	}
	//Box-Box collision
	else if (typeid(*col) == typeid(BoxCollider)) {
		if (col->transform == NULL || transform == NULL)
			return false;

		BoxCollider* box2Col = (BoxCollider*)col;

		// Update dimensions of the width, height and angle
		SpriteRenderer* thissr = this->Owner()->GetComponent<SpriteRenderer>();
		SpriteRenderer* othersr = box2Col->Owner()->GetComponent<SpriteRenderer>();
		width = thissr->GetHalfWidth() * 2;
		height = thissr->GetHalfHeight() * 2;
		angle = this->Owner()->transform->worldrotation;
		box2Col->width = othersr->GetHalfWidth() * 2;
		box2Col->height = othersr->GetHalfHeight() * 2;
		box2Col->angle = box2Col->Owner()->transform->worldrotation;

		// Collision Method (Seperating Axis Theorem)
		// Box 1
		Vector2 box1Pos = transform->worldposition;
		vector<Vector2> box1Cor = GetRectCorners(box1Pos, width, height, 0);

		// Box 2
		Vector2 box2Pos = box2Col->transform->worldposition;
		// Rotate box2 according box1 angle
		box2Pos = box2Pos.operator-(box1Pos);
		box2Pos.RotateAC(angle);
		box2Pos = box1Pos.operator+(box2Pos);
		vector<Vector2> box2Cor = GetRectCorners(box2Pos, box2Col->width, box2Col->height, -box2Col->angle + angle);

		// Sort minmax at x Axis based on the box
		vector<Vector2> box1minmax = SortMinMax(box1Cor, true); //MinCoord
		vector<Vector2> box2minmax = SortMinMax(box2Cor, true); //minvec
		// Check if it overlaps
		if (!(box1minmax[0].x >= box2minmax[0].x && box1minmax[0].x <= box2minmax[1].x || box1minmax[1].x >= box2minmax[0].x && box1minmax[1].x <= box2minmax[1].x
			|| box1minmax[0].x < box2minmax[0].x && box1minmax[1].x >= box2minmax[0].x || box1minmax[0].x <= box2minmax[1].x && box1minmax[1].x > box2minmax[1].x))
			return false;

		// Sort minmax at y Axis based on the box
		box1minmax = SortMinMax(box1Cor, false); //MinCoord
		box2minmax = SortMinMax(box2Cor, false); //minvec

		if (!(box1minmax[0].y >= box2minmax[0].y && box1minmax[0].y <= box2minmax[1].y || box1minmax[1].y >= box2minmax[0].y && box1minmax[1].y <= box2minmax[1].y
			|| box1minmax[0].y < box2minmax[0].y && box1minmax[1].y >= box2minmax[0].y || box1minmax[0].y <= box2minmax[1].y && box1minmax[1].y > box2minmax[1].y))
			return false;
		
		//==============================

		// Box 1 (Reset box2Pos)
		box1Pos = transform->worldposition;
		box2Pos = box2Col->transform->worldposition;
		// Rotate box1 according box2 angle
		box1Pos = box1Pos.operator-(box2Pos);
		box1Pos.RotateAC(box2Col->angle);
		box1Pos = box2Pos.operator+(box1Pos);
		box1Cor = GetRectCorners(box1Pos, width, height, -angle + box2Col->angle);

		// Box 2
		box2Pos = box2Col->transform->worldposition;
		box2Cor = GetRectCorners(box2Pos, box2Col->width, box2Col->height, 0);

		// Sort minmax at x Axis based on the box
		box1minmax = SortMinMax(box1Cor, true); //minvec
		box2minmax = SortMinMax(box2Cor, true); //MinCoord

		if (!(box2minmax[0].x >= box1minmax[0].x && box2minmax[0].x <= box1minmax[1].x || box2minmax[1].x >= box1minmax[0].x && box2minmax[1].x <= box1minmax[1].x
			|| box2minmax[0].x < box1minmax[0].x && box2minmax[1].x >= box1minmax[0].x || box2minmax[0].x <= box1minmax[1].x && box2minmax[1].x > box1minmax[1].x))
			return false;
		
		// Sort minmax at y Axis based on the box
		box1minmax = SortMinMax(box1Cor, false); //minvec
		box2minmax = SortMinMax(box2Cor, false); //MinCoord

		if (!(box2minmax[0].y >= box1minmax[0].y && box2minmax[0].y <= box1minmax[1].y || box2minmax[1].y >= box1minmax[0].y && box2minmax[1].y <= box1minmax[1].y
			|| box2minmax[0].y < box1minmax[0].y && box2minmax[1].y >= box1minmax[0].y || box2minmax[0].y <= box1minmax[1].y && box2minmax[1].y > box1minmax[1].y))
			return false;

		return true;
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
		if (col->transform == NULL || transform == NULL)
			return false;

		CircleCollider* other = (CircleCollider*)col;
		
		// Update dimensions of the width, height and/or radius
		SpriteRenderer* thissr = this->Owner()->GetComponent<SpriteRenderer>();
		SpriteRenderer* othersr = other->Owner()->GetComponent<SpriteRenderer>();
		radius = thissr->GetHalfWidth() * 2 + thissr->GetHalfHeight() * 2;
		angle = this->Owner()->transform->worldrotation;
		other->radius = othersr->GetHalfWidth() * 2 + othersr->GetHalfHeight() * 2;
		other->angle = other->Owner()->transform->worldrotation;

		float Dist2 = (radius + other->radius)* (radius + other->radius);

		if ((this->Owner()->transform->worldposition- other->Owner()->transform->worldposition).LengthSquared() <= Dist2 ) {
			
			return true;
		}
		
	}
	//Circle-Box collision
	else if (typeid(*col) == typeid(BoxCollider)) {
		if (col->transform == NULL || transform == NULL)
			return false;

		BoxCollider* boxCol = (BoxCollider*)col;

		// Update dimensions of the width, height and/or radius
		SpriteRenderer* thissr = this->Owner()->GetComponent<SpriteRenderer>();
		SpriteRenderer* othersr = boxCol->Owner()->GetComponent<SpriteRenderer>();
		radius = thissr->GetHalfWidth() * 2 + thissr->GetHalfHeight() * 2;
		angle = this->Owner()->transform->worldrotation;
		boxCol->width = othersr->GetHalfWidth() * 2;
		boxCol->height = othersr->GetHalfHeight() * 2;
		boxCol->angle = boxCol->Owner()->transform->worldrotation;

		Vector2 boxPos = boxCol->transform->worldposition;
		Vector2 vecDist = boxPos.operator-(transform->worldposition);

		// Rotate Circle according to boxPos
		vecDist.RotateAC(boxCol->angle);
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