#pragma once
#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "Physics.h"
#include "Tween.h"
#include "Animation.h"
#include "BlockManager.h"
#include "StageManager.h"
#include "audioModule.h"
#include "Debug.h"

typedef struct MonsterBookProp MonsterBookProp;

extern GameObject* CreateMonsterBook();

void MonsterBookStart(GameObject* this);
void MonsterBookUpdate(GameObject* this, double dt);
void MonsterBookOnDestroy(GameObject* this);

DWORD WINAPI MonsterBookDraw(GameObject* this);

typedef struct MonsterBookItem {
	HBITMAP content;
	int price;
	vector2 position;
	float size;
	rect2D area;
}MonsterBookItem;
SequenceList* sequenceList;
