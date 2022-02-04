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
	bool fullScreen = true;
};
