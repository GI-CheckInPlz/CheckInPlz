#include "BGMSelect.h"

extern Bool _isBGMSelectOn;
Bool _isStageSelectOn;

typedef struct BGMSelectProp
{
	HBITMAP BGMSelectUI;
	HBITMAP BGMPellet;
	HBITMAP EffectPellet;

	rect2D bgmPelletArea;
	rect2D effectPelletArea;

	int BGMPelletPos;
	int EffectPelletPos;

	Bool testBool;


}BGMSelectProp;



//사이 서로 580간의 차이가 존재, 
//

void SetBGMPelletsRectArea(GameObject* this, vector2 _pos)
{
	BGMSelectProp* prop = this->property;
	if (_pos.x >= 670 && _pos.x <= 1250)
	{
		prop->BGMPelletPos = (int)_pos.x;
		prop->bgmPelletArea.min.x = _pos.x - 22;
		prop->bgmPelletArea.max.x = _pos.x + 22;

		int dvBGM = ((prop->BGMPelletPos - 670) / 580) * 100;
		AUDIO_SetBgmVolume(dvBGM);
	}

	//결과적으로, 
	//위치상 670 = Zero 취급, 1250 = 100 취급.
	//그러니, ex. 1000->
	//1000-670 = 330. 

}

void SetEffectPelletsRectArea(GameObject* this, vector2 _pos)
{
	BGMSelectProp* prop = this->property;
	if (_pos.x >= 670 && _pos.x <= 1250)
	{
		prop->EffectPelletPos = (int)_pos.x;
		prop->effectPelletArea.min.x = _pos.x - 22;
		prop->effectPelletArea.max.x = _pos.x + 22;

		int dvEffect = ((prop->BGMPelletPos - 670) / 580) * 100;
		AUDIO_SetEffectVolume(dvEffect);
	}

}


GameObject* CreateBGMSelect()
{
	BGMSelectProp* property = (BGMSelectProp*)malloc(sizeof(BGMSelectProp));
	if (property == NULL)
	{
		return NULL;
	}

	Transform transform = { {960,540},0,{1,1} };
	GameObject* obj = CreateGameObject();

	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Start = BGMSelectStart;
	obj->Draw = BGMSelectDraw;
	obj->Update = BGMSelectUpdate;
	obj->OnDestroy = BGMSelectOnDestroy;

	obj->property = property;
	property->BGMSelectUI = LoadBitmapImage(L"Resources\\TitleUI\\BGMSelect\\SoundSettings.bmp");
	property->BGMPellet = LoadBitmapImage(L"Resources\\TitleUI\\BGMSelect\\pellet.bmp");
	property->EffectPellet = LoadBitmapImage(L"Resources\\TitleUI\\BGMSelect\\pellet.bmp");
	//670, 562
	//670, 692

	property->BGMPelletPos = (1250);
	property->EffectPelletPos = (1250);

	property->bgmPelletArea.min.x = 1250 - 22;
	property->bgmPelletArea.max.x = 1250 + 22;
	property->bgmPelletArea.min.y = 562 - 35;
	property->bgmPelletArea.max.y = 562 + 35;
	//실제로 좌표 위에 위치.

	property->effectPelletArea.min.x = 1250 - 22;
	property->effectPelletArea.max.x = 1250 + 22;
	property->effectPelletArea.min.y = 692 - 35;
	property->effectPelletArea.max.y = 692 + 35;
	//디폴트 상태 펠렛 area 확립.

	/*bgmPelletArea;
	effectPelletArea;*/
	property->testBool = false;

	obj->SetRect(obj, 950, 800);
	obj->SetTag(obj, "BGMSelect");
	obj->renderOrder = UI_ORDER;
	obj->collider = false;
	return obj;
}

void BGMSelectStart(GameObject* this)
{

}

void BGMSelectUpdate(GameObject* this, double dt)
{
	BGMSelectProp* prop = this->property;
	vector2 pos = GetMousePosition();

	//44x70이 펠렛 크기.


	if (!(physics.InBound(this, pos)) && input.GetMouseButtonDown(0))
	{
		_isBGMSelectOn = false;
	}

	if (_isBGMSelectOn == true)
	{
		
		//NoClick.wav

		if (_isStageSelectOn == false && _isBGMSelectOn == true)
		{

			if (input.GetMouseButton(0) && physics.InBoundRect(prop->bgmPelletArea, pos))
			{
				SetBGMPelletsRectArea(this, pos);
			}

			if (input.GetMouseButton(0) && physics.InBoundRect(prop->effectPelletArea, pos))
			{
				SetEffectPelletsRectArea(this, pos);
			}

			if (input.GetMouseButtonDown(0) && physics.InBoundRect(prop->bgmPelletArea, pos))
			{
				AUDIO_PlayAudio("Resources\\Sound\\NoClick.wav", 1);
			}

			if (input.GetMouseButtonDown(0) && physics.InBoundRect(prop->effectPelletArea, pos))
			{
				AUDIO_PlayAudio("Resources\\Sound\\NoClick.wav", 1);
			}

		}


	}
}


DWORD WINAPI BGMSelectDraw(GameObject* this)
{
	BGMSelectProp* prop = this->property;

	if (_isBGMSelectOn == true)
	{
		render.DrawBitmapPreSize(this, prop->BGMSelectUI, 1, 950, 800);
		//render.DrawBitmapWithCustom(this, prop->BGMPellet, 1, 44, 70, -290, 22); // offset: (-290,22) // 원래 960 540 // 670 562
		//render.DrawBitmapWithCustom(this, prop->EffectPellet, 1, 44, 70, -290, 152); // offset: (-290,152)

		render.DrawBitmapWithCoords(this, prop->BGMPellet, 1, 44, 70, prop->BGMPelletPos, 562);
		render.DrawBitmapWithCoords(this, prop->EffectPellet, 1, 44, 70, prop->EffectPelletPos, 692); // original

	}
	return 0;
}

void BGMSelectOnDestroy(GameObject* this)
{
	BGMSelectProp* prop = this->property;
	free(prop);
}



