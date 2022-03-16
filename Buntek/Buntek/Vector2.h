/*!*****************************************************************************
\file Vector2.h
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Vector2
*******************************************************************************/

#ifndef VECTOR2_H
#define VECTOR2_H

#include <string>
#include "hisMath.h"
#include <math.h>
using namespace Math;

class Vector2
{
public:
	Vector2();
	Vector2(int x, int y);
	Vector2(float x, float y);
	~Vector2();

	float x, y;

	Vector2& operator=(const Vector2& vec);

	Vector2 operator-(void) const;
	Vector2 operator+(const Vector2& vec) const;
	Vector2 operator-(const Vector2& vec) const;
	Vector2& operator+=(const Vector2& vec);
	Vector2 operator-=(const Vector2& vec);
	Vector2 operator*(const float scalar) const;
	Vector2& operator*=(float scalar);

	void Set(const Vector2& vec);
	void Set(float x, float y);
	void SetZero();
	void RotateAC(float degrees); //Counterclockwise
	void RotateC(float degrees); //Clockwise
	

	float Length(void) const;
	float LengthSquared(void) const;
	float Dot(const Vector2& vec) const;
	float AngleBetween(Vector2 vec);
	Vector2 Normalized(void) const;
	Vector2& Normalize(void);
	Vector2& Divide(float scalar);

	std::string ToString(void);

	static Vector2 Zero();
	static Vector2 Splat(float splat);
	Vector2 RandUnitVector(void);

	Vector2 Lerp(Vector2 destination, float speed);
};

#endif