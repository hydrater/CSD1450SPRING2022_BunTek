/*!*****************************************************************************
\file hisMath.h
\project Beyond Aurorean Skies
\author: Steven Koe (80%)
\co-authors: Algene Tan Chuan Hong (5%), Isaiah Lim Ji Rong (5%), Bryan Boh Tai Hong (5%), Goh Kiat Beng (5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles the Math of the system
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*******************************************************************************/
#ifndef MATH_H
#define MATH_H

#include <cmath>
#include <exception>
#include <ctime>
#include <cstdlib>

namespace Math
{
	const float epsilon = 0.00001f;  ///Used for error checking
	const float	pi = 3.1415926535897932384626433832795f;
	const float two_pi = pi * 2.0f;
	const float half_pi = pi / 2.0f;
	const float quarter_pi = pi / 4.0f;

	inline float FAbs(float value)
	{
		return (value < 0) ? -value : value;
	}

	inline float DegreeToRadian(float value)
	{
		return value * pi / 180.0f;
	}

	inline float RadianToDegree(float value)
	{
		return value * 180.0f / pi;
	}

	template<typename T>
	T Wrap(T val, T minVal, T maxVal)
	{
		if (val < minVal)
		{
			return maxVal;
		}
		else if (val > maxVal)
		{
			return minVal;
		}

		return val;
	}

	template<typename T>
	T Clamp(T val, T minVal, T maxVal)
	{
		if (val < minVal)
		{
			return minVal;
		}
		else if (val > maxVal)
		{
			return maxVal;
		}

		return val;
	}

	template<typename T>
	T Min(T x, T y)
	{
		return (x < y) ? x : y;
	}

	template<typename T>
	T Max(T x, T y)
	{
		return (x > y) ? x : y;
	}

	template<typename T>
	T Square(T x)
	{
		return x * x;
	}

	inline void InitRNG(void)
	{
		srand(static_cast<unsigned> (time(0)));
	}//end of InitRNG function


	inline unsigned RandInt(void)
	{
		return rand();
	}//end of RandInt function

	inline int RandIntMinMax(int min, int max)
	{
		int num = rand() % (max - min + 1);
		return (num + min);
	}//end of RandIntMinMax function


	inline float RandFloat(void)
	{
		return rand() / static_cast <float> (RAND_MAX);
	}//end of RandFloat function


	inline float RandFloatMinMax(float min, float max)
	{
		float num = (max - min) * RandFloat();
		return (num + min);
	}//end of RandFloatMinMax function

	//inline float LerpF(float start_value, float end_value, float t)
	//{
	//	t = t > 1 ? 1 : t;
	//	t = t < 0 ? 0 : t;
	//	return start_value + (end_value - start_value) * t;
	//}//end of LerpF function

	inline float easeIn(float t)
	{
		return t * t;
	}

	inline float flip(float x)
	{
		return 1 - x;
	}

	inline float easeOut(float t)
	{
		float tmp = flip(t);
		return flip(tmp * tmp);
	}
	inline float lerpF(float start_value, float end_value, float t)
	{
		t = Clamp(t, 0.0f, 1.0f);
		return start_value + (end_value - start_value) * t;
	}
	inline float easeInOut(float t)
	{
		return lerpF(easeIn(t), easeOut(t), t);
		//t*t*t * (t * (6f*t - 15f) + 10f)
	}


}//end namespace Math

class DivideByZero : public std::exception
{
public:
	const char* what() { return "Divide By Zero"; }
};

#endif
