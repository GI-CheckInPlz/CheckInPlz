#include "ReturnToHomeBtn.h"


typedef struct ReturnToHomeBtnProp
{
	HBITMAP normalSprite;
	HBITMAP pressedSprite;
	
	Bool isClicked;

}ReturnToHomeBtnProp;

GameObject* CreateReturnToHomeBtn()
{
	ReturnToHomeBtnProp* property = (ReturnToHomeBtnProp*)malloc(sizeof(ReturnToHomeBtnProp));
	if (property == NULL)
	{
		return NULL;
	}

	Transform transform = { {1800,80},0,{1,1} };
	GameObject* obj = CreateGameObject();

	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Start = ReturnToHomeBtnStart;
	obj->Draw = ReturnToHomeBtnDraw;
	obj->Update = ReturnToHomeBtnUpdate;
	obj->OnDestroy = ReturnToHomeBtnOnDestroy;

	obj->property = property;
	property->normalSprite = LoadBitmapImage(L"Resources\\Map\\homeKey.bmp");
	property->pressedSprite = LoadBitmapImage(L"Resources\\Map\\homeKeyPressed.bmp");
	property->isClicked = false;

	obj->SetRect(obj, 80, 80);
	obj->SetTag(obj, "ReturnToHomeBtn");
	obj->renderOrder = UI_ORDER;
	obj->collider = false;
	obj->OnDestroy = ReturnToHomeBtnOnDestroy;

	return obj;
}

void ReturnToHomeBtnStart(GameObject* this)
{

}

void ReturnToHomeBtnUpdate(GameObject* this, double dt)
{
	ReturnToHomeBtnProp* prop = this->property;
	vector2 pos = GetMousePosition();
	if (physics.InBound(this, pos) && input.GetMouseButtonDown(0))
	{
		prop->isClicked = true;
		AUDIO_PlayAudio("Resources\\Sound\\ButtonClick.wav", 1);
	}

	if (input.GetMouseButtonUp(0) && prop->isClicked)
	{
		ClearMonster();
		ChangeScene(GameScene[0]);
	}

	if (!physics.InBound(this, pos) || input.GetMouseButtonUp(0))
	{
		prop->isClicked = false;
	}


}

void ReturnToHomeBtnOnDestroy(GameObject* this)
{
	ReturnToHomeBtnProp* prop = this->property;
	free(prop);
}


DWORD WINAPI ReturnToHomeBtnDraw(GameObject* this)
{
	ReturnToHomeBtnProp* prop = this->property;
	if (prop->isClicked == true)
	{
		render.DrawBitmapPreSize(this, prop->pressedSprite, 1, 80, 80);

	}
	else
	{
		render.DrawBitmapPreSize(this, prop->normalSprite, 1, 80, 80);
	}
	return 0;
}