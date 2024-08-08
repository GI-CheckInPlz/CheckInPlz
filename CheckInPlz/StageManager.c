#include "StageManager.h"



Constructor MonsterConstructor[KIND_OF_MONSTER] = {
	CreateBasicMonster,
	CreateMonster2,
	CreateMonster3,
	CreateMonster4,
	CreateMonster5
};

StageData stageData[NUMBER_OF_STAGE]= {
	{"Resources\\Stage1M.CSV", "Resources\\Stage1S.CSV",350 },
	{"Resources\\Stage2M.CSV", "Resources\\Stage2S.CSV",600 },
	{"Resources\\Stage3M.CSV", "Resources\\Stage3S.CSV",1150 },
	{"Resources\\Stage4M.CSV", "Resources\\Stage4S.CSV",2000 }
};



void InitializeStageManager(GameObject* this,char *monsterfilename, char *solutionfilename)
{
	for (int i = 0; i < 5; i++)
	{
		DeleteObject(MonsterBitmap[i]);
	}
	if (MonsterList)
	{
		free(MonsterList);
	}
	if (sequenceList)
	{
		for (int i = 0; i < sequenceList->count; i++)
		{
			free(sequenceList->Content[i]);
		}
		free(sequenceList);
	}
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 2; k++)
		{
	
			StageSolution[i][k].type = -1;
			StageSolution[i][k].sprite = NULL;
			PlayerSolution[i][k] = false;
		}
	}

	MonsterBitmap[0] = render.LoadBitmapImage(L"Resources\\m1\\idle1.bmp");
	MonsterBitmap[1] = render.LoadBitmapImage(L"Resources\\m2\\idle1.bmp");
	MonsterBitmap[2] = render.LoadBitmapImage(L"Resources\\m3\\idle1.bmp");
	MonsterBitmap[3] = render.LoadBitmapImage(L"Resources\\m4\\idle1.bmp");
	MonsterBitmap[4] = render.LoadBitmapImage(L"Resources\\m5\\idle1.bmp");
	MonsterList = CreateGameObjectList();
	sequenceList = CreateSequenceList();
	GenerateSquence(this, monsterfilename);
	GenerateSolution(this, solutionfilename);
}

void GenerateSolution(GameObject* this,char * filename)
{
	FILE* file = NULL;
	char* content[2];

	char line[1024];
	fopen_s(&file, filename, "r");
	if (file)
	{
		fgets(line, 1024, file);//√π∂Û¿Œ Ω∫≈µ
		
		for (int i = 0; i < 4; i++)
		{
			char* remain = NULL;
			fgets(line, 1024, file);
			content[0] = strtok_s(line, ",", &remain);
			content[1] = strtok_s(NULL, ",", &remain);

			for (int k = 0; k <= 1; k++)
			{
				StageSolution[i][k].type = atoi(content[k])-1;
				StageSolutionType[i][k] = atoi(content[k]) - 1;
				if (StageSolution[i][k].type >= 0)
				{
					StageSolution[i][k].sprite = MonsterBitmap[StageSolution[i][k].type];
				}
				else
				{
					StageSolution[i][k].sprite = NULL;
					PlayerSolution[i][k] = true;
				}
			}
		} 
	}
	fclose(file);
}



void GenerateMonster(GameObject* this)
{
	for (int i = 0; i < sequenceList->count; i++)
	{
		timer.Delay(this, sequenceList->Content[i]->delay,false,SequenceFunc, sequenceList->Content[i]);
	}
}

void SequenceFunc(GameObject* this, void* data)
{
	Sequence* sqData = data;
	GameObject* newMonster = MonsterConstructor[sqData->type]();
	newMonster->transform.position = floorPosition[sqData->floor];
	MonsterList->Add(MonsterList, newMonster);
	Instantiate(newMonster);
}

void ClearMonster()
{

	for (int i = 0; i < MonsterList->count; i++)
	{
		Destroy(MonsterList->Content[i]);
	}
	MonsterList->Clear(MonsterList);
}


void GenerateSquence(GameObject* this, char* filename)
{
	FILE* file=NULL;
	char* content[3];

	char line[1024];
	fopen_s(&file, filename, "r");
	if(file)
	{
		fgets(line, 1024, file);//√π∂Û¿Œ Ω∫≈µ
		while (!feof(file)) {
			char* remain = NULL;
			fgets(line, 1024, file);
			content[0] = strtok_s(line, ",", &remain);
			for (int i = 1; i < 3; i++)
			{
				content[i] = strtok_s(NULL, ",", &remain);
			}
			
			Sequence* data = (Sequence*)malloc(sizeof(Sequence));
			if (data == NULL)
			{
				return;
			}
			data->delay= (float)atoi(content[0]);
			data->type = atoi(content[1]) - 1;
			data->floor = atoi(content[2]) - 1;
			sequenceList->Add(sequenceList,data);
		}
	}
	fclose(file);
}
