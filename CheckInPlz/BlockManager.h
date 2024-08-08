#pragma once

#include "GameObject.h"
#include "Win32Api.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Physics.h"
#include "Block1.h"
#include "Block2.h"
#include "Block3.h"
#include "Ingame.h"

#include "audioModule.h"


DWORD WINAPI BlockManagerDraw(GameObject* this);
void BlockManagerUpdate(GameObject* this, double dt);
void BlockManagerStart(GameObject* this);
void BlockManagerOnDestroy(GameObject* this);





typedef struct BlockManagerProp
{
	int Row;
	int Column;
	int Offset;
	int blockNum;
	Bool enableBlock;
	HBITMAP block1[3];
	HBITMAP block2;
	HBITMAP block3;
}BlockManagerProp;

BlockType CurrentBlockType;
extern int BlockCost[3];
extern Bool BlockManagerActive;
extern GameObject* CreateBlockManager();
extern void ClearBoard(GameObject* this);
Bool IsPlaying;