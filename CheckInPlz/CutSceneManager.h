#pragma once
#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "Physics.h"
#include "Ingame.h"

#include "audioModule.h"
#define NUMBER_OF_MASK 3
#define MAX_CUTSCENE_OBJECT 10
#define NUMBER_OF_CUTS 3
typedef struct CutSceneObject {
	Transform transform;
	HBITMAP sprite;
	float alpha;
}CutSceneObject;
typedef struct SpeechBubble {
	Transform transform;
	HBITMAP sprite;
	float alpha;
}SpeechBubble;
typedef struct Cut{
	Transform transform;
	HBITMAP sprite;
	HBITMAP outline;
	float alpha;
	int length;
	CutSceneObject image;
	CutSceneObject object[10];
}Cut;


typedef struct CutSceneManagerProp
{
	SpeechBubble bubble[4];
	HBITMAP Background;
	Cut mask[NUMBER_OF_MASK];
	void (*AnimateCutScene[NUMBER_OF_CUTS])(GameObject*);
	Bool isClicked;
	int index;
}CutSceneManagerProp;




extern GameObject* CreateCutSceneManager();

void CutSceneManagerUpdate(GameObject* this);

DWORD WINAPI CutSceneManagerDraw(GameObject* this);
void CutSceneManagerUpdate(GameObject* this, double dt);
void DrawMaskedDC(GameObject* this, HDC tmp, HBITMAP maskBMP, int size_x, int size_y, int _posX, int _posY);
void CutSceneManagerStart(GameObject*);
void CutSceneManagerOnDestroy(GameObject* this);
void initilizeCut0(CutSceneManagerProp* property);
void initilizeCut1(CutSceneManagerProp* property);
void initilizeCut2(CutSceneManagerProp* property);
void cut0(GameObject* this);

static Bool Showing;
