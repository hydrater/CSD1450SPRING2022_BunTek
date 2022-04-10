/*!*****************************************************************************
\file DebuggingTools.h
\project Beyond Aurorean Skies
\author: Algene Tan Chuan Hong (90%)
\co-authors: Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Bryan Boh Tai Hong (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Debugging Tools
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*******************************************************************************/
#pragma once

#define Debugger _debuggingTools::Instance()

class _debuggingTools
{
public:
	_debuggingTools();
	~_debuggingTools();
	static _debuggingTools& Instance(void);
	void CheatsUpdate(void);
private:
};
