#include "CollisionManager2D.h"
#include "Collider2D.h"

Collider2D::Collider2D(void)
{
}


Collider2D::~Collider2D(void)
{

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

void BoxCollider::UpdateDimension(void)
{
	if (transform != NULL) {
		angle = transform->worldrotation;
	}
	else {
		angle = 0.0f;
	}

	SpriteRenderer* _sr = this->gameObject->GetComponent<SpriteRenderer>();
	if (_sr != NULL) {
		width = _sr->GetHalfWidth() * 2;
		height = _sr->GetHalfHeight() * 2;
	}
	else {
		width = 100;
		height = 100;
	}
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
		// Top Left
		Vector2 box1Offset = Vector2(-width / 2, -height / 2);
		box1Offset.Rotate(angle);
		Vector2 box1TopLeft = Vector2(box1Pos.x + box1Offset.x, box1Pos.y + box1Offset.y);
		// Top Right
		box1Offset = Vector2(width / 2, -height / 2);
		box1Offset.Rotate(angle);
		Vector2 box1TopRight = Vector2(box1Pos.x + box1Offset.x, box1Pos.y + box1Offset.y);
		// Bottom Left
		box1Offset = Vector2(-width / 2, height / 2);
		box1Offset.Rotate(angle);
		Vector2 box1BottomLeft = Vector2(box1Pos.x + box1Offset.x, box1Pos.y + box1Offset.y);
		// Bottom Right
		box1Offset = Vector2(width / 2, height / 2);
		box1Offset.Rotate(angle);
		Vector2 box1BottomRight = Vector2(box1Pos.x + box1Offset.x, box1Pos.y + box1Offset.y);

		// Box 2
		BoxCollider* box2Col = (BoxCollider*)col;
		Vector2 box2Pos = box2Col->transform->worldposition;
		// Top Left
		Vector2 box2Offset = Vector2(-box2Col->width / 2, -box2Col->height / 2);
		box2Offset.Rotate(box2Col->angle);
		Vector2 box2TopLeft = Vector2(box2Pos.x + box2Offset.x, box2Pos.y + box2Offset.y);
		// Top Right
		box2Offset = Vector2(box2Col->width / 2, -box2Col->height / 2);
		box2Offset.Rotate(box2Col->angle);
		Vector2 box2TopRight = Vector2(box2Pos.x + box2Offset.x, box2Pos.y + box2Offset.y);
		// Bottom Left
		box2Offset = Vector2(-box2Col->width / 2, box2Col->height / 2);
		box2Offset.Rotate(box2Col->angle);
		Vector2 box2BottomLeft = Vector2(box2Pos.x + box2Offset.x, box2Pos.y + box2Offset.y);
		// Bottom Right
		box2Offset = Vector2(box2Col->width / 2, box2Col->height / 2);
		box2Offset.Rotate(box2Col->angle);
		Vector2 box2BottomRight = Vector2(box2Pos.x + box2Offset.x, box2Pos.y + box2Offset.y);

		Vector2 box1TopNorm = (box1TopRight.operator-(box1TopLeft)).Normalize();
		Vector2 box1SideNorm = (box1BottomLeft.operator-(box1TopLeft)).Normalize();
		// Get each box corners for length (Seperating Axis Theorem)
		bool axis1 = false;
		bool axis2 = false;
		// Axis 1 (box1Top) Get the bigger distance
		float box1TopDist = (box1TopRight.operator-(box1TopLeft)).Length();
		float box2TopLeftDist = abs((box1TopRight.operator-(box2TopLeft)).Dot(box1TopNorm));
		if (box2TopLeftDist < abs((box1TopLeft.operator-(box2TopLeft)).Dot(box1TopNorm)))
			box2TopLeftDist = abs((box1TopLeft.operator-(box2TopLeft)).Dot(box1TopNorm));
		float box2TopRightDist = abs((box1TopRight.operator-(box2TopRight)).Dot(box1TopNorm));
		if (box2TopRightDist < abs((box1TopLeft.operator-(box2TopRight)).Dot(box1TopNorm)))
			box2TopRightDist = abs((box1TopLeft.operator-(box2TopRight)).Dot(box1TopNorm));
		float box2BottomLeftDist = abs((box1TopRight.operator-(box2BottomLeft)).Dot(box1TopNorm));
		if (box2BottomLeftDist < abs((box1TopLeft.operator-(box2BottomLeft)).Dot(box1TopNorm)))
			box2BottomLeftDist = abs((box1TopLeft.operator-(box2BottomLeft)).Dot(box1TopNorm));
		float box2BottomRightDist = abs((box1TopRight.operator-(box2BottomRight)).Dot(box1TopNorm));
		if (box2BottomRightDist < abs((box1TopLeft.operator-(box2BottomRight)).Dot(box1TopNorm)))
			box2BottomRightDist = abs((box1TopLeft.operator-(box2BottomRight)).Dot(box1TopNorm));
		if (box2TopLeftDist < box1TopDist || box2TopRightDist < box1TopDist || box2BottomLeftDist < box1TopDist || box2BottomRightDist < box1TopDist)
			axis1 = true;
		// Axis 2 (box1Side)
		float box1SideDist = (box1BottomLeft.operator-(box1TopLeft)).Length();
		box2TopLeftDist = abs((box1BottomLeft.operator-(box2TopLeft)).Dot(box1SideNorm));
		if (box2TopLeftDist < abs((box1TopRight.operator-(box2TopLeft)).Dot(box1SideNorm)))
			box2TopLeftDist = abs((box1TopRight.operator-(box2TopLeft)).Dot(box1SideNorm));
		box2TopRightDist = abs((box1BottomLeft.operator-(box2TopRight)).Dot(box1SideNorm));
		if (box2TopRightDist < abs((box1TopRight.operator-(box2TopRight)).Dot(box1SideNorm)))
			box2TopRightDist = abs((box1TopRight.operator-(box2TopRight)).Dot(box1SideNorm));
		box2BottomLeftDist = abs((box1BottomLeft.operator-(box2BottomLeft)).Dot(box1SideNorm));
		if (box2BottomLeftDist < abs((box1TopRight.operator-(box2BottomLeft)).Dot(box1SideNorm)))
			box2BottomLeftDist = abs((box1TopRight.operator-(box2BottomLeft)).Dot(box1SideNorm));
		box2BottomRightDist = abs((box1BottomLeft.operator-(box2BottomRight)).Dot(box1SideNorm));
		if (box2BottomRightDist < abs((box1TopRight.operator-(box2BottomRight)).Dot(box1SideNorm)))
			box2BottomRightDist = abs((box1TopRight.operator-(box2BottomRight)).Dot(box1SideNorm));
		if (box2TopLeftDist < box1SideDist || box2TopRightDist < box1SideDist || box2BottomLeftDist < box1SideDist || box2BottomRightDist < box1SideDist)
			axis2 = true;

		// Check Collision
		if (axis1 && axis2)
			return true;
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

void CircleCollider::UpdateDimension(void)
{
	SpriteRenderer* _sr = this->Owner()->GetComponent<SpriteRenderer>();
	if (_sr != NULL) {
		radius = _sr->GetHalfWidth() + _sr->GetHalfHeight();
	}
	else {
		radius = 50;
	}
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