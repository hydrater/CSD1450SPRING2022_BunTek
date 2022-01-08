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
		float value = (float)(camPos.y + cameraMoveSpeed * AEFrameRateControllerGetFrameTime());
		value = AEClamp(value, -maxY, maxY);
		camPos.y = value;

		AEGfxSetCamPosition(camPos.x, value);
	}

	if (y > lowerBoundary)
	{
		float value = (float)(camPos.y - cameraMoveSpeed * AEFrameRateControllerGetFrameTime());
		value = AEClamp(value, -maxY, maxY);
		camPos.y = value;

		AEGfxSetCamPosition(camPos.x, value);
	}

	if (x < leftBoundary)
	{
		float value = (float)(camPos.x - cameraMoveSpeed * AEFrameRateControllerGetFrameTime());
		value = AEClamp(value, -maxX, maxX);
		camPos.x = value;

		AEGfxSetCamPosition(value, camPos.y);
	}

	if (x > rightBoundary)
	{
		float value = (float)(camPos.x + cameraMoveSpeed * AEFrameRateControllerGetFrameTime());
		value = AEClamp(value, -maxX, maxX);
		camPos.x = value;

		AEGfxSetCamPosition(value, camPos.y);
	}

	float n, m;
	AEGfxGetCamPosition(&n, &m);
}
