#include "CoinInGame.h"

typedef struct CoinInGameProp
{
	HBITMAP coin;
	HBITMAP panel;
	int preCoin;
	float textHeight;
	AnimationData* AnimateHandler;
}CoinInGameProp;

GameObject* CreateCoinInGame()
{
	CoinInGameProp* property = (CoinInGameProp*)malloc(sizeof(CoinInGameProp));
	if (property == NULL)
	{
		return NULL;
	}

	Transform transform = { {385,185},0,{1,1} };
	GameObject* obj = CreateGameObject();

	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Start = CoinInGameStart;
	obj->Draw = CoinInGameDraw;
	obj->Update = CoinInGameUpdate;

	obj->property = property;
	property->coin = LoadBitmapImage(L"Resources\\Map\\Coin.bmp");
	property->panel = LoadBitmapImage(L"Resources\\Map\\Panel.bmp");
	property->preCoin = CurrentCoin;
	property->textHeight = 60;
	obj->SetRect(obj, 82, 82);
	obj->SetTag(obj, "CoinInGame");
	obj->renderOrder = UI_ORDER;
	obj->collider = false;
	obj->OnDestroy = CoinInGameOnDestroy;

	return obj;
}

void CoinInGameStart(GameObject* this)
{

}

void CoinInGameUpdate(GameObject* this, double dt)
{
	CoinInGameProp* prop = this->property;
	if (prop->preCoin != CurrentCoin)
	{
		prop->textHeight = 60;
		Animate(this, &prop->textHeight, PLAYBACK_ONCE_PINGPONG, 40, EASING_INOUTBOUNCE, 0.4f, NULL);
	}
	prop->preCoin = CurrentCoin;
}

DWORD WINAPI CoinInGameDraw(GameObject* this)
{
	_TCHAR strCoin[200];
	wsprintf(strCoin, TEXT("%d"), CurrentCoin);
	CoinInGameProp* prop = this->property;
	render.DrawBitmapPre(this, prop->panel, 1, (int)(this->transform.position.x), (int)(this->transform.position.y + 80), 175, 100);
	render.DrawBitmapPre(this, prop->coin, 1, (int)(this->transform.position.x), (int)(this->transform.position.y+20), 82, 82);
	rect2D rect = { - 100,30, 100, 130 };
	render.DrawTextPre(this, strCoin,rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER, TEXT("Cinzel Decorative"),(int)prop->textHeight, 1000,RGB(245,255,200), RGB(5, 5, 0));
	return 0;
}

void CoinInGameOnDestroy(GameObject* this)
{
	free(this->property);
}