#include "Vector2.h"


Vector2::Vector2() :
	x(0),
	y(0)
{
}

Vector2::Vector2(int x, int y)
{
	this->x = (float)(x);
	this->y = (float)(y);
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2 Vector2::operator-(void) const
{
	return Vector2(-x, -y);
}

Vector2& Vector2::operator=(const Vector2& vec)
{
	x = vec.x;
	y = vec.y;
	return *this;
}

Vector2 Vector2::operator+(const Vector2& vec) const
{
	return Vector2(x + vec.x, y + vec.y);
}

Vector2 Vector2::operator-(const Vector2& vec) const
{
	return Vector2(x - vec.x, y - vec.y);
}

Vector2& Vector2::operator+=(const Vector2& vec)
{
	x += vec.x;
	y += vec.y;
	return *this;
}

Vector2 Vector2::operator-=(const Vector2& vec)
{
	x -= vec.x;
	y -= vec.y;
	return *this;
}

Vector2 Vector2::operator*(const float scalar) const
{
	return Vector2(scalar * x, scalar * y);
}

Vector2& Vector2::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

void Vector2::Set(const Vector2& vec)
{
	x = vec.x;
	y = vec.y;
}

void Vector2::Set(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Vector2::SetZero()
{
	x = y = 0;
}

//Does Clockwise Rotatoin
void Vector2::Rotate(float degrees)
{
	float sin = sinf(degrees / 180.0f * 3.1415926535897932384626433832795f);
	float cos = cosf(degrees / 180.0f * 3.1415926535897932384626433832795f);
	float tx = x;
	float ty = y;
	x = (sin * ty) - (cos * tx);
	y = (sin * tx) + (cos * ty);
}

float Vector2::Length(void) const
{
	return sqrt(x * x + y * y );
}

float Vector2::LengthSquared(void) const
{
	return x * x + y * y;
}

float Vector2::Dot(const Vector2& vec) const
{
	return x * vec.x + y * vec.y ;
}

float Vector2::AngleBetween(const Vector2 vec) {
	return atan2f(y - vec.y, x - vec.x);
}

Vector2 Vector2::Normalized(void) const throw(DivideByZero)
{
	float d = Length();
	if (d <= Math::epsilon && -d <= Math::epsilon)
		throw DivideByZero();
	return Vector2(x / d, y / d);
}

Vector2& Vector2::Normalize(void) throw(DivideByZero)
{
	float d = Length();
	if (d <= Math::epsilon && -d <= Math::epsilon)
		throw DivideByZero();
	x /= d;
	y /= d;
	return *this;
}

Vector2 Vector2::Zero()
{
	return Vector2();
}

Vector2 Vector2::Splat(float splat)
{
	return Vector2(splat, splat);
}

//speed is min 0 max 1
Vector2 Vector2::Lerp(Vector2 destination, float speed)
{
	speed = Clamp(speed, 0.0f, 1.0f);
	return Vector2(x * (1 - speed) + destination.x * speed, y * (1 - speed) + destination.y * speed);
}

#include <sstream>

std::string Vector2::ToString(void)
{
	std::ostringstream ss;
	ss <<"[" <<x << ", " << y << "]";
	return ss.str();
}
Vector2::~Vector2()
{

}
