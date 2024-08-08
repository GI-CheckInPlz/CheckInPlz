#include "TitleBackground.h"

//Controls Soundplay

typedef struct TitleBackgroundProp
{
	HBITMAP titleImage;
	HBITMAP titleLogo;

	
}TitleBackgroundProp;

GameObject* CreateTitleBackground()
{
	TitleBackgroundProp* property = (TitleBackgroundProp*)malloc(sizeof(TitleBackgroundProp));
	if (property == NULL)
	{
		return NULL;
	}

	Transform transform = { {960,540},0,{1,1} };
	GameObject* obj = CreateGameObject();

	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;

	obj->Draw = TitleBackgroundDraw;
	

	obj->property = property;
	property->titleImage = LoadBitmapImage(L"Resources\\TitleUI\\TitleScreen.bmp");
	property->titleLogo = LoadBitmapImage(L"Resources\\TitleUI\\TitleLogo.bmp");
	
	obj->SetRect(obj, 1920, 1080);
	obj->SetTag(obj, "TitleBackground");
	obj->renderOrder = UI_ORDER-10;
	obj->collider = false;
	return obj;
}



DWORD WINAPI TitleBackgroundDraw(GameObject* this)
{
	TitleBackgroundProp* prop = this->property;
	render.DrawBitmapPreSize(this, prop->titleImage, 1, 1920, 1080);
	render.DrawBitmapWithCustom(this, prop->titleLogo, 1, 785, 310,0,-200);
	return 0;
}

