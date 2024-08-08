#pragma once
#include "define.h"
#include "BasicMonster.h"
#include "Monster2.h"
#include "Monster3.h"
#include "Monster4.h"
#include "Monster5.h"
#include "GameObjectList.h"
#include "Timer.h"
#include "SequenceList.h"


static Constructor MonsterConstructor[KIND_OF_MONSTER];
extern HBITMAP MonsterBitmap[KIND_OF_MONSTER];
extern GameObjectList* MonsterList;
static vector2 floorPosition[FLOOR_DEPTH] = {
		{0,850},
		{0,650},
		{0,450}
};


extern SequenceList* sequenceList;

typedef struct Solution {
	HBITMAP sprite;
	int type;
}Solution;

typedef struct StageData
{
	char MonsterFileName[30];
	char SolutionFileName[30];
	int coin;
}StageData;


extern StageData stageData[NUMBER_OF_STAGE];
extern Solution StageSolution[4][2];
int StageSolutionType[4][2];
extern Bool PlayerSolution[4][2];
static int StageCoin;
void GenerateSolution(GameObject* this, char* filename);
extern void InitializeStageManager(GameObject* this, char* monsterfilename, char* solutionfilename);
void GenerateMonster(GameObject* this);
static void GenerateSquence(GameObject* this, char* filename);
static void SequenceFunc(GameObject* this, void* data);
void ClearMonster();
extern Bool IsPlaying;