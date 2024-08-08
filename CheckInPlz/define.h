#pragma once

#include<stdlib.h>
#include <stdio.h>
#include "framework.h"
#include "resource.h"
#include "type.h"
#include "vmath.h"

//debug 모드
#define DEBUG 1

#define MAX_TIMER 1000 //타이머가 셀 수 있는 최대한의 초
#define MAX_GAMEOBJECT 1000 //한 씬 안에 있을 수 있는 최대한의 겜옵젝 수
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
typedef struct Screen //스크린 구조체
{
	vector2 resolution; //vector2에서 x는 가로 해상도, y는 세로 해상도
}Screen;

typedef struct Transform
{
	vector2 position; //vector2 형태로 x,y 좌표 저장 (위치)
	float rotation; //기운 정도
	vector2 scale; //x,y는 차례로 가로, 세로 비율.
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