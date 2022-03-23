/*!*****************************************************************************
\file DebuggingTools.h
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Debugging Tools
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
