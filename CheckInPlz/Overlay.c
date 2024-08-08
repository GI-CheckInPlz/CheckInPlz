#include "Overlay.h"

GameObject* CreateOverlay()
{
	OverlayProp* property = (OverlayProp*)malloc(sizeof(OverlayProp));
	if (property == NULL)
	{
		return NULL;
	}

	Transform transform = { {960, 560},0,{1,1} };
	GameObject* obj = CreateGameObject();

	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Start = OverlayStart;
	obj->Draw = OverlayDraw;
	obj->OnDestroy = OverlayOnDestroy;
	obj->property = property;

	property->retrySprite = LoadBitmapImage(L"Resources\\Map\\Retry.bmp");
	property->clearSprite = LoadBitmapImage(L"Resources\\Map\\Clear.bmp");
	property->stageSprite[0] = LoadBitmapImage(L"Resources\\Map\\Stage1.bmp");
	property->stageSprite[1] = LoadBitmapImage(L"Resources\\Map\\Stage2.bmp");
	property->stageSprite[2] = LoadBitmapImage(L"Resources\\Map\\Stage3.bmp");
	property->stageSprite[3] = LoadBitmapImage(L"Resources\\Map\\Stage4.bmp");

	property->isClicked = false;
	property->fadeClear = 0;
	property->fadeRetry = 0;
	property->fadeFilter = 0;
	property->fadeStage[0] = 0;
	property->fadeStage[1] = 0;
	property->fadeStage[2] = 0;
	property->fadeStage[3] = 0;
	obj->SetRect(obj, 105, 137);
	obj->SetTag(obj, "PlayBtnInGame");
	obj->renderOrder = UI_ORDER+1;
	obj->collider = false;

	return obj;
}

void OverlayStart(GameObject* this)
{
	AUDIO_PlayAudioLoop("Resources\\Sound\\BGM_Stage.wav");
	AUDIO_PlayAudio("Resources\\Sound\\StageStart.wav", 6);
}

DWORD WINAPI OverlayDraw(GameObject* this)
{
	OverlayProp* prop = this->property;
	render.DrawRectangle(this, 900, 800, RGB(30, 20, 0), RGB(30, 20, 0),prop->fadeFilter);
	render.DrawBitmap(this, prop->retrySprite, prop->fadeRetry);
	render.DrawBitmap(this, prop->clearSprite, prop->fadeClear);
	render.DrawBitmap(this, prop->stageSprite[0], prop->fadeStage[0]);
	render.DrawBitmap(this, prop->stageSprite[1], prop->fadeStage[1]);
	render.DrawBitmap(this, prop->stageSprite[2], prop->fadeStage[2]);
	render.DrawBitmap(this, prop->stageSprite[3], prop->fadeStage[3]);
	return 0;
}

void OverlayOnDestroy(GameObject* this)
{
	OverlayProp* prop = this->property;
	free(prop);
}