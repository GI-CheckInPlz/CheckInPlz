#pragma once
#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "Physics.h"
#include "Ingame.h"

#include "audioModule.h"
typedef struct OverlayProp
{
	HBITMAP retrySprite;
	HBITMAP clearSprite;
	HBITMAP stageSprite[4];
	Bool isClicked;
	float fadeRetry;
	float fadeClear;
	float fadeFilter;
	float fadeStage[4];
}OverlayProp;

extern GameObject* CreateOverlay();

void OverlayStart(GameObject* this);

DWORD WINAPI OverlayDraw(GameObject* this);

void OverlayOnDestroy(GameObject* this);

GameObject* ingame;
