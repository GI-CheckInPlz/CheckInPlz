#include "StartBtn.h"

Bool _isStageSelectOn;
Bool _isBGMSelectOn;

typedef struct StartBtnProp {
	int size_x;
	int size_y;
	float filterAlpha;
	HBITMAP normal;
	HBITMAP pressed;
	HBITMAP current;
	Bool clicked;
}StartBtnProp;

GameObject* CreateStartBtn()
{
	StartBtnProp* property = (StartBtnProp*)malloc(sizeof(StartBtnProp));
	if (property == NULL)
	{
		return NULL;
	}
	property->normal = render.LoadBitmapImage(L"Resources\\TitleUI\\GameStartButton1.bmp");
	property->pressed = render.LoadBitmapImage(L"Resources\\TitleUI\\GameStartButton2.bmp");
	property->current = property->normal;
	property->filterAlpha = 0;
	Transform transform = { {960,700},0,{1,1} };
	GameObject* obj = CreateGameObject();
	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Draw = StartBtnDraw;
	obj->Update = StartBtnUpdate;
	obj->property = property;
	property->size_x = 300;
	property->size_y = 60;
	property->clicked = false;
	obj->SetRect(obj, property->size_x, property->size_y);
	obj->SetTag(obj, "box");
	obj->collider = false;
	obj->OnDestroy = StartBtnOnDestroy;
	return obj;


}

DWORD WINAPI StartBtnDraw(GameObject* this)
{
	StartBtnProp* prop = this->property;
	render.DrawBitmapPreSize(this, prop->current, 1, (int)(prop->size_x * this->transform.scale.x), (int)(prop->size_y * this->transform.scale.y));
	render.DrawRectangle(this, prop->size_x, prop->size_y, RGB(255, 255, 255), RGB(220, 180, 100), prop->filterAlpha);
	return 0;
}


void StartBtnUpdate(GameObject* this, double dt)
{
	StartBtnProp* prop = this->property;
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
			//버그 고치기 (클릭이 다른 UI가 떠 있음에도 실행)
			if (_isStageSelectOn == false && _isBGMSelectOn == false)
			{
				currentStage = 0;
				ChangeScene(GameScene[1]);
				prop->clicked = false;
			}
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


	if (_isStageSelectOn == false && _isBGMSelectOn == false)
	{
		if (physics.InBound(this, input.GetMousePosition()) && input.GetMouseButtonDown(0))
		{
			AUDIO_PlayAudio("Resources\\Sound\\ButtonClick.wav", 1);
		}
	}





}

void StartBtnOnDestroy(GameObject* this)
{
	free(this->property);
}