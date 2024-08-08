#include "StageStartBtn.h"
//#define PRESSED_COLOR RGB(051,102,051)
//#define NOT_PRESSED_COLOR RGB(051,255,051)

static COLORREF btnPressed = RGB(051, 102, 051);
static COLORREF btnNotPressed = RGB(051, 255, 051);

typedef struct StageStartBtnProp {
	int size_x;
	int size_y;
	COLORREF btnColor;
	Bool clicked;
}StageStartBtnProp;

GameObject* CreateStageStartBtn()
{
	StageStartBtnProp* property = (StageStartBtnProp*)malloc(sizeof(StageStartBtnProp));
	Transform transform = { {200,50},0,{1,1} };
	GameObject* obj = CreateGameObject();
	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Draw = StageStartBtnDraw;
	obj->Update = StageStartBtnUpdate;
	obj->property = property;
	property->size_x = 200;
	property->size_y = 100;
	property->clicked = false;
	obj->SetRect(obj, property->size_x, property->size_y);
	obj->SetTag(obj, "StageStartBtn");
	obj->renderOrder = UI_ORDER;
	obj->collider = false;
	obj->OnDestroy = StageStartBtnOnDestroy;
	return obj;
}

DWORD WINAPI StageStartBtnDraw(GameObject* this)
{
	StageStartBtnProp* prop = this->property;
	render.DrawRectangle(this, prop->size_x, prop->size_y, prop->btnColor, prop->btnColor,1);
}


void StageStartBtnUpdate(GameObject* this, double dt)
{
	StageStartBtnProp* prop = this->property;
	if (physics.InBound(this, input.GetMousePosition()))
	{
		if (input.GetMouseButtonDown(0))
		{
			prop->clicked = true;
		}
		else if (prop->clicked && input.GetMouseButtonUp(0))
		{
			GenerateMonster(this);
			prop->clicked = false;
		}
		else if (prop->clicked && input.GetMouseButton(0))
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
		if (input.GetMouseButtonUp(0))
		{
			prop->clicked = false;
		}
	}
}

void StageStartBtnOnDestroy(GameObject* this)
{
	free(this->property);
}