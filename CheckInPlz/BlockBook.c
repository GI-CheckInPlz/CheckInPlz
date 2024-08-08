#include "BlockBook.h"
Bool toggleDebug;
typedef struct BlockBookProp
{
	Bool isExtended;
	HBITMAP sprite;
	HBITMAP coin;
	Item item[4];
}BlockBookProp;



GameObject* CreateBlockBook()
{
	BlockBookProp* property = (BlockBookProp*)malloc(sizeof(BlockBookProp));
	if (property == NULL)
	{
		return NULL;
	}
	Transform transform = { {950,1400},0,{1,1} };
	GameObject* obj = CreateGameObject();
	property->isExtended = false;
	property->sprite = render.LoadBitmapImage(L"Resources\\Map\\extendedUIBook.bmp");
	property->coin = LoadBitmapImage(L"Resources\\Map\\Coin.bmp");
	vector2 pos0= { -300,- 250 };
	property->item[0].position = pos0;
	vector2 pos1= { 0,-250 };
	property->item[1].position = pos1;
	vector2 pos2 = { 300,-250 };
	property->item[2].position = pos2;
	property->item[0].content = render.LoadBitmapImage(L"Resources\\blocks\\1_1.bmp");
	property->item[1].content = render.LoadBitmapImage(L"Resources\\blocks\\2.bmp");
	property->item[2].content = render.LoadBitmapImage(L"Resources\\blocks\\3.bmp");
	
	property->item[0].size = 1;
	property->item[1].size = 1;
	property->item[2].size = 1;

	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Start = BlockBookStart;
	obj->Draw = BlockBookDraw;
	obj->Update = BlockBookUpdate;

	obj->property = property;
	
	obj->SetRect(obj, 900, 900);
	obj->SetTag(obj, "BottomUI");
	obj->renderOrder = UI_ORDER+10;
	obj->collider = false;
	obj->OnDestroy = BlockBookOnDestroy;

	return obj;
}


void BlockBookStart(GameObject* this)
{
	
}
void ExtendChange(GameObject* this, void* etc)
{
	BlockBookProp* prop = this->property;
	if (prop->isExtended)
	{
		this->SetRect(this, 900, 700);
	}
	else
	{
		this->SetRect(this, 900, 900);
	}
}

void BlockBookUpdate(GameObject* this, double dt)
{
	BlockBookProp* prop = this->property;
	vector2 mousePos = GetMousePosition();
	if (physics.InBoundRect(prop->item[0].area, mousePos))
	{
		if (input.GetMouseButtonDown(0))
		{
			CurrentBlockType = 0;
		}
		prop->item[0].size = 1.2f;
	}
	else
	{
		prop->item[0].size = 1;
	}

	if (physics.InBoundRect(prop->item[1].area, mousePos))
	{
		if (input.GetMouseButtonDown(0))
		{
			CurrentBlockType = 1;
		}
		prop->item[1].size = 1.2f;
	}
	else
	{
		prop->item[1].size = 1;
	}

	if (physics.InBoundRect(prop->item[2].area, mousePos))
	{
		if (input.GetMouseButtonDown(0))
		{
			CurrentBlockType = 2;
		}
		prop->item[2].size = 1.2f;
	}
	else
	{
		prop->item[2].size = 1;
	}

	if (!IsPlaying && physics.InBound(this, mousePos) )
	{
		if (!prop->isExtended)
		{
			Animate(this, &this->transform.position.y, PLAYBACK_ONCE_FORWARD, 1200, EASING_OUTSINE, 0.5, ExtendChange);
		}
		prop->isExtended = true;
		BlockManagerActive = false;
	}
	else
	{
		if (prop->isExtended)
		{
			Animate(this, &this->transform.position.y, PLAYBACK_ONCE_FORWARD, 1400, EASING_OUTELASTIC, 0.5, ExtendChange);
		}
		BlockManagerActive = true;
		prop->isExtended = false;
	}	
	rect2D rect0 = { { this->transform.position.x + prop->item[0].position.x - 100,this->transform.position.y + prop->item[0].position.y - 100 }, { this->transform.position.x + prop->item[0].position.x + 100,this->transform.position.y + prop->item[0].position.y + 100 } };
	prop->item[0].area = rect0;

	rect2D rect1 = { { this->transform.position.x + prop->item[1].position.x - 100,this->transform.position.y + prop->item[1].position.y - 100 }, { this->transform.position.x + prop->item[1].position.x + 100,this->transform.position.y + prop->item[1].position.y + 100 } };
	prop->item[1].area = rect1;

	rect2D rect2 = { { this->transform.position.x + prop->item[2].position.x - 100,this->transform.position.y + prop->item[2].position.y - 100 }, { this->transform.position.x + prop->item[2].position.x + 100,this->transform.position.y + prop->item[2].position.y + 100 } };
	prop->item[2].area = rect2;

}

void BlockBookOnDestroy(GameObject* this)
{
	free(this->property);
}



DWORD WINAPI BlockBookDraw(GameObject* this)
{
	BlockBookProp* prop = this->property;
	render.DrawBitmapPre(this, prop->sprite, 1, (int)this->transform.position.x, (int)(this->transform.position.y-300), 1200, 350);
	for (int i = 0; i < 3; i++)
	{
		_TCHAR strCoin[200];
		vector2 pos = { this->transform.position.x + prop->item[i].position.x, this->transform.position.y + prop->item[i].position.y };
		render.DrawBitmapPre(this, prop->item[i].content, 1, (int)pos.x, (int)pos.y, (int)(100* prop->item[i].size), (int)(100 * prop->item[i].size));
		render.DrawBitmapPre(this, prop->coin, 1, (int)(pos.x - 60), (int)(pos.y - 100), 75, 75);
		rect2D rect = { { prop->item[i].position.x-75,  prop->item[i].position.y-110 }, { prop->item[i].position.x+75, prop->item[i].position.y+100 }};
		wsprintf(strCoin, TEXT("%d"), BlockCost[i]);
		render.DrawTextPre(this, strCoin, rect, DT_CENTER | DT_WORDBREAK, TEXT("Cinzel Decorative"), 40, 1000, RGB(0, 0, 0), RGB(5, 5, 0));
	}
	//render.DrawRectangle(this, this->rect.max.x - this->rect.min.x, this->rect.max.y - this->rect.min.y, RGB(255, 0, 0), RGB(255, 0, 0));
#if DEBUG
	if (toggleDebug)
	{
		DrawDebugRectangle(this);
	}
#endif
	return 0;
}


