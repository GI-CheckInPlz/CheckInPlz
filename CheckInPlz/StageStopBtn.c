#include "StageStopBtn.h"
//#define PRESSED_COLOR RGB(255,153,153)
//#define NOT_PRESSED_COLOR RGB(255,0,0)

static COLORREF btnPressed = RGB(255, 153, 153);
static COLORREF btnNotPressed = RGB(255, 0, 0);

typedef struct StageStopBtnProp {
	int size_x;
	int size_y;
	COLORREF btnColor;
	Bool clicked;
}StageStopBtnProp;

GameObject* CreateStageStopBtn()
{
	StageStopBtnProp* property = (StageStopBtnProp*)malloc(sizeof(StageStopBtnProp));
	Transform transform = { {400,50},0,{1,1} };
	GameObject* obj = CreateGameObject();
	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Draw = StageStopBtnDraw;
	obj->Update = StageStopBtnUpdate;
	obj->property = property;
	property->size_x = 200;
	property->size_y = 100;
	property->clicked = false;
	obj->SetRect(obj, property->size_x, property->size_y);
	obj->SetTag(obj, "StageStopBtn");
	obj->renderOrder = UI_ORDER;
	obj->collider = false;
	obj->OnDestroy = StageStopBtnOnDestroy;
	return obj;
}

DWORD WINAPI StageStopBtnDraw(GameObject* this)
{
	StageStopBtnProp* prop = this->property;
	render.DrawRectangle(this, prop->size_x, prop->size_y, prop->btnColor, prop->btnColor,1);
}


void StageStopBtnUpdate(GameObject* this, double dt)
{
	StageStopBtnProp* prop = this->property;
	if (physics.InBound(this, input.GetMousePosition()))
	{
		if (input.GetMouseButtonDown(0))
		{
			prop->clicked = true;
		}
		else if (input.GetMouseButtonUp(0))
		{

			prop->clicked = false;
		}
		else if (input.GetMouseButton(0))
		{
			prop->btnColor = btnPressed;
		}
		//this->transform.scale.x = 1.2;
		//this->transform.scale.y = 1.2;
	}
	else
	{
		prop->btnColor = btnNotPressed;
		this->transform.scale.x = 1;
		this->transform.scale.y = 1;
	}
}

void StageStopBtnOnDestroy(GameObject* this)
{
	free(this->property);
}