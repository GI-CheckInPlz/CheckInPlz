#include "PopUpBottomUI.h"

typedef struct PopUpBottomUIProp
{
	Bool inUIArea;
	Bool isExtended;
	HBITMAP lowSprite;
	HBITMAP extendedSprite;
}PopUpBottomUIProp;

GameObject* CreatePopUpBottomUI()
{
	PopUpBottomUIProp* property = (PopUpBottomUIProp*)malloc(sizeof(PopUpBottomUIProp));
	Transform transform = { {950,1000},0,{1,1} };
	GameObject* obj = CreateGameObject();

	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Start = PopUpBottomUIStart;
	obj->Draw = PopUpBottomUIDraw;
	obj->Update = PopUpBottomUIUpdate;

	obj->property = property;
	property->inUIArea = false;
	property->isExtended = false;
	property->lowSprite = render.LoadBitmapImage(L"Resources\\Map\\layingUIBook.bmp");
	property->extendedSprite = render.LoadBitmapImage(L"Resources\\Map\\extendedUIBook.bmp");
	obj->SetRect(obj, 900, 80);
	obj->SetTag(obj, "BottomUI");
	obj->renderOrder = 4;
	obj->collider = false;
	return obj;
}


void PopUpBottomUIStart(GameObject* this)
{
	
}

void PopUpBottomUIUpdate(GameObject* this, double dt)
{
	PopUpBottomUIProp* prop = this->property;
	vector2 mousePos = GetMousePosition();

	if (physics.InBound(this, mousePos))
	{
		prop->inUIArea = true;
		this->SetRect(this, 900, 230);

	}
	else
	{
		prop->inUIArea = false;
		this->SetRect(this, 900, 80);
	}


	//this->SetRect()
	
	
}

DWORD WINAPI PopUpBottomUIDraw(GameObject* this)
{
	PopUpBottomUIProp* prop = this->property;
	
	render.DrawBitmapPreSize(this, prop->lowSprite, 1, 900, 115);

}


