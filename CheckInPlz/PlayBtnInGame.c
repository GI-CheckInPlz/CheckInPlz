#include "PlayBtnInGame.h"

typedef struct PlayBtnInGameProp
{
	HBITMAP normalSprite;
	HBITMAP pressedSprite;
	
	Bool isClicked;

}PlayBtnInGameProp;

GameObject* CreatePlayBtnInGame()
{
	PlayBtnInGameProp* property = (PlayBtnInGameProp*)malloc(sizeof(PlayBtnInGameProp));
	if (property == NULL)
	{
		return NULL;
	}

	Transform transform = { {100,250},0,{1,1} };
	GameObject* obj = CreateGameObject();

	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Start = PlayBtnInGameStart;
	obj->Draw = PlayBtnInGameDraw;
	obj->Update = PlayBtnInGameUpdate;
	obj->OnDestroy = PlayBtnInGameOnDestroy;
	obj->property = property;

	property->normalSprite = LoadBitmapImage(L"Resources\\Map\\PlayBtnInGame.bmp");
	property->pressedSprite = LoadBitmapImage(L"Resources\\Map\\PlayBtnInGamePressed.bmp");
	property->isClicked = false;

	obj->SetRect(obj, 105, 137);
	obj->SetTag(obj, "PlayBtnInGame");
	obj->renderOrder = UI_ORDER;
	obj->collider = false;
	obj->OnDestroy = PlayBtnInGameOnDestroy;

	return obj; 
}

void PlayBtnInGameStart(GameObject* this)
{

}

void PlayBtnInGameUpdate(GameObject* this, double dt)
{
	
	PlayBtnInGameProp* prop = this->property;
	vector2 pos = GetMousePosition();
	if (input.GetMouseButtonUp(0) && prop->isClicked)
	{
		if (!IsPlaying)
		{
			Play(ingame);
			prop->isClicked = false;
		}
	}

	if (physics.InBound(this, pos) && input.GetMouseButtonDown(0))
	{
		prop->isClicked = true;
		AUDIO_PlayAudio("Resources\\Sound\\ButtonClick.wav", 1);
	}

	if (!physics.InBound(this, pos) || input.GetMouseButtonUp(0))
	{
		prop->isClicked = false;
	}

	
}

DWORD WINAPI PlayBtnInGameDraw(GameObject* this)
{
	PlayBtnInGameProp* prop = this->property;
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

void PlayBtnInGameOnDestroy(GameObject* this)
{
	PlayBtnInGameProp* prop = this->property;
	free(prop);
}