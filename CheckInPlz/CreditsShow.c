#include "CreditsShow.h"

//10ÃÊ ÈÄ 

typedef struct CreditsProp
{
	HBITMAP backgroundOne;
	HBITMAP backgroundTwo;
	//HBITMAP textPro;
	//HBITMAP textArt;
	//HBITMAP textDes;

	//HBITMAP currentShow;

	Animation* creditsAnim;

	//float creditAlpha;
	
}CreditsProp;

GameObject* CreateCredits()
{
	CreditsProp* property = (CreditsProp*)malloc(sizeof(CreditsProp));
	if (property == NULL)
	{
		return NULL;
	}

	Transform transform = { {960,540},0,{1,1} };
	GameObject* obj = CreateGameObject();

	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Start = CreditsStart;
	obj->Draw = CreditsDraw;
	obj->Update = CreditsUpdate;
	obj->OnDestroy = CreditsOnDestroy;

	obj->property = property;
	property->backgroundOne = LoadBitmapImage(L"Resources\\Credits\\ending1.bmp");
	property->backgroundTwo = LoadBitmapImage(L"Resources\\Credits\\ending2.bmp");
	//property->textArt = LoadBitmapImage(L"Resources\\Credits\\ArtistCredits.bmp");
	//property->textDes = LoadBitmapImage(L"Resources\\Credits\\DesignerCredits.bmp");
	//property->textPro = LoadBitmapImage(L"Resources\\Credits\\ProgrammerCredits.bmp");
	//property->creditAlpha = 1;

	
	property->creditsAnim = CreateAnimation();
	property->creditsAnim->PushImage(property->creditsAnim, L"Resources\\Credits\\ending1.bmp");
	property->creditsAnim->PushImage(property->creditsAnim, L"Resources\\Credits\\ending2.bmp");

	obj->SetRect(obj, 1920, 1080);
	obj->SetTag(obj, "Credits");
	obj->renderOrder = UI_ORDER+2;
	obj->collider = false;
	return obj;
}

void CreditsStart(GameObject* this)
{
	AUDIO_PlayAudioLoop("Resources\\Sound\\BGM_Ending.wav");
	CreditsProp* prop = this->property;
	prop->creditsAnim->Play(this, prop->creditsAnim, 1.2f, true);
}

void CreditsUpdate(GameObject* this, double dt)
{

}

DWORD WINAPI CreditsDraw(GameObject* this)
{
	CreditsProp* prop = this->property;
	prop->creditsAnim->Draw(this, prop->creditsAnim, 2);
}

void CreditsOnDestroy(GameObject* this)
{
	CreditsProp* prop = this->property;
	CancelAnimation(prop->creditsAnim);
	DestoryAnimation(prop->creditsAnim);
	free(prop);
}