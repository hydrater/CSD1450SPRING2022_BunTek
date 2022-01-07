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
		CircleCollider* circleCol = (CircleCollider*)col;

		if (col->transform == NULL || transform == NULL)
			return false;

		Vector2 boxPos = transform->worldposition;
		Vector2 vecDist = boxPos.operator-(circleCol->transform->worldposition);

		// Top Left
		Vector2 boxOffset = Vector2(-width / 2, -height / 2);
		boxOffset.Rotate(angle);
		Vector2 boxTopLeft = Vector2(boxPos.x + boxOffset.x, boxPos.y + boxOffset.y);
		// Top Right
		boxOffset = Vector2(width / 2, -height / 2);
		boxOffset.Rotate(angle);
		Vector2 boxTopRight = Vector2(boxPos.x + boxOffset.x, boxPos.y + boxOffset.y);
		// Bottom Left
		boxOffset = Vector2(-width / 2, height / 2);
		boxOffset.Rotate(angle);
		Vector2 boxBottomLeft = Vector2(boxPos.x + boxOffset.x, boxPos.y + boxOffset.y);
		// Bottom Right
		boxOffset = Vector2(width / 2, height / 2);
		boxOffset.Rotate(angle);
		Vector2 boxBottomRight = Vector2(boxPos.x + boxOffset.x, boxPos.y + boxOffset.y);

		Vector2 boxTop = (boxTopRight.operator-(boxTopLeft)).Normalize();
		Vector2 boxSide = (boxBottomLeft.operator-(boxTopLeft)).Normalize();

		float dotproductx = boxTop.Dot(vecDist);
		float dotproducty = boxSide.Dot(vecDist);

		// Check Collision
		if (abs(dotproductx) < width / 2 + circleCol->radius && abs(dotproducty) < height / 2 + circleCol->radius)
			return true;
	}
	//Box-Box collision
	else if (typeid(*col) == typeid(BoxCollider)) {
		if (col->transform == NULL || transform == NULL)
			return false;

		// Box 1
		Vector2 box1Pos = transform->worldposition;
		// Corners
		// Rotate box1 to angle 0
		Vector2 box1Offset = Vector2(-width / 2, -height / 2);
		box1Offset.Rotate(0);
		Vector2 box1TopLeft = Vector2(box1Pos.x + box1Offset.x, box1Pos.y + box1Offset.y);
		box1Offset = Vector2(width / 2, -height / 2);
		box1Offset.Rotate(0);
		Vector2 box1TopRight = Vector2(box1Pos.x + box1Offset.x, box1Pos.y + box1Offset.y);
		box1Offset = Vector2(-width / 2, height / 2);
		box1Offset.Rotate(0);
		Vector2 box1BottomLeft = Vector2(box1Pos.x + box1Offset.x, box1Pos.y + box1Offset.y);
		box1Offset = Vector2(width / 2, height / 2);
		box1Offset.Rotate(0);
		Vector2 box1BottomRight = Vector2(box1Pos.x + box1Offset.x, box1Pos.y + box1Offset.y);

		// Box 2
		// Rotate box2 according box1 angle
		BoxCollider* box2Col = (BoxCollider*)col;
		Vector2 box2Pos = box2Col->transform->worldposition;
		// Corners
		Vector2 box2Offset = Vector2(-box2Col->width / 2, -box2Col->height / 2);
		box2Offset.Rotate(box2Col->angle - angle);
		Vector2 box2TopLeft = Vector2(box2Pos.x + box2Offset.x, box2Pos.y + box2Offset.y);
		box2Offset = Vector2(box2Col->width / 2, -box2Col->height / 2);
		box2Offset.Rotate(box2Col->angle - angle);
		Vector2 box2TopRight = Vector2(box2Pos.x + box2Offset.x, box2Pos.y + box2Offset.y);
		box2Offset = Vector2(-box2Col->width / 2, box2Col->height / 2);
		box2Offset.Rotate(box2Col->angle - angle);
		Vector2 box2BottomLeft = Vector2(box2Pos.x + box2Offset.x, box2Pos.y + box2Offset.y);
		box2Offset = Vector2(box2Col->width / 2, box2Col->height / 2);
		box2Offset.Rotate(box2Col->angle - angle);
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
		if (box1TopLeft.x >= minvec.x && box1TopLeft.x <= maxvec.x || box1TopRight.x >= minvec.x && box1TopRight.x <= maxvec.x
			|| box1TopLeft.x < minvec.x && box1TopRight.x >= minvec.x || box1TopLeft.x <= maxvec.x && box1TopRight.x > maxvec.x)
			box1axis1 = true;
		else if (angle == 0 && box2Col->angle == 45)
		{
			cout << "box1axis1 false" << endl;
			return false;
		}

		// Get box 2 coord projected on axis 2 (box1SideVec); Check for min and max vec
		Vector2 box1SideVec = box1BottomLeft.operator-(box1TopLeft);
		box2TopLeftVec = box2TopLeft;// box1SideVec.operator*(box2TopLeft.Dot(box1SideNorm));
		minvec = box2TopLeftVec;
		maxvec = box2TopLeftVec;
		box2TopRightVec = box2TopRight;// box1SideVec.operator*(box2TopRight.Dot(box1SideNorm));
		minvec = (maxvec.operator-(minvec)).Length() < (maxvec.operator-(box2TopRightVec)).Length() ? box2TopRightVec : minvec;
		maxvec = (maxvec.operator-(minvec)).Length() < (box2TopRightVec.operator-(minvec)).Length() ? box2TopRightVec : maxvec;
		box2BottomLeftVec = box2BottomLeft;// box1SideVec.operator*(box2BottomLeft.Dot(box1SideNorm));
		minvec = (maxvec.operator-(minvec)).Length() < (maxvec.operator-(box2BottomLeftVec)).Length() ? box2BottomLeftVec : minvec;
		maxvec = (maxvec.operator-(minvec)).Length() < (box2BottomLeftVec.operator-(minvec)).Length() ? box2BottomLeftVec : maxvec;
		box2BottomRightVec = box2BottomRight;// box1SideVec.operator*(box2BottomRight.Dot(box1SideNorm));
		minvec = (maxvec.operator-(minvec)).Length() < (maxvec.operator-(box2BottomRightVec)).Length() ? box2BottomRightVec : minvec;
		maxvec = (maxvec.operator-(minvec)).Length() < (box2BottomRightVec.operator-(minvec)).Length() ? box2BottomRightVec : maxvec;
		// Check if the box 1 vectors y value is within min and max vec
		if (box1TopLeft.y >= minvec.y && box1TopLeft.y <= maxvec.y || box1BottomLeft.y >= minvec.y && box1BottomLeft.y <= maxvec.y
			|| box1TopLeft.y < minvec.y && box1BottomLeft.y >= minvec.y || box1TopLeft.y <= maxvec.y && box1BottomLeft.y > maxvec.y)
			box1axis2 = true;
		else if (angle == 0 && box2Col->angle == 45)
		{
			cout << "box1axis2 false" << endl;
			return false;
		}

		// Corners
		// Rotate box1 according box2 angle
		box1Offset = Vector2(-width / 2, -height / 2);
		box1Offset.Rotate(angle - box2Col->angle);
		box1TopLeft = Vector2(box1Pos.x + box1Offset.x, box1Pos.y + box1Offset.y);
		box1Offset = Vector2(width / 2, -height / 2);
		box1Offset.Rotate(angle - box2Col->angle);
		box1TopRight = Vector2(box1Pos.x + box1Offset.x, box1Pos.y + box1Offset.y);
		box1Offset = Vector2(-width / 2, height / 2);
		box1Offset.Rotate(angle - box2Col->angle);
		box1BottomLeft = Vector2(box1Pos.x + box1Offset.x, box1Pos.y + box1Offset.y);
		box1Offset = Vector2(width / 2, height / 2);
		box1Offset.Rotate(angle - box2Col->angle);
		box1BottomRight = Vector2(box1Pos.x + box1Offset.x, box1Pos.y + box1Offset.y);

		// Box 2
		// Rotate box2 angle to 0
		// Corners
		box2Offset = Vector2(-box2Col->width / 2, -box2Col->height / 2);
		box2Offset.Rotate(0);
		box2TopLeft = Vector2(box2Pos.x + box2Offset.x, box2Pos.y + box2Offset.y);
		box2Offset = Vector2(box2Col->width / 2, -box2Col->height / 2);
		box2Offset.Rotate(0);
		box2TopRight = Vector2(box2Pos.x + box2Offset.x, box2Pos.y + box2Offset.y);
		box2Offset = Vector2(-box2Col->width / 2, box2Col->height / 2);
		box2Offset.Rotate(0);
		box2BottomLeft = Vector2(box2Pos.x + box2Offset.x, box2Pos.y + box2Offset.y);
		box2Offset = Vector2(box2Col->width / 2, box2Col->height / 2);
		box2Offset.Rotate(0);
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
		minvec = (maxvec.operator-(minvec)).Length() < (maxvec.operator-(box1TopRightVec)).Length() ? box1TopRightVec : minvec;
		maxvec = (maxvec.operator-(minvec)).Length() < (box1TopRightVec.operator-(minvec)).Length() ? box1TopRightVec : maxvec;
		Vector2 box1BottomLeftVec = box1BottomLeft;// box2TopVec.operator*(box1BottomLeft.Dot(box2TopNorm));
		minvec = (maxvec.operator-(minvec)).Length() < (maxvec.operator-(box1BottomLeftVec)).Length() ? box1BottomLeftVec : minvec;
		maxvec = (maxvec.operator-(minvec)).Length() < (box1BottomLeftVec.operator-(minvec)).Length() ? box1BottomLeftVec : maxvec;
		Vector2 box1BottomRightVec = box1BottomRight;// box2TopVec.operator*(box1BottomRight.Dot(box2TopNorm));
		minvec = (maxvec.operator-(minvec)).Length() < (maxvec.operator-(box1BottomRightVec)).Length() ? box1BottomRightVec : minvec;
		maxvec = (maxvec.operator-(minvec)).Length() < (box1BottomRightVec.operator-(minvec)).Length() ? box1BottomRightVec : maxvec;
		// Check if the box 2 vectors x value is within min and max vec
		if (box2TopLeft.x >= minvec.x && box2TopLeft.x <= maxvec.x || box2TopRight.x >= minvec.x && box2TopRight.x <= maxvec.x
			|| box2TopLeft.x < minvec.x && box2TopRight.x >= minvec.x || box2TopLeft.x <= maxvec.x && box2TopRight.x > maxvec.x)
		{
			cout << "Unwanted true box2axis1" << endl;
			//printf("box1TopLeft: %f | %f \n", box1TopLeft.x, box1TopLeft.y);
			//printf("Dotbox2TopLeft: %f\n", box2TopLeft.Dot(box1TopNorm));
			printf("box1Offset: %f | %f \n", box1Offset.x, box1Offset.y);
			printf("box1TopLeftVec: %f | %f \n", box1TopLeftVec.x, box1TopLeftVec.y);
			printf("box1TopRightVec: %f | %f \n", box1TopRightVec.x, box1TopRightVec.y);
			printf("min: %f | %f \n", minvec.x, minvec.y);
			printf("max: %f | %f \n", maxvec.x, maxvec.y);
			printf("box2Offset: %f | %f \n", box2Offset.x, box2Offset.y);
			printf("box2TopLeft: %f | %f \n", box2TopLeft.x, box2TopLeft.y);
			printf("box2TopRight: %f | %f \n", box2TopRight.x, box2TopRight.y);
			printf("box2TopVec: %f | %f \n", box2TopVec.x, box2TopVec.y);
			box2axis1 = true;
		}
		else if (angle == 0 && box2Col->angle == 45)
		{
			cout << "box2axis1 false" << endl;
			return false;
		}

		// Get box 2 coord projected on axis 2 (box1SideVec); Check for min and max vec
		Vector2 box2SideVec = box2BottomLeft.operator-(box2TopLeft);
		box1TopLeftVec = box1TopLeft;// box2SideVec.operator*(box1TopLeft.Dot(box2SideNorm));
		minvec = box1TopLeftVec;
		maxvec = box1TopLeftVec;
		box1TopRightVec = box1TopRight;// box2SideVec.operator*(box1TopRight.Dot(box2SideNorm));
		minvec = (maxvec.operator-(minvec)).Length() < (maxvec.operator-(box1TopRightVec)).Length() ? box1TopRightVec : minvec;
		maxvec = (maxvec.operator-(minvec)).Length() < (box1TopRightVec.operator-(minvec)).Length() ? box1TopRightVec : maxvec;
		box1BottomLeftVec = box1BottomLeft;// box2SideVec.operator*(box1BottomLeft.Dot(box2SideNorm));
		minvec = (maxvec.operator-(minvec)).Length() < (maxvec.operator-(box1BottomLeftVec)).Length() ? box1BottomLeftVec : minvec;
		maxvec = (maxvec.operator-(minvec)).Length() < (box1BottomLeftVec.operator-(minvec)).Length() ? box1BottomLeftVec : maxvec;
		box1BottomRightVec = box1BottomRight;// box2SideVec.operator*(box1BottomRight.Dot(box2SideNorm));
		minvec = (maxvec.operator-(minvec)).Length() < (maxvec.operator-(box1BottomRightVec)).Length() ? box1BottomRightVec : minvec;
		maxvec = (maxvec.operator-(minvec)).Length() < (box1BottomRightVec.operator-(minvec)).Length() ? box1BottomRightVec : maxvec;
		// Check if the box 1 vectors y value is within min and max vec
		if (box2TopLeft.y >= minvec.y && box2TopLeft.y <= maxvec.y || box2BottomLeft.y >= minvec.y && box2BottomLeft.y <= maxvec.y
			|| box2TopLeft.y < minvec.y && box2BottomLeft.y >= minvec.y || box2TopLeft.y <= maxvec.y && box2BottomLeft.y > maxvec.y)
		{
			box2axis2 = true;
			if (angle == 0 && box2Col->angle == 45)
			{
				cout << "meet" << endl;
			}
		}
		else if (angle == 0 && box2Col->angle == 45)
		{
			cout << "box2axis2 false" << endl;
			return false;
		}

		//// Check Collision
		//if (angle == 0 && box2Col->angle == 45)
		//{
		//	cout << "::::::::::::::::" << endl;
		//	cout << box1axis1 << endl;
		//	cout << box1axis2 << endl;
		//}
		//if (box1axis1 && box1axis2 && angle == 0 && box2Col->angle == 45)
		//{
		//	cout << "============" << endl;
		//	cout << box2axis1 << endl;
		//	cout << box2axis2 << endl;
		//}
		//if (box1axis1 && box1axis2 && box2axis1 && box2axis2 && angle == 0 && box2Col->angle == 45)
		//{
		//	cout << "meet" << endl;
		//	return true;
		//}
	}

	return true;
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

		Vector2 boxPos = col->transform->worldposition;
		Vector2 vecDist = boxPos.operator-(transform->worldposition);

		// Top Left
		Vector2 boxOffset = Vector2(-boxCol->width / 2, -boxCol->height / 2);
		boxOffset.Rotate(boxCol->angle);
		Vector2 boxTopLeft = Vector2(boxPos.x + boxOffset.x, boxPos.y + boxOffset.y);
		// Top Right
		boxOffset = Vector2(boxCol->width / 2, -boxCol->height / 2);
		boxOffset.Rotate(boxCol->angle);
		Vector2 boxTopRight = Vector2(boxPos.x + boxOffset.x, boxPos.y + boxOffset.y);
		// Bottom Left
		boxOffset = Vector2(-boxCol->width / 2, boxCol->height / 2);
		boxOffset.Rotate(boxCol->angle);
		Vector2 boxBottomLeft = Vector2(boxPos.x + boxOffset.x, boxPos.y + boxOffset.y);
		// Bottom Right
		boxOffset = Vector2(boxCol->width / 2, boxCol->height / 2);
		boxOffset.Rotate(boxCol->angle);
		Vector2 boxBottomRight = Vector2(boxPos.x + boxOffset.x, boxPos.y + boxOffset.y);

		Vector2 boxTop = (boxTopRight.operator-(boxTopLeft)).Normalize();
		Vector2 boxSide = (boxBottomLeft.operator-(boxTopLeft)).Normalize();

		float dotproductx = boxTop.Dot(vecDist);
		float dotproducty = boxSide.Dot(vecDist);

		// Check Collision
		if (abs(dotproductx) < boxCol->width/2 + radius && abs(dotproducty) < boxCol->height/2 + radius)
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

// ============ CIRCLE COLLIDER END ============ 
//bool CircleRectCol(CircleGameObject* c1, BoxGameObject* b1, bool doPhysics) {
//
//	Vector2 boxTopLeft = b1->gameObject.position;
//	Vector2 boxTopRight = newVector2(boxTopLeft.x + b1->width * cosf(b1->gameObject.angle / 180 * PI), boxTopLeft.y + b1->width * sinf(b1->gameObject.angle / 180 * PI));
//	Vector2 boxBottomLeft = newVector2(boxTopLeft.x + b1->height * cosf((b1->gameObject.angle + 90) / 180 * PI), boxTopLeft.y + b1->height * sinf((b1->gameObject.angle + 90) / 180 * PI));
//	Vector2 boxBottomRight = newVector2(boxTopLeft.x + b1->width * cosf(b1->gameObject.angle / 180 * PI) + b1->height * cosf((b1->gameObject.angle + 90) / 180 * PI), boxTopLeft.y + b1->width * sinf(b1->gameObject.angle / 180 * PI) + b1->height * sinf((b1->gameObject.angle + 90) / 180 * PI));
//	Vector2 boxCenter = newVector2((boxTopLeft.x + boxBottomRight.x) / 2, (boxTopLeft.y + boxBottomRight.y) / 2);
//
//
//	float boxWidth = b1->width;
//
//
//	float boxHeight = b1->height;
//
//	Vector2 VectorDist = VectorMinus(c1->gameObject.position, boxCenter);
//
//	//Check within X bounds
//	float dotprodx = DotProd(Normalize(VectorMinus(boxTopLeft, boxTopRight)), VectorDist);
//	float dotprody = DotProd(Normalize(VectorMinus(boxTopLeft, boxBottomLeft)), VectorDist);
//
//	// Check if collided
//	bool collided = false;
//
//	if ((dotprodx < boxWidth / 2 + c1->radius && dotprodx > -(boxWidth / 2 + c1->radius)) && (dotprody< boxHeight / 2 + c1->radius && dotprody > -(boxHeight / 2 + c1->radius))) {
//		collided = true;
//	}
//	else {
//		return false;
//	}
//
//	if (collided) {
//		bool collidedLeft = false;
//		bool collidedTop = false;
//
//		bool confirmedX = false;
//		bool confirmedY = false;
//
//
//		if (dotprodx < boxWidth / 2 && dotprodx > -(boxWidth / 2)) {
//			confirmedX = true;
//		}
//		if (dotprodx > 0) {
//			collidedLeft = true;
//		}
//
//
//		if (dotprody < boxHeight / 2 && dotprody > -(boxHeight / 2)) {
//			confirmedY = true;
//		}
//		if (dotprody > 0) {
//			collidedTop = true;
//		}
//
//		//If circle center is inside rect
//		if (confirmedY && confirmedX) {
//			float angbet = (AngBet(c1->gameObject.position, boxCenter) / PI * 180) - b1->gameObject.angle;
//			if (angbet < 0) {
//				angbet += 360;
//			}
//
//			float topAngleRange = atan2f(boxHeight, boxWidth) / PI * 180;
//
//			if (angbet < topAngleRange || angbet >= 270 + (90 - topAngleRange)) {
//				confirmedX = false;
//				confirmedY = true;
//				collidedLeft = false;
//			}
//			else if (angbet >= topAngleRange && angbet < 180 - topAngleRange) {
//				confirmedX = true;
//				confirmedY = false;
//				collidedTop = false;
//			}
//			else if (angbet >= 180 - topAngleRange && angbet < 180 + topAngleRange) {
//				confirmedX = false;
//				confirmedY = true;
//				collidedLeft = true;
//			}
//			else {
//				confirmedX = true;
//				confirmedY = false;
//				collidedTop = true;
//			}
//		}
//
//		if (confirmedX && !confirmedY) {
//			if (!doPhysics) {
//				return true;
//			}
//			if (collidedTop) { // collided on top vertex
//
//				Vector2 NewLocation;
//				Vector2 ReversedBallVelocity = Normalize(VectorMultiply(c1->gameObject.velocity, -1)); // Reversed Velocity of magnitude 1
//
//				float ReversedDotY = DotProd(ReversedBallVelocity, Normalize(VectorMinus(boxTopLeft, boxBottomLeft)));
//
//				float multiplier = 1 / ReversedDotY;
//				ReversedBallVelocity = VectorMultiply(ReversedBallVelocity, multiplier);
//				NewLocation = VectorAdd(c1->gameObject.position, VectorMultiply(ReversedBallVelocity, (boxHeight / 2 + c1->radius) - dotprody));
//
//				// Reflect ball velocity
//				Vector2 newVelocityX = VectorProject(c1->gameObject.velocity, VectorMinus(boxTopRight, boxTopLeft));
//				Vector2 newVelocityY = VectorMultiply(VectorMinus(c1->gameObject.velocity, newVelocityX), -1);
//
//				Vector2 finalVelocity = VectorAdd(newVelocityX, newVelocityY);
//				c1->gameObject.velocity = VectorMultiply(finalVelocity, c1->gameObject.bounciness * b1->gameObject.bounciness);
//				c1->gameObject.position = NewLocation;
//
//				if (debug) {
//					//Draw correct Green location
//					CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
//					CP_Graphics_DrawCircle(NewLocation.x, NewLocation.y, c1->radius * 2);
//				}
//			}
//			else { // collided on bottom vertex
//				Vector2 NewLocation;
//				Vector2 ReversedBallVelocity = Normalize(VectorMultiply(c1->gameObject.velocity, -1)); // Reversed Velocity of magnitude 1
//
//				float ReversedDotY = DotProd(ReversedBallVelocity, Normalize(VectorMinus(boxTopLeft, boxBottomLeft)));
//
//				float multiplier = 1 / ReversedDotY;
//				ReversedBallVelocity = VectorMultiply(ReversedBallVelocity, multiplier);
//				NewLocation = VectorAdd(c1->gameObject.position, VectorMultiply(ReversedBallVelocity, -(boxHeight / 2 + c1->radius) - dotprody));
//
//				// Reflect ball velocity
//				Vector2 newVelocityX = VectorProject(c1->gameObject.velocity, VectorMinus(boxTopLeft, boxTopRight));
//				Vector2 newVelocityY = VectorMultiply(VectorMinus(c1->gameObject.velocity, newVelocityX), -1);
//
//				Vector2 finalVelocity = VectorAdd(newVelocityX, newVelocityY);
//				c1->gameObject.velocity = VectorMultiply(finalVelocity, c1->gameObject.bounciness * b1->gameObject.bounciness);
//				c1->gameObject.position = NewLocation;
//
//				if (debug) {
//					//Draw correct Green location
//					CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
//					CP_Graphics_DrawCircle(NewLocation.x, NewLocation.y, c1->radius * 2);
//				}
//			}
//			return true;
//		}
//		else if (confirmedY && !confirmedX) {
//			if (!doPhysics) {
//				return true;
//			}
//			if (collidedLeft) { //collided on left vertex
//				Vector2 NewLocation;
//				Vector2 ReversedBallVelocity = Normalize(VectorMultiply(c1->gameObject.velocity, -1)); // Reversed Velocity of magnitude 1
//
//				float ReversedDotX = DotProd(ReversedBallVelocity, Normalize(VectorMinus(boxTopLeft, boxTopRight)));
//
//				float multiplier = 1 / ReversedDotX;
//				ReversedBallVelocity = VectorMultiply(ReversedBallVelocity, multiplier);
//				NewLocation = VectorAdd(c1->gameObject.position, VectorMultiply(ReversedBallVelocity, (boxWidth / 2 + c1->radius) - dotprodx));
//
//				// Reflect ball velocity
//				Vector2 newVelocityX = VectorProject(c1->gameObject.velocity, VectorMinus(boxTopLeft, boxBottomLeft));
//				Vector2 newVelocityY = VectorMultiply(VectorMinus(c1->gameObject.velocity, newVelocityX), -1);
//
//				Vector2 finalVelocity = VectorAdd(newVelocityX, newVelocityY);
//				c1->gameObject.velocity = VectorMultiply(finalVelocity, c1->gameObject.bounciness * b1->gameObject.bounciness);
//				c1->gameObject.position = NewLocation;
//
//				if (debug) {
//					//Draw correct Green location
//					CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
//					CP_Graphics_DrawCircle(NewLocation.x, NewLocation.y, c1->radius * 2);
//				}
//			}
//			else { //collided on right vertex
//				Vector2 NewLocation;
//				Vector2 ReversedBallVelocity = Normalize(VectorMultiply(c1->gameObject.velocity, -1)); // Reversed Velocity of magnitude 1
//
//				float ReversedDotX = DotProd(ReversedBallVelocity, Normalize(VectorMinus(boxTopLeft, boxTopRight)));
//
//				float multiplier = 1 / ReversedDotX;
//				ReversedBallVelocity = VectorMultiply(ReversedBallVelocity, multiplier);
//				NewLocation = VectorAdd(c1->gameObject.position, VectorMultiply(ReversedBallVelocity, -(boxWidth / 2 + c1->radius) - dotprodx));
//
//				// Reflect ball velocity
//				Vector2 newVelocityX = VectorProject(c1->gameObject.velocity, VectorMinus(boxBottomLeft, boxTopLeft));
//				Vector2 newVelocityY = VectorMultiply(VectorMinus(c1->gameObject.velocity, newVelocityX), -1);
//
//				Vector2 finalVelocity = VectorAdd(newVelocityX, newVelocityY);
//				c1->gameObject.velocity = VectorMultiply(finalVelocity, c1->gameObject.bounciness * b1->gameObject.bounciness);
//				c1->gameObject.position = NewLocation;
//
//				if (debug) {
//					//Draw correct Green location
//					CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
//					CP_Graphics_DrawCircle(NewLocation.x, NewLocation.y, c1->radius * 2);
//				}
//			}
//			return true;
//		}
//
//		else {
//			if (collidedTop) {
//				if (collidedLeft) {
//					//check top left point for collision
//					if (DistBetweenSquared(boxTopLeft, c1->gameObject.position) < c1->radius * c1->radius) {
//						if (!doPhysics) {
//							return true;
//						}
//						else {
//							//Collided with top left point!
//							CirclePointCol(c1, boxTopLeft, true);
//							return true;
//						}
//					}
//
//				}
//				else {
//					//check top right point for collision
//					if (DistBetweenSquared(boxTopRight, c1->gameObject.position) < c1->radius * c1->radius) {
//						if (!doPhysics) {
//							return true;
//						}
//						else {
//							//Collided with top right point!
//							CirclePointCol(c1, boxTopRight, true);
//							return true;
//						}
//					}
//				}
//			}
//			else {
//				if (collidedLeft) {
//					//check bottom left point for collision
//					if (DistBetweenSquared(boxBottomLeft, c1->gameObject.position) < c1->radius * c1->radius) {
//						if (!doPhysics) {
//							return true;
//						}
//						else {
//							//Collided with bottom Left point!
//							CirclePointCol(c1, boxBottomLeft, true);
//							return true;
//						}
//					}
//				}
//				else {
//					//check bottom right point for collision
//					if (DistBetweenSquared(boxBottomRight, c1->gameObject.position) < c1->radius * c1->radius) {
//						if (!doPhysics) {
//							return true;
//						}
//						else {
//							//Collided with bottom Right point!
//							CirclePointCol(c1, boxBottomRight, true);
//							return true;
//						}
//					}
//				}
//			}
//		}
//	}
//
//	return false;
//}