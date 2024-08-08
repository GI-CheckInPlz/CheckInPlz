#include "MonsterBook.h"

Bool toggleDebug;

typedef struct MonsterBookProp
{
	Bool isExtended;
	HBITMAP sprite;
	MonsterBookItem item[4];
}MonsterBookProp;

static float m_posx[6] = { -1000, 120, 50, -20, -90, -160 };
static float m_posy[3] = {135,0,-135};
GameObject* CreateMonsterBook()
{
	MonsterBookProp* property = (MonsterBookProp*)malloc(sizeof(MonsterBookProp));
	if (property == NULL)
	{
		return NULL;
	}
	Transform transform = { {-170,650},0,{1,1} };
	GameObject* obj = CreateGameObject();
	property->isExtended = false;
	property->sprite = render.LoadBitmapImage(L"Resources\\Map\\MonsterBookExtended.bmp");
	/*vector2 pos0 = { -300,-250 };
	property->item[0].position = pos0;
	vector2 pos1 = { 0,-250 };
	property->item[1].position = pos1;
	vector2 pos2 = { 300,-250 };
	property->item[2].position = pos2;
	property->item[0].content = render.LoadBitmapImage(L"Resources\\blocks\\1_1.bmp");
	property->item[1].content = render.LoadBitmapImage(L"Resources\\blocks\\2.bmp");
	property->item[2].content = render.LoadBitmapImage(L"Resources\\blocks\\3.bmp");

	property->item[0].size = 1;
	property->item[1].size = 1;
	property->item[2].size = 1;*/

	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Start = MonsterBookStart;
	obj->Draw = MonsterBookDraw;
	obj->Update = MonsterBookUpdate;

	obj->property = property;

	obj->SetRect(obj, 500, 600);
	obj->SetTag(obj, "MonsterBook");
	obj->renderOrder = UI_ORDER + 10;
	obj->collider = false;
	obj->OnDestroy = MonsterBookOnDestroy;

	return obj;
}



void MonsterBookStart(GameObject* this)
{

}

void MonsterBookExtendChange(GameObject* this, void* etc)
{
	MonsterBookProp* prop = this->property;
	if (prop->isExtended)
	{
		this->SetRect(this, 500, 600);
	}
	else
	{
		this->SetRect(this, 500, 600);
	}
}

void MonsterBookUpdate(GameObject* this, double dt)
{
	MonsterBookProp* prop = this->property;
	vector2 mousePos = GetMousePosition();
	
	if (!IsPlaying && physics.InBound(this, mousePos))
	{
		if (!prop->isExtended)
		{
			Animate(this, &this->transform.position.x, PLAYBACK_ONCE_FORWARD, 200, EASING_OUTSINE, 0.5, MonsterBookExtendChange);
		}
		prop->isExtended = true;
	}
	else
	{
		if (prop->isExtended)
		{
			Animate(this, &this->transform.position.x, PLAYBACK_ONCE_FORWARD, -170, EASING_OUTELASTIC, 0.5, MonsterBookExtendChange);
		}
		prop->isExtended = false;
	}

}

void MonsterBookOnDestroy(GameObject* this)
{
	free(this->property);
}



DWORD WINAPI MonsterBookDraw(GameObject* this)
{
	MonsterBookProp* prop = this->property;
	render.DrawBitmapPre(this, prop->sprite, 1, (int)(this->transform.position.x+65), (int)(this->transform.position.y), 500, 600);
	
	for (int i=0; i<sequenceList->count;i++)
	{
		render.DrawBitmapPre(this, MonsterBitmap[sequenceList->Content[i]->type], 1, (int)(this->transform.position.x + m_posx[(int)sequenceList->Content[i]->delay]), (int)(this->transform.position.y+ m_posy[sequenceList->Content[i]->floor]), 150, 150);
	}

#if DEBUG
	if (toggleDebug)
	{
		DrawDebugRectangle(this);
	}
	
#endif
	return 0;
}


