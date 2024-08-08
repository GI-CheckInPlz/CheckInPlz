#include "SelectStageBtn.h"

Bool _isStageSelectOn;
Bool _isBGMSelectOn;

typedef struct SelectStageBtnProp {
	int size_x;
	int size_y;
	float filterAlpha;
	HBITMAP normal;
	HBITMAP pressed;
	HBITMAP current;
	Bool clicked;
}SelectStageBtnProp;

GameObject* CreateSelectStageBtn()
{
	SelectStageBtnProp* property = (SelectStageBtnProp*)malloc(sizeof(SelectStageBtnProp));
	if (property == NULL)
	{
		return NULL;
	}
	property->normal = render.LoadBitmapImage(L"Resources\\TitleUI\\SelectStageButton1.bmp");
	property->pressed = render.LoadBitmapImage(L"Resources\\TitleUI\\SelectStageButton2.bmp");
	property->current = property->normal;
	property->filterAlpha = 0;
	Transform transform = { {960,800},0,{1,1} };
	GameObject* obj = CreateGameObject();
	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Draw = SelectStageBtnDraw;
	obj->Update = SelectStageBtnUpdate;
	obj->property = property;
	property->size_x = 300;
	property->size_y = 60;
	property->clicked = false;
	obj->SetRect(obj, property->size_x, property->size_y);
	obj->SetTag(obj, "box");
	obj->collider = false;
	obj->OnDestroy = SelectStateBtnOnDestroy;
	return obj;


}

DWORD WINAPI SelectStageBtnDraw(GameObject* this)
{
	SelectStageBtnProp* prop = this->property;
	render.DrawBitmapPreSize(this, prop->current, 1, (int)(prop->size_x * this->transform.scale.x), (int)(prop->size_y * this->transform.scale.y));
	render.DrawRectangle(this, prop->size_x, prop->size_y, RGB(255, 255, 255), RGB(220, 180, 100), prop->filterAlpha);
	return 0;
}


void SelectStageBtnUpdate(GameObject* this, double dt)
{
	SelectStageBtnProp* prop = this->property;
	if (physics.InBound(this, input.GetMousePosition()))
	{
		prop->filterAlpha = 0.1f;

		if (input.GetMouseButtonDown(0))
		{
			prop->clicked = true;
			prop->current = prop->pressed;
		}
		else if (prop->clicked && input.GetMouseButtonUp(0))
		{
			//ChangeScene(GameScene[2]);
			_isStageSelectOn = true; //스테이지 셀렉션을 킨다.
			prop->clicked = false;
		}
		else if (prop->clicked && input.GetMouseButton(0))
		{

		}
		this->transform.scale.x = 1.2f;
		this->transform.scale.y = 1.2f;
	}
	else
	{
		prop->filterAlpha = 0;
		if (input.GetMouseButtonUp(0))
		{
			prop->filterAlpha = 0;
			prop->clicked = false;
			prop->current = prop->normal;
		}
		this->transform.scale.x = 1;
		this->transform.scale.y = 1;
	}



	if (physics.InBound(this, input.GetMousePosition()) && input.GetMouseButtonDown(0))
	{
		if (_isStageSelectOn == false && _isBGMSelectOn == false)
		{
			AUDIO_PlayAudio("Resources\\Sound\\ButtonClick.wav", 1);
		}
	}

	




}

void SelectStateBtnOnDestroy(GameObject* this)
{
	free(this->property);
}