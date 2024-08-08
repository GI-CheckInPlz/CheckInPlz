#include "ResetBtnInGame.h"

typedef struct ResetBtnInGameProp
{
	HBITMAP pressedSprite;
	HBITMAP normalSprite;

	Bool isClicked;
}ResetBtnInGameProp;

GameObject* CreateResetBtnInGame()
{
	ResetBtnInGameProp* property = (ResetBtnInGameProp*)malloc(sizeof(ResetBtnInGameProp));
	if (property == NULL)
	{
		return NULL;
	}

	Transform transform = { {230,250},0,{1,1} };
	GameObject* obj = CreateGameObject();

	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Start = ResetBtnInGameStart;
	obj->Draw = ResetBtnInGameDraw;
	obj->Update = ResetBtnInGameUpdate;
	obj->OnDestroy = ResetBtnInGameOnDestroy;

	obj->property = property;
	property->normalSprite = LoadBitmapImage(L"Resources\\Map\\ResetBtnInGame.bmp");
	property->pressedSprite = LoadBitmapImage(L"Resources\\Map\\ResetBtnInGamePressed.bmp");
	property->isClicked = false;

	obj->SetRect(obj, 105, 137);
	obj->SetTag(obj, "ResetBtnInGame");
	obj->renderOrder = UI_ORDER;
	obj->collider = false;
	obj->OnDestroy = ResetBtnInGameOnDestroy;

	return obj;
}

void ResetBtnInGameStart(GameObject* this)
{

}

void ResetBtnInGameUpdate(GameObject* this, double dt)
{
	ResetBtnInGameProp* prop = this->property;
	vector2 pos = GetMousePosition();

	if (input.GetMouseButtonUp(0) && prop->isClicked)
	{
		Reset(ingame);
		prop->isClicked = false;
	}
	if (physics.InBound(this, pos) && input.GetMouseButtonDown(0))
	{
		AUDIO_PlayAudio("Resources\\Sound\\ButtonClick.wav", 1);
		prop->isClicked = true;
	}

	if (!physics.InBound(this, pos) || input.GetMouseButtonUp(0))
	{
		prop->isClicked = false;
	}
}

DWORD WINAPI ResetBtnInGameDraw(GameObject* this)
{
	ResetBtnInGameProp* prop = this->property;
	if (prop->isClicked == true)
	{
		render.DrawBitmapPreSize(this, prop->pressedSprite, 1, 105, 137);
	}
	else
	{
		render.DrawBitmapPreSize(this, prop->normalSprite, 1, 105, 137);
	}
	return 0;
}

void ResetBtnInGameOnDestroy(GameObject* this)
{
	ResetBtnInGameProp* prop = this->property;
	free(prop);
}