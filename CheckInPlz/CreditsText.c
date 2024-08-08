#include "CreditsText.h"
#include <time.h>

//10초 후 
extern Bool creditsBool = false; //현재 재생이 안되고 있을 때 false

static clock_t startTime;
static clock_t endTime;
 
static Bool startOp;
typedef struct CreditsTextProp
{
	
	HBITMAP textPro;
	HBITMAP textProd;
	HBITMAP textArt;
	HBITMAP textDes;

	float creditAlpha;


}CreditsTextProp;

GameObject* CreateCreditsText()
{
	CreditsTextProp* property = (CreditsTextProp*)malloc(sizeof(CreditsTextProp));
	if (property == NULL)
	{
		return NULL;
	}

	Transform transform = { {960,540},0,{1,1} };
	GameObject* obj = CreateGameObject();

	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Start = CreditsTextStart;
	obj->Draw = CreditsTextDraw;
	obj->Update = CreditsTextUpdate;
	obj->OnDestroy = CreditsTextOnDestroy;

	obj->property = property;
	
	property->textArt = LoadBitmapImage(L"Resources\\Credits\\artist2.bmp");
	property->textDes = LoadBitmapImage(L"Resources\\Credits\\designer2.bmp");
	property->textPro = LoadBitmapImage(L"Resources\\Credits\\programmer2.bmp");
	property->textProd = LoadBitmapImage(L"Resources\\Credits\\ending1.bmp");
	property->creditAlpha = 0;
	startOp = false;
	creditsBool = false;

	obj->SetRect(obj, 700, 700);
	obj->SetTag(obj, "CreditsText");
	obj->renderOrder = UI_ORDER+5;
	obj->collider = false;



	return obj;
}


void WaitForCredits()
{
	startOp = true;
}

void SwitchText()
{
	startOp = false;
}

static int txtCount = 0;

void CreditsTextStart(GameObject* this)
{
	Bool creditsBool = true;
	startTime = clock();

	CreditsTextProp* prop = this->property;
	timer.Delay(this, 6, true, WaitForCredits, NULL); //나중에 10초로 수정
	Animate(this, &prop->creditAlpha, PLAYBACK_LOOP_PINGPONG, 1, EASING_LINEAR, 8, NULL);
}

void CreditsTextUpdate(GameObject* this, double dt)
{
	CreditsTextProp* prop = this->property;

	endTime = clock() - startTime;
	float elapsedSeconds = ((float)endTime) / CLOCKS_PER_SEC;


	if (elapsedSeconds >= 0 && elapsedSeconds < 8)
	{
		txtCount = 0;
	}

	if (elapsedSeconds >= 8 && elapsedSeconds < 16)
	{
		txtCount = 1;
	}

	if (elapsedSeconds >= 16 && elapsedSeconds < 24)
	{
		txtCount = 2;
	}

	if (elapsedSeconds > 24 && elapsedSeconds <=32)
	{
		txtCount = 3;
	}

	if (elapsedSeconds > 33)
	{
		ChangeScene(GameScene[0]);
		
		creditsBool = false;
	}
}

DWORD WINAPI CreditsTextDraw(GameObject* this)
{
	CreditsTextProp* prop = this->property;
	if (startOp == true)
	{
		if (txtCount ==0)
		{
			
		}
		else if (txtCount==1)
		{
			
			DrawBitmapWithCustom(this, prop->textDes, prop->creditAlpha, 1556, 895, -400, 100);
		}
		else if (txtCount ==2)
		{
			DrawBitmapWithCustom(this, prop->textArt, prop->creditAlpha, 1553, 899, -400, 100);
		}
		else if (txtCount == 3)
		{
			DrawBitmapWithCustom(this, prop->textPro, prop->creditAlpha, 1540, 896, -400, 0);
		}
	}
	
}

void CreditsTextOnDestroy(GameObject* this)
{
	creditsBool = false;
	timer.CancelAllInObject(this);
	CreditsTextProp* prop = this->property;
	free(prop);
}