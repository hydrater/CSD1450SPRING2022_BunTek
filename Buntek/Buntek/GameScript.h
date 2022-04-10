/*!*****************************************************************************
\file GameScript.h
\project Beyond Aurorean Skies
\author: Algene Tan Chuan Hong (90%)
\co-authors: Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Bryan Boh Tai Hong (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles GameScript
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*******************************************************************************/

#ifndef SCRIPT_H
#define SCRIPT_H

#include "Component.h"

class GameScript : public Component
{
public:
	GameScript();
	virtual ~GameScript();

	void Init(GameObject* owner) override;
	virtual void Start(void);
	virtual void Update(void);
	void setStarted(bool setValue);
	bool getStarted(void);
private:
	bool hasStarted;
};

#endif