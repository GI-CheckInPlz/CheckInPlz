#include "GearIcon.h"

Bool _isBGMSelectOn;

//Controls Soundplay

typedef struct GearIconProp
{
	HBITMAP pressedSprite;
	HBITMAP normalSprite;

	Bool isClicked;
}GearIconProp;

GameObject* CreateGearIcon()
{
	GearIconProp* property = (GearIconProp*)malloc(sizeof(GearIconProp));
	if (property == NULL)
	{
		return NULL;
	}

	Transform transform = { {1850,50},0,{1,1} };
	GameObject* obj = CreateGameObject();

	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Start = GearIconStart;
	obj->Draw = GearIconDraw;
	obj->Update = GearIconUpdate;
	obj->OnDestroy = GearIconOnDestroy;

	obj->property = property;
	property->normalSprite = LoadBitmapImage(L"Resources\\TitleUI\\GearIcon.bmp");
	property->pressedSprite = LoadBitmapImage(L"Resources\\TitleUI\\GearIconPressed.bmp");
	property->isClicked = false;

	obj->SetRect(obj, 80, 81);
	obj->SetTag(obj, "GearIcon");
	obj->renderOrder = UI_ORDER;
	obj->collider = false;
	return obj;
}

void GearIconStart(GameObject* this)
{
	_isBGMSelectOn = false;
	AUDIO_PlayAudioLoop("Resources\\Sound\\BGM_Title.wav"); // Resources\/Sound\/
}

void GearIconUpdate(GameObject* this, double dt)
{
	GearIconProp* prop = this->property;
	vector2 pos = GetMousePosition();
	if (physics.InBound(this, pos) && input.GetMouseButton(0))
	{
		prop->isClicked = true;
		_isBGMSelectOn = true;
	}
	else
	{
		prop->isClicked = false;
	}

	if (physics.InBound(this, pos) && input.GetMouseButtonDown(0))
	{
		AUDIO_PlayAudio("Resources\\Sound\\ButtonClick.wav", 1);
	}
	
}

DWORD WINAPI GearIconDraw(GameObject* this)
{
	GearIconProp* prop = this->property;
	if (prop->isClicked == false)
	{
		render.DrawBitmapPreSize(this, prop->normalSprite, 1, 80, 81);
	}
	else
	{
		render.DrawBitmapPreSize(this, prop->pressedSprite, 1, 80, 81);
	}
	return 0;
}

void GearIconOnDestroy(GameObject* this)
{
	GearIconProp* prop = this->property;
	free(prop);
}
