

#include "define.h"
#include "Engine.h"
#include "GameScenes.h"
#include "Win32Api.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,_In_ LPWSTR lpCmdLine,_In_ int nCmdShow)
{
	Init(hInstance);
	InitScenes();
	RunEngine(GameScene[0]);
	RemoveFontResource(L"Resources\\Font\\CinzelDecorative-Black.ttf");
	RemoveFontResource(L"Resources\\Font\\CinzelDecorative-Bold.ttf");
}