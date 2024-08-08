#pragma once

#include<stdlib.h>
#include <stdio.h>
#include "framework.h"
#include "resource.h"
#include "type.h"
#include "vmath.h"

//debug ���
#define DEBUG 1

#define MAX_TIMER 1000 //Ÿ�̸Ӱ� �� �� �ִ� �ִ����� ��
#define MAX_GAMEOBJECT 1000 //�� �� �ȿ� ���� �� �ִ� �ִ����� �׿��� ��
#define false 0
#define true 1
#define nullptr NULL
#define PI	3.141592654
#define public extern
//ORDER
#define UI_ORDER 10
#define MONSTER_ORDER 4
#define BLOCK_OFFSET 100


#define KIND_OF_MONSTER 5
#define FLOOR_DEPTH 3
#define NUMBER_OF_STAGE 4

typedef struct GameObject GameObject;
typedef struct Screen //��ũ�� ����ü
{
	vector2 resolution; //vector2���� x�� ���� �ػ�, y�� ���� �ػ�
}Screen;

typedef struct Transform
{
	vector2 position; //vector2 ���·� x,y ��ǥ ���� (��ġ)
	float rotation; //��� ����
	vector2 scale; //x,y�� ���ʷ� ����, ���� ����.
}Transform;

typedef void(*callBack)(GameObject*,void* etc);
typedef GameObject*(*Constructor)();
typedef enum BlockType {
	DefaultBlock,
	SlowBlock,
	JumpBlock,
	Empty
}BlockType;

typedef struct Cell {
	vector2 position;
	GameObject* block;
	BlockType type;
}Cell;