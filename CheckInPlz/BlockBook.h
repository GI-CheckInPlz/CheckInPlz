#pragma once
#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "Physics.h"
#include "Tween.h"
#include "Animation.h"
#include "BlockManager.h"

#include "audioModule.h"

typedef struct BlockBookProp BlockBookProp;

extern GameObject* CreateBlockBook();

void BlockBookStart(GameObject* this);

void BlockBookUpdate(GameObject* this, double dt);

BlockType CurrentBlockType;
void BlockBookOnDestroy(GameObject* this);
DWORD WINAPI BlockBookDraw(GameObject* this);

typedef struct Item {
	HBITMAP content;
	int price;
	vector2 position;
	float size;
	rect2D area;
}Item;

