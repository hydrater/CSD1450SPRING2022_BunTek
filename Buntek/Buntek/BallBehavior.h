#pragma once
#include "Component.h"
#include <iostream>
using namespace std;

class BallBehavior :
	public Component
{
public:
	BallBehavior();
	~BallBehavior();

	void TestPrint(void);
};