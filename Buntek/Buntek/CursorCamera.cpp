#include "CursorCamera.h"

CursorCamera::CursorCamera(void)
{
}

CursorCamera::~CursorCamera(void)
{
}

void CursorCamera::Start(void)
{
}

void CursorCamera::Update(void)
{
	AEInputGetCursorPosition(&x, &y);
	if (y < upperBoundary)
	{
		float value = camPos.y + cameraMoveSpeed * AEFrameRateControllerGetFrameTime();
		value = AEClamp(value, -maxY, maxY);
		camPos.y = value;

		AEGfxSetCamPosition(camPos.x, value);
	}

	if (y > lowerBoundary)
	{
		float value = camPos.y - cameraMoveSpeed * AEFrameRateControllerGetFrameTime();
		value = AEClamp(value, -maxY, maxY);
		camPos.y = value;

		AEGfxSetCamPosition(camPos.x, value);
	}

	if (x < leftBoundary)
	{
		float value = camPos.x - cameraMoveSpeed * AEFrameRateControllerGetFrameTime();
		value = AEClamp(value, -maxX, maxX);
		camPos.x = value;

		AEGfxSetCamPosition(value, camPos.y);
	}

	if (x > rightBoundary)
	{
		float value = camPos.x + cameraMoveSpeed * AEFrameRateControllerGetFrameTime();
		value = AEClamp(value, -maxX, maxX);
		camPos.x = value;

		AEGfxSetCamPosition(value, camPos.y);
	}

	float n, m;
	AEGfxGetCamPosition(&n, &m);
	cout << n << " " << m << endl;
}
