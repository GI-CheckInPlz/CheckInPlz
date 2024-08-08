#include "Debug.h"
#include <time.h>
#define DEBUG_ORDER 100

Bool creditsBool;
extern Bool toggleDebug;

GameObject* CreateDebug()
{
	Transform transform = { {100, 100}, 0, {1,1} };
	PropDebug* property = (PropDebug*)malloc(sizeof(PropDebug));
	if (property == NULL)
	{
		return NULL;
	}
	property->frameCnt = 0;
	property->current = 0;
	GameObject* obj = CreateGameObject();
	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Start = DebugStart;
	obj->Update = DebugUpdate;
	obj->Draw = DebugDraw;
	obj->SetRect(obj, 100, 100);
	obj->property = property;
	property->maskBMP = LoadBitmapImage(L"Resources\\CutScene\\MaskWhite.bmp");
	property->printBMP = LoadBitmapImage(L"Resources\\CutScene\\BackgroundPaper.bmp");



	obj->renderOrder = DEBUG_ORDER;
	obj->OnDestroy = DebugOnDestroy;
	return obj;
}

static clock_t prevTime;
static clock_t nowTime;



void DebugStart(GameObject* this)
{
	prevTime = clock();
	PropDebug* prop = this->property;
	timer.Delay(this, 1, true, ResetFrameCnt, &prop->frameCnt);
}

void ResetFrameCnt(GameObject* this, int* fc)
{
	PropDebug* prop = this->property;
	prop->current = prop->frameCnt;
	*fc = 0;
}
DWORD WINAPI DebugDraw(GameObject* this)
{
	PropDebug* prop = this->property;
	
	TCHAR str1[1024];
	TCHAR str2[1024];
	wsprintf(str1, TEXT("fps : %d"), prop->current / 1000);
	rect2D matrix = { {30, 10},{100,100} };
	wsprintf(str2, TEXT("Á¤´ä\n%d %d\n %d %d\n %d %d \n %d %d"), PlayerSolution[3][0], PlayerSolution[3][1], PlayerSolution[2][0], PlayerSolution[2][1], PlayerSolution[1][0], PlayerSolution[1][1], PlayerSolution[0][0], PlayerSolution[0][1]);
	if (toggleDebug)
	{
		render.DrawDebugText(this, str1, this->rect, L"Cinzel Decorative Black", 16, FW_BLACK);
		render.DrawDebugText(this, str2, matrix, L"Cinzel Decorative Black", 16, FW_BLACK);
	}
	
	//render.DrawMaskedBitmapCoords(this, prop->printBMP, 1, 1920, 1080, 0, 0, prop->maskBMP);
	
	
	return 0;
}

WINDOWPLACEMENT g_wpPrev = { sizeof(g_wpPrev) };






void DebugUpdate(GameObject* this, double dt)
{
	PropDebug* prop = this->property;
	prop->frameCnt++;

	if (input.GetKeyDown(0x46))
	{
		DWORD dwStyle = GetWindowLong(m_hWnd, GWL_STYLE);
		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{
			MONITORINFO mi = { sizeof(mi) };
			if (GetWindowPlacement(m_hWnd, &g_wpPrev) &&
				GetMonitorInfo(MonitorFromWindow(m_hWnd,
					MONITOR_DEFAULTTOPRIMARY), &mi))
			{
				SetWindowLong(m_hWnd, GWL_STYLE,
					dwStyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(m_hWnd, HWND_TOP,
					mi.rcMonitor.left, mi.rcMonitor.top,
					mi.rcMonitor.right - mi.rcMonitor.left,
					mi.rcMonitor.bottom - mi.rcMonitor.top,
					SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
			}
		}
		else
		{
			SetWindowLong(m_hWnd, GWL_STYLE,
				dwStyle | WS_OVERLAPPEDWINDOW);
			SetWindowPlacement(m_hWnd, &g_wpPrev);
			SetWindowPos(m_hWnd, NULL, 0, 0, 0, 0,
				SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER |
				SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
		}
	}

	/// <summary>
	/// CREDIT
	/// </summary>
	/// <param name=""></param>
	/// <param name="dt"></param>
	

	
	if (input.GetKeyDown(0x45))
	{
		nowTime = clock()-prevTime;
		float elapsedSeconds = ((float)nowTime) / CLOCKS_PER_SEC;
		if (elapsedSeconds >= 2)
		{
			if (currentScene != GameScene[3])
			{
				ChangeScene(GameScene[3]);
			}
			else
			{
				ChangeScene(GameScene[0]);
			}
		}
		prevTime = clock();
	}

	if (input.GetKeyDown(0x54))
	{
		toggleDebug = !toggleDebug;
	}


}

void DebugOnDestroy(GameObject* this)
{
	free(this->property);
	timer.CancelAllInObject(this);
}