#include "CutSceneManager.h"
#define NUMBER_OF_LOOP_CUT_ANIMATION 7

static AnimationData* animation[NUMBER_OF_LOOP_CUT_ANIMATION];
void CompleteShow(GameObject* this, void* etc)
{
	Showing = false;
}

void cut0_3(GameObject* this, void* etc)
{
	CutSceneManagerProp* prop = this->property;
	animation[0] = Animate(this, &prop->mask[0].object[1].transform.rotation, PLAYBACK_LOOP_PINGPONG, prop->mask[0].object[1].transform.rotation+5, EASING_LINEAR, 5, NULL);
	animation[1] = Animate(this, &prop->mask[0].object[1].transform.position.y, PLAYBACK_LOOP_PINGPONG, prop->mask[0].object[1].transform.position.y - 10, EASING_LINEAR, 5, NULL);
	animation[2] = Animate(this, &prop->mask[0].object[1].transform.position.x, PLAYBACK_LOOP_PINGPONG, prop->mask[0].object[1].transform.position.x - 10, EASING_LINEAR, 5, NULL);

}
void cut0_2(GameObject* this, void* etc)
{
	CutSceneManagerProp* prop = this->property;
	prop->mask[0].object[1].alpha = 1;
	prop->mask[0].object[1].transform.position.x = 200;
	prop->mask[0].object[1].transform.position.y = -30;
	prop->mask[0].object[1].transform.rotation = -80;
	Animate(this, &prop->mask[0].object[1].transform.position.x, PLAYBACK_ONCE_BACKWARD, prop->mask[0].object[1].transform.position.x + 700, EASING_INBACK, 1, NULL);
	Animate(this, &prop->mask[0].object[1].transform.position.y, PLAYBACK_ONCE_BACKWARD, prop->mask[0].object[1].transform.position.y - 300, EASING_LINEAR, 1, NULL);
	Animate(this, &prop->mask[0].object[1].transform.rotation, PLAYBACK_ONCE_FORWARD, 0, EASING_OUTBOUNCE, 1.2, CompleteShow);
	timer.Delay(this, 1, false, cut0_3, NULL);
}

void cut0_1(GameObject* this, void* etc)
{
	CutSceneManagerProp* prop = this->property;
	Animate(this, &prop->mask[0].object[0].transform.position.x, PLAYBACK_ONCE_FORWARD, prop->mask[0].object[1].transform.position.x + 800, EASING_INBACK, 1, NULL);
	Animate(this, &prop->mask[0].object[0].transform.position.y, PLAYBACK_ONCE_FORWARD, prop->mask[0].object[1].transform.position.y - 300, EASING_LINEAR, 1, NULL);
	Animate(this, &prop->mask[0].object[0].transform.rotation, PLAYBACK_ONCE_BACKWARD, 0, EASING_OUTBOUNCE, 1.2, NULL);
	timer.Delay(this, 1, false, cut0_2,NULL);
}

void cut0(GameObject* this)
{
	CutSceneManagerProp* prop = this->property;
	prop->mask[0].image.alpha = 1;
	prop->mask[0].object[0].alpha = 1;
	prop->mask[0].object[0].transform.position.x= 200;
	prop->mask[0].object[0].transform.position.y = -50;
	prop->mask[0].object[0].transform.rotation = 0;
	Animate(this, &prop->mask[0].transform.position.x,PLAYBACK_ONCE_BACKWARD, prop->mask[0].transform.position.x- 1000,EASING_INBACK,2,NULL);
	Animate(this, &prop->mask[0].transform.scale.x, PLAYBACK_ONCE_BACKWARD, 0.3, EASING_INBACK, 2, NULL);
	Animate(this, &prop->mask[0].transform.scale.y, PLAYBACK_ONCE_BACKWARD, 0.3, EASING_INBACK, 2, NULL);
	
	Animate(this, &prop->mask[0].object[0].transform.rotation, PLAYBACK_ONCE_PINGPONG, 10, EASING_INBOUNCE, 2, NULL);
	Animate(this, &prop->mask[0].object[0].transform.position.y, PLAYBACK_ONCE_PINGPONG, prop->mask[0].object[0].transform.position.y -200, EASING_INBACK, 2, NULL);
	Animate(this, &prop->mask[0].object[0].transform.position.x, PLAYBACK_ONCE_PINGPONG, prop->mask[0].object[0].transform.position.x - 100, EASING_INBOUNCE, 2, NULL);

	//obj1
	
	timer.Delay(this, 3, false, cut0_1, NULL);
}

void cut1_2(GameObject* this, void* etc)
{
	CutSceneManagerProp* prop = this->property;
	animation[3] = Animate(this, &prop->bubble[0].transform.scale.x, PLAYBACK_LOOP_PINGPONG, prop->bubble[0].transform.scale.x*1.2, EASING_INELASTIC, 5, NULL);
	animation[4] = Animate(this, &prop->bubble[0].transform.scale.y, PLAYBACK_LOOP_PINGPONG, prop->bubble[0].transform.scale.y * 1.2, EASING_INELASTIC, 5, NULL);

}
void cut1_1(GameObject* this, void * etc)
{
	CutSceneManagerProp* prop = this->property;
	prop->bubble[0].alpha = 1;
	prop->bubble[0].transform.position.x = 1500;
	prop->bubble[0].transform.position.y = 500;
	
	Animate(this, &prop->bubble[0].transform.position.x, PLAYBACK_ONCE_BACKWARD, prop->bubble[0].transform.position.x - 100, EASING_INELASTIC, 0.5, NULL);
	Animate(this, &prop->bubble[0].transform.scale.x, PLAYBACK_ONCE_BACKWARD, 0.1, EASING_INELASTIC, 1, NULL);
	Animate(this, &prop->bubble[0].transform.scale.y, PLAYBACK_ONCE_BACKWARD, 0.1, EASING_INELASTIC, 1, NULL);

	Animate(this, &prop->mask[1].image.transform.position.x, PLAYBACK_ONCE_FORWARD, prop->mask[0].image.transform.position.x - 10, EASING_OUTBOUNCE, 2, NULL);
	Animate(this, &prop->mask[1].image.transform.position.y, PLAYBACK_ONCE_FORWARD, prop->mask[0].image.transform.position.y - 150, EASING_OUTBOUNCE, 2, NULL);
	Animate(this, &prop->bubble[0].transform.position.y, PLAYBACK_ONCE_FORWARD, prop->bubble[0].transform.position.y - 150, EASING_OUTBOUNCE, 3, CompleteShow);
	timer.Delay(this, 3, false, cut1_2, NULL);
}

void cut1(GameObject* this)
{
	CutSceneManagerProp* prop = this->property;
	prop->mask[1].image.alpha = 1;
	
	Animate(this, &prop->mask[1].transform.position.x, PLAYBACK_ONCE_BACKWARD, prop->mask[0].transform.position.x + 700, EASING_INBACK, 2, NULL);
	Animate(this, &prop->mask[1].transform.scale.x, PLAYBACK_ONCE_BACKWARD, 0.3, EASING_INBACK, 2, NULL);
	Animate(this, &prop->mask[1].transform.scale.y, PLAYBACK_ONCE_BACKWARD, 0.3, EASING_INBACK, 2.1, cut1_1);

	
}
void cut2_2(GameObject* this, void* etc)
{
	CutSceneManagerProp* prop = this->property;
	prop->bubble[2].alpha = 0;
	prop->bubble[3].alpha = 1;
	prop->bubble[3].transform.position.x = 1200;
	prop->bubble[3].transform.position.y = 800;
	Animate(this, &prop->bubble[3].transform.scale.x, PLAYBACK_ONCE_BACKWARD, 0.3, EASING_INBACK, 1, NULL);
	Animate(this, &prop->bubble[3].transform.scale.y, PLAYBACK_ONCE_BACKWARD, 0.3, EASING_INBACK, 1, CompleteShow);
	animation[5] = Animate(this, &prop->bubble[3].transform.position.x, PLAYBACK_LOOP_PINGPONG, prop->bubble[3].transform.position.x - 30, EASING_INELASTIC, 5, NULL);
	animation[6] = Animate(this, &prop->bubble[3].transform.position.y, PLAYBACK_LOOP_PINGPONG, prop->bubble[3].transform.position.y + 30, EASING_INELASTIC, 5, NULL);

	DeleteObject(prop->mask[2].image.sprite);
	prop->mask[2].image.sprite = render.LoadBitmapImage(L"Resources\\Opening\\image\\cut3_3.bmp");
}

void cut2_1(GameObject* this, void* etc)
{
	CutSceneManagerProp* prop = this->property;
	prop->bubble[1].alpha = 0;
	prop->bubble[2].alpha = 1;
	prop->bubble[2].transform.position.x = 630;
	prop->bubble[2].transform.position.y = 750;
	
	DeleteObject(prop->mask[2].image.sprite);
	prop->mask[2].image.sprite = render.LoadBitmapImage(L"Resources\\Opening\\image\\cut3_2.bmp");
	timer.Delay(this, 3, false, cut2_2, NULL);
}
void cut2(GameObject* this)
{
	CutSceneManagerProp* prop = this->property;
	prop->mask[2].image.alpha = 1;
	Animate(this, &prop->mask[2].transform.position.x, PLAYBACK_ONCE_BACKWARD, prop->mask[2].transform.position.x - 700, EASING_INBACK, 2, NULL);
	Animate(this, &prop->mask[2].transform.scale.x, PLAYBACK_ONCE_BACKWARD, 0.3, EASING_INBACK, 2, NULL);
	Animate(this, &prop->mask[2].transform.scale.y, PLAYBACK_ONCE_BACKWARD, 0.3, EASING_INBACK, 2, NULL);
	
	timer.Delay(this, 3, false, cut2_1,NULL);
	prop->bubble[1].alpha = 1;
	prop->bubble[1].transform.position.x = 630;
	prop->bubble[1].transform.position.y = 750;
	Animate(this, &prop->bubble[1].transform.position.x, PLAYBACK_ONCE_BACKWARD, prop->mask[2].transform.position.x - 500, EASING_INBACK, 2, NULL);
	Animate(this, &prop->bubble[1].transform.scale.x, PLAYBACK_ONCE_BACKWARD, 0.3, EASING_INELASTIC, 0.1, NULL);
	Animate(this, &prop->bubble[1].transform.scale.y, PLAYBACK_ONCE_BACKWARD, 0.3, EASING_INELASTIC, 0.1, NULL);

}




GameObject* CreateCutSceneManager()
{
	CutSceneManagerProp* property = (CutSceneManagerProp*)malloc(sizeof(CutSceneManagerProp));
	Transform transform = { {960, 560},0,{1,1} };
	Transform defaultTransform = { 0,0,0,1,1 };
	GameObject* obj = CreateGameObject();

	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Draw = CutSceneManagerDraw;
	obj->Update = CutSceneManagerUpdate;
	obj->OnDestroy = CutSceneManagerOnDestroy;
	obj->Start = CutSceneManagerStart;
	obj->property = property;
	property->isClicked = false;
	property->index = 0;
	property->AnimateCutScene[0] = cut0;
	property->AnimateCutScene[1] = cut1;
	property->AnimateCutScene[2] = cut2;
	initilizeCut0(property);
	initilizeCut1(property);
	initilizeCut2(property);
	property->Background= render.LoadBitmapImage(L"Resources\\Opening\\background\\background_paper.bmp");
	property->bubble[0].sprite= render.LoadBitmapImage(L"Resources\\Opening\\image\\Exclamation_mark.bmp");
	property->bubble[0].transform = defaultTransform;
	property->bubble[0].transform.position = defaultTransform.position;
	property->bubble[0].transform.scale = defaultTransform.scale;
	property->bubble[0].alpha = 0;

	property->bubble[1].sprite = render.LoadBitmapImage(L"Resources\\Opening\\image\\speech bubble.bmp");
	property->bubble[1].transform = defaultTransform;
	property->bubble[1].transform.position = defaultTransform.position;
	property->bubble[1].transform.scale = defaultTransform.scale;
	property->bubble[1].alpha = 0;

	property->bubble[2].sprite = render.LoadBitmapImage(L"Resources\\Opening\\image\\speech bubble2.bmp");
	property->bubble[2].transform = defaultTransform;
	property->bubble[2].transform.position = defaultTransform.position;
	property->bubble[2].transform.scale = defaultTransform.scale;
	property->bubble[2].alpha = 0;

	property->bubble[3].sprite = render.LoadBitmapImage(L"Resources\\Opening\\image\\bulb.bmp");
	property->bubble[3].transform = defaultTransform;
	property->bubble[3].transform.position = defaultTransform.position;
	property->bubble[3].transform.scale = defaultTransform.scale;
	property->bubble[3].alpha = 0;

	obj->SetRect(obj, 105, 137);
	obj->SetTag(obj, "PlayBtnInGame");
	obj->renderOrder = UI_ORDER + 1;
	obj->collider = false;
	Showing = false;
	return obj;
}

void initilizeCut0(CutSceneManagerProp* property)
{
	HBITMAP cut = render.LoadBitmapImage(L"Resources\\Opening\\mask\\only_cut1_black.bmp");
	Transform cutTransform = { {910,230},0,{1,1} };
	property->mask[0].sprite = cut;
	property->mask[0].transform = cutTransform;
	property->mask[0].transform.position = cutTransform.position;
	property->mask[0].transform.scale = cutTransform.scale;
	property->mask[0].alpha = 0;
	property->mask[0].length = 1;
	property->mask[0].outline= render.LoadBitmapImage(L"Resources\\Opening\\image\\cut_line_1.bmp");
	//image
	HBITMAP obj = render.LoadBitmapImage(L"Resources\\Opening\\image\\cut1.bmp");
	Transform objTransform = { {0,0},0,{1,1} };
	property->mask[0].image.sprite = obj;
	property->mask[0].image.transform = objTransform;
	property->mask[0].image.transform.position = objTransform.position;
	property->mask[0].image.transform.scale = objTransform.scale;
	property->mask[0].image.alpha = 0;
	property->mask[0].image.transform;

	HBITMAP obj1 = render.LoadBitmapImage(L"Resources\\Opening\\image\\close.bmp");
	Transform obj1Transform = { {0,0},0,{1,1} };
	property->mask[0].object[0].sprite = obj1;
	property->mask[0].object[0].transform = obj1Transform;
	property->mask[0].object[0].transform.position = obj1Transform.position;
	property->mask[0].object[0].transform.scale = obj1Transform.scale;
	property->mask[0].object[0].alpha = 0;
	property->mask[0].object[0].transform;

	HBITMAP obj2 = render.LoadBitmapImage(L"Resources\\Opening\\image\\open.bmp");
	Transform obj2Transform = { {0,0},0,{1,1} };
	property->mask[0].object[1].sprite = obj2;
	property->mask[0].object[1].transform = obj2Transform;
	property->mask[0].object[1].transform.position = obj2Transform.position;
	property->mask[0].object[1].transform.scale = obj2Transform.scale;
	property->mask[0].object[1].alpha = 0;
	property->mask[0].object[1].transform;
	property->mask[0].length = 2;

}

void initilizeCut1(CutSceneManagerProp* property)
{
	HBITMAP cut = render.LoadBitmapImage(L"Resources\\Opening\\mask\\only_cut2_black.bmp");
	Transform cutTransform = { {1000,500},0,{1,1} };
	property->mask[1].sprite = cut;
	property->mask[1].transform = cutTransform;
	property->mask[1].transform.position = cutTransform.position;
	property->mask[1].transform.scale = cutTransform.scale;
	property->mask[1].alpha = 0;
	property->mask[1].outline = render.LoadBitmapImage(L"Resources\\Opening\\image\\cut_line_2.bmp");
	//image
	HBITMAP obj = render.LoadBitmapImage(L"Resources\\Opening\\image\\cut2.bmp");
	Transform objTransform = { {0,0},0,{1,1} };
	property->mask[1].image.sprite = obj;
	property->mask[1].image.transform = objTransform;
	property->mask[1].image.transform.position = objTransform.position;
	property->mask[1].image.transform.scale = objTransform.scale;
	property->mask[1].image.alpha = 0;
	property->mask[1].image.transform;
	property->mask[1].length = 0;
}

void initilizeCut2(CutSceneManagerProp* property)
{
	HBITMAP cut = render.LoadBitmapImage(L"Resources\\Opening\\mask\\only_cut3_black.bmp");
	Transform cutTransform = { {910,850},0,{1,1} };
	property->mask[2].sprite = cut;
	property->mask[2].transform = cutTransform;
	property->mask[2].transform.position = cutTransform.position;
	property->mask[2].transform.scale = cutTransform.scale;
	property->mask[2].alpha = 0;
	property->mask[2].outline = render.LoadBitmapImage(L"Resources\\Opening\\image\\cut_line_3.bmp");
	//image
	HBITMAP obj = render.LoadBitmapImage(L"Resources\\Opening\\image\\cut3_1.bmp");
	Transform objTransform = { {0,0},0,{1,1} };
	property->mask[2].image.sprite = obj;
	property->mask[2].image.transform = objTransform;
	property->mask[2].image.transform.position = objTransform.position;
	property->mask[2].image.transform.scale = objTransform.scale;
	property->mask[2].image.alpha = 0;
	property->mask[2].image.transform;
	property->mask[2].length = 0;
}

void CutSceneManagerStart(GameObject* this)
{
	AUDIO_PlayAudioLoop("Resources\\Sound\\BGM_Opening.wav");
	CutSceneManagerProp* prop = this->property;
	prop->AnimateCutScene[prop->index](this);
	prop->index++;
	Showing = true;
}

void CutSceneManagerUpdate(GameObject* this,double dt)
{
	CutSceneManagerProp* prop = this->property;
	if (input.GetMouseButtonDown(0) && !Showing)
	{
		if (prop->index < NUMBER_OF_CUTS)
		{
			prop->AnimateCutScene[prop->index](this);
			prop->index++;
			Showing = true;
		}
		else
		{
			currentStage = 0;
			ChangeScene(GameScene[2]);
			Showing = true;
		}
		
	}
}



DWORD WINAPI CutSceneManagerDraw(GameObject* this)
{
	CutSceneManagerProp* prop = this->property;
	render.DrawBitmapPreSize(this, prop->Background, 1,1920,1080);
	for (int i = 0; i < NUMBER_OF_MASK; i++)
	{
		DrawMaskedBitmapCoords(this, prop->mask[i].sprite ,900*prop->mask[i].transform.scale.x, 500*prop->mask[i].transform.scale.y, prop->mask[i].transform.position.x, prop->mask[i].transform.position.y, prop->mask[i].alpha, prop->mask[i].image.sprite, prop->mask[i].image.transform.position.x, prop->mask[i].image.transform.position.y, prop->mask[i].image.transform.scale.x, prop->mask[i].image.transform.scale.y, prop->mask[i].image.alpha);
		for (int k = 0; k < prop->mask[i].length; k++)
		{
			DrawMaskedBitmapCoordsM(this, prop->mask[i].sprite, 900 * prop->mask[i].transform.scale.x, 500 * prop->mask[i].transform.scale.y, prop->mask[i].transform.position.x, prop->mask[i].transform.position.y, prop->mask[i].alpha, prop->mask[i].object[k].sprite, prop->mask[i].object[k].transform.position.x, prop->mask[i].object[k].transform.position.y, prop->mask[i].object[k].transform.scale.x, prop->mask[i].object[k].transform.scale.y, prop->mask[i].object[k].transform.rotation, prop->mask[i].object[k].alpha);
		}
		DrawBitmapPre(this, prop->mask[i].outline, prop->mask[i].image.alpha, prop->mask[i].transform.position.x, prop->mask[i].transform.position.y, 900 * prop->mask[i].transform.scale.x, 500 * prop->mask[i].transform.scale.y);
	}
	for (int i = 0; i < 4; i++)
	{
		DrawBitmapPre(this, prop->bubble[i].sprite, prop->bubble[i].alpha, prop->bubble[i].transform.position.x, prop->bubble[i].transform.position.y, 500 * prop->bubble[i].transform.scale.x, 500 * prop->bubble[i].transform.scale.y);
	}
	return 0;
}

void CutSceneManagerOnDestroy(GameObject* this)
{
	CutSceneManagerProp* prop = this->property;
	for (int i = 0; i < NUMBER_OF_LOOP_CUT_ANIMATION; i++)
	{
		CancleAnimate(animation[i]);
	}
	free(prop);
}