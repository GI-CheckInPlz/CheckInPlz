#include "BlockManager.h"

int BlockCost[3] = {
	50,
	150,
	200
};
Bool BlockManagerActive;
Cell** Board;
GameObject* CreateBlockManager()
{
	Transform transform = { {500,160}, 0, {1,1} };
	BlockManagerProp* property = (BlockManagerProp*)malloc(sizeof(BlockManagerProp));
	if (property == NULL)
	{
		return NULL;
	}
	property->Row = 8;
	property->Column = 9;
	property->Offset = BLOCK_OFFSET;
	property->enableBlock = true;;
	property->block1[0] = render.LoadBitmapImage(L"Resources\\blocks\\1_1.bmp");
	property->block1[1] = render.LoadBitmapImage(L"Resources\\blocks\\1_2.bmp");
	property->block1[2] = render.LoadBitmapImage(L"Resources\\blocks\\1_3.bmp");
	property->block2 = render.LoadBitmapImage(L"Resources\\blocks\\2.bmp");
	property->block3 = render.LoadBitmapImage(L"Resources\\blocks\\3.bmp");
	GameObject* obj = CreateGameObject();
	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Draw = BlockManagerDraw;
	obj->Start = BlockManagerStart;
	obj->Update = BlockManagerUpdate;
	obj->renderOrder = 4;
	obj->property = property;
	obj->SetRect(obj, property->Column * property->Offset, property->Row*property->Offset);
	obj->SetTag(obj, "BlockArea");
	obj->collider = false;
	Board = (Cell**)malloc(sizeof(Cell*) * property->Row);
	if (Board == NULL)
	{
		return NULL;
	}
	for (int i = 0; i < property->Row; i++)
	{
		Board[i] = (Cell*)malloc(sizeof(Cell) * property->Column);
		if (Board[i] == NULL)
		{
			return NULL;
		}
		for (int j = 0; j < property->Column; j++)
		{
			vector2 pos = { transform.position.x+property->Offset * j+ property->Offset/2,transform.position.y + property->Offset * i + property->Offset / 2 };
			Board[i][j].position = pos;
			Board[i][j].block = NULL;
			Board[i][j].type = Empty;
		}
	}
	obj->OnDestroy = BlockManagerOnDestroy;
	BlockManagerActive = true;
	CurrentBlockType = DefaultBlock;
	return obj;
}

void ClearBoard(GameObject* this)
{
	BlockManagerProp* prop = this->property;
	for (int i = 0; i < prop->Row; i++)
	{
		for (int j = 0; j < prop->Column; j++)
		{
			if (Board[i][j].block)
			{
				Destroy(Board[i][j].block);
				Board[i][j].block = NULL;
				Board[i][j].type = Empty;
			}
		}
	}

}

void DrawBlock(GameObject* this, HBITMAP bmp, float alpha,int pos_x, int pos_y,int size_x,int size_y)
{
	static HDC tmp;
	static HDC tmpAlpha;
	HBITMAP OldBit = (HBITMAP)SelectObject(MemDC, hBit);
	BITMAP btSize;
	HBITMAP tBit;
	HBITMAP hOldBitmap;
	tmp = CreateCompatibleDC(hdc);
	tmpAlpha = CreateCompatibleDC(hdc);

	GetObject(bmp, sizeof(BITMAP), &(btSize));
	tBit = CreateCompatibleBitmap(hdc, (int)(screen.resolution.x), (int)(screen.resolution.y));
	SelectObject(tmpAlpha, tBit);
	hOldBitmap = (HBITMAP)SelectObject(tmp, bmp);
	pos_x = pos_x - size_x / 2;
	pos_y = pos_y - size_y / 2;
	BLENDFUNCTION bf;
	bf.AlphaFormat = 0; // 비트맵 종류로 일반 비트맵의 경우 0, 32비트 비트맵의 경우 AC_SRC_ALPHA
	bf.BlendFlags = 0; // 무조건 0이어야 한다
	bf.BlendOp = AC_SRC_OVER; // 무조건 AC_SRC_OVER이어야 하고 원본과 대상 이미지를 합친다는 의미
	bf.SourceConstantAlpha = 255 * alpha; // 투명도(투명 0 - 불투명 255)
	//BitBlt(tmpAlpha, pos_x, pos_y, size_x, size_y, MemDC[this->renderOrder], pos_x, pos_y, SRCCOPY);
	BitBlt(tmpAlpha, 0, 0, size_x, size_y, MemDC, pos_x, pos_y, SRCCOPY);
	TransparentBlt(tmpAlpha, 0, 0, size_x, size_y, tmp, 0, 0, btSize.bmWidth, btSize.bmHeight, RGB(255, 0, 255));
	if (alpha < 1)
	{
		AlphaBlend(MemDC, pos_x, pos_y, size_x, size_y, tmpAlpha, 0, 0, size_x, size_y, bf);
	}
	else
	{
		BitBlt(MemDC, pos_x, pos_y, size_x, size_y, tmpAlpha, 0, 0, SRCCOPY);
	}

	SelectObject(tmp, hOldBitmap);
	DeleteObject(tBit);
	DeleteDC(tmp);
	DeleteDC(tmpAlpha);
}

void DrawGridBox(GameObject* this, int size_x, int size_y, COLORREF penColor, vector2 pos)
{

	HPEN hNewPen = CreatePen(PS_SOLID, 3, penColor);
	HPEN hOldPen = (HPEN)SelectObject(MemDC, hNewPen);

	HBRUSH hNewBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(MemDC, hNewBrush);

	Transform transform = this->transform;
	vector2 size = { size_x * transform.scale.x, size_y * transform.scale.x };
	Rectangle(MemDC, (int)(pos.x - size.x / 2), (int)(pos.y - size.y / 2), (int)(pos.x + size.x / 2), (int)(pos.y + size.y / 2));

	SelectObject(MemDC, hOldPen);
	DeleteObject(hNewPen);

	SelectObject(MemDC, hOldBrush);
	DeleteObject(hNewBrush);
}

DWORD WINAPI BlockManagerDraw(GameObject* this)
{
	BlockManagerProp* prop = this->property;
	vector2 mousePos = input.GetMousePosition();
	int divideX = (int)(mousePos.x - this->transform.position.x) / prop->Offset;
	int divideY = (int)(mousePos.y - this->transform.position.y ) / prop->Offset;
	int deltaColor = 15;
	int baseColor = 90;
	mousePos.x = mousePos.x - prop->Offset * prop->Column / 2;
	mousePos.y = mousePos.y - prop->Offset * prop->Row / 2;


	if (!IsPlaying && BlockManagerActive && physics.InBound(this, mousePos))
	{
		
		if (!Board[divideY][divideX].block)
		{
			switch (CurrentBlockType)
			{
			case DefaultBlock:
				DrawBlock(this, prop->block1[prop->blockNum % 3], 0.7f, (int)(Board[divideY][divideX].position.x), (int)(Board[divideY][divideX].position.y), prop->Offset, prop->Offset);
				break;
			case SlowBlock:
				DrawBlock(this, prop->block2, 0.7f, (int)Board[divideY][divideX].position.x, (int)Board[divideY][divideX].position.y, prop->Offset, prop->Offset);
				break;
			case JumpBlock:
				DrawBlock(this, prop->block3, 0.7f, (int)Board[divideY][divideX].position.x, (int)Board[divideY][divideX].position.y, prop->Offset, prop->Offset);
				break;
			}
		}
		for (int i = 0; i < prop->Row; i++)
		{
			for (int j = 0; j < prop->Column; j++)
			{
				int color = abs(divideX - j) * deltaColor + abs(divideY - i) * deltaColor > baseColor ? baseColor : abs(divideX - j) * deltaColor + abs(divideY - i) * deltaColor;
				vector2 pos = { Board[i][j].position.x, Board[i][j].position.y };
				if (i == divideY && j == divideX)
					DrawGridBox(this, prop->Offset, prop->Offset, RGB(100, 100, 255), pos);
				else
					DrawGridBox(this, prop->Offset, prop->Offset, RGB(100 + color, 100 + color, 50 + color), pos);
			}
		}
	}
	else
	{
		for (int i = 0; i < prop->Row; i++)
		{
			for (int j = 0; j < prop->Column; j++)
			{
				vector2 pos = { Board[i][j].position.x, Board[i][j].position.y };
				DrawGridBox(this, prop->Offset, prop->Offset, RGB(100 + baseColor, 100 + baseColor, 50 + baseColor), pos);
			}
		}

	}

	return 0;
}
void EnableBlock(GameObject* this, void *etc)
{
	BlockManagerProp* prop = this->property;
	prop->enableBlock = true;
}

void BlockManagerUpdate(GameObject* this, double dt)
{
	BlockManagerProp* prop = this->property;
	//vector2 pos = this->transform.position;
	vector2 mousePos = input.GetMousePosition();

	//블록이 그리드의 중앙에 배치되게
	int divideX = (int)(mousePos.x - this->transform.position.x) / prop->Offset;
	int divideY = (int)(mousePos.y - this->transform.position.y) / prop->Offset;
	mousePos.x = mousePos.x - prop->Offset * prop->Column / 2;
	mousePos.y = mousePos.y - prop->Offset * prop->Row / 2;

	//BlockShift
#if DEBUG
	if (input.GetKeyDown(VK_SPACE))
	{
		if (CurrentBlockType == DefaultBlock)
		{
			CurrentBlockType = SlowBlock;
		}
		else if (CurrentBlockType == SlowBlock)
		{
			CurrentBlockType = JumpBlock;
		}
		else if (CurrentBlockType == JumpBlock)
		{
			CurrentBlockType = DefaultBlock;
		}
	}
#endif
	if (!IsPlaying && BlockManagerActive && input.GetMouseButtonDown(0) && physics.InBound(this, mousePos) && Board[divideY][divideX].block==NULL && CurrentCoin >= BlockCost[CurrentBlockType])
	{
		GameObject* newTypeBlock;
		switch (CurrentBlockType)
		{
		case DefaultBlock:
			newTypeBlock = CreateBlock1(prop->block1[prop->blockNum%3], prop->Offset);
			newTypeBlock->transform.position.x = Board[divideY][divideX].position.x;
			newTypeBlock->transform.position.y = Board[divideY][divideX].position.y;
			Board[divideY][divideX].block = newTypeBlock;
			Instantiate(newTypeBlock);
			AUDIO_PlayAudio("Resources\\Sound\\BlockCraft.wav", 2);
			break;
		case SlowBlock:
			newTypeBlock = CreateBlock2(prop->block2, prop->Offset);
			newTypeBlock->transform.position.x = Board[divideY][divideX].position.x;
			newTypeBlock->transform.position.y = Board[divideY][divideX].position.y;
			Board[divideY][divideX].block = newTypeBlock;
			Instantiate(newTypeBlock);
			AUDIO_PlayAudio("Resources\\Sound\\ExBlockCraft.wav", 2);
			break;
		case JumpBlock:
			newTypeBlock = CreateBlock3(prop->block3, prop->Offset);
			newTypeBlock->transform.position.x = Board[divideY][divideX].position.x;
			newTypeBlock->transform.position.y = Board[divideY][divideX].position.y;
			Board[divideY][divideX].block = newTypeBlock;
			Instantiate(newTypeBlock);
			AUDIO_PlayAudio("Resources\\Sound\\ExBlockCraft.wav", 2);
			break;
		}
		if (CurrentBlockType < 0)
		{
			return;
		}
		CurrentCoin-=BlockCost[CurrentBlockType];
		Board[divideY][divideX].type = CurrentBlockType;
		prop->blockNum = rand();
	}


	if (!IsPlaying && input.GetMouseButtonDown(1) && physics.InBound(this, mousePos) && Board[divideY][divideX].block != NULL)
	{
		CurrentCoin += BlockCost[Board[divideY][divideX].type];
		Destroy(Board[divideY][divideX].block);
		Board[divideY][divideX].block = NULL;
		Board[divideY][divideX].type = Empty;
		AUDIO_PlayAudio("Resources\\Sound\\BlockDelete.wav", 1);
	}

}

void BlockManagerStart(GameObject* this)
{
	BlockManagerProp* prop = this->property;
	srand(time(NULL));
	prop->blockNum = rand();
}

void BlockManagerOnDisable(GameObject* this)
{
	BlockManagerProp* prop = this->property;
	for (int i = 0; i < prop->Row; i++)
	{
		for (int j = 0; j < prop->Column; j++)
		{
			free(Board[i][j].block);
		}
		free(Board[i]);
	}
	free(Board);
}

void BlockManagerOnDestroy(GameObject* this)
{
	free(this->property);
}