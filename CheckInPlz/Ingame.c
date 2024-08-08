#include "Ingame.h"

GameObject* CreateInGame()
{
	Transform transform = { {960, 900}, 0, {1,1} };
	PropIngame* property = (PropIngame*)malloc(sizeof(PropIngame));
	if (property == NULL)
	{
		return NULL;
	}
	property->BlockManager = CreateBlockManager();
	property->BottomUI = CreateBlockBook();
	property->MonsterBook = CreateMonsterBook();
	property->Overlay = CreateOverlay();
	GameObject* obj = CreateGameObject();
	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->SetRect(obj, 1920, 10);
	obj->SetTag(obj, "block");
	obj->Start = IngameStart;
	obj->OnDestroy = IngameOnDestroy;
	obj->property = property;

	Instantiate(property->BlockManager);
	Instantiate(property->BottomUI);
	Instantiate(property->Overlay);
	Instantiate(property->MonsterBook);
	Instantiate(CreateFloor1());
	Instantiate(CreateFloor2());
	Instantiate(CreateFloor3());
	Instantiate(CreateFloor4());
	Instantiate(CreateFloor5());
	Instantiate(CreateFloor6());
	Instantiate(CreateBackground());
	

	Instantiate(CreatePlayBtnInGame());
	Instantiate(CreateResetBtnInGame());
	Instantiate(CreateReturnToHomeBtn());
	Instantiate(CreateCoinInGame());
	Instantiate(CreateExit());
	Instantiate(CreateExit2());
	Instantiate(CreateExit3());
	Instantiate(CreateExit4());
	InitializeStageManager(obj, stageData[currentStage].MonsterFileName, stageData[currentStage].SolutionFileName);
	CurrentCoin = stageData[currentStage].coin;
	IsPlaying = true;
	ingame=obj;
	return obj;
}



Bool CheckClear()
{
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			if(!PlayerSolution[i][k])
			{
				return false;
			}
		}
	}
	return true;
}


void PlayFalse(GameObject* this)
{
	IsPlaying = false;
}

void MonsterOut(GameObject* this)
{
	MonsterProp* p = this->property;
	p->characterState = Collision;
	this->collider = false;
	//this->rigidbody = false;
	Animate(this, &this->transform.position.x, PLAYBACK_ONCE_FORWARD, this->transform.position.x -80, EASING_INOUTBOUNCE, 0.3f, NULL);
	Animate(this, &this->transform.position.y, PLAYBACK_ONCE_PINGPONG, this->transform.position.y - 80, EASING_INOUTBOUNCE, 0.3f, NULL);
	Animate(this, &p->alpha, PLAYBACK_ONCE_FORWARD, p->alpha - 0.5f, EASING_OUTCUBIC, 0.3f, NULL);

	// �ʹ� ���� destroy�ϰ� �Ǹ� fall-jump �浹���� ���α׷� �ٿ�
	// ����: destroy�� ���ӿ�����Ʈ�� ���Ŀ� jump���� fall�� ��ȯ�ϴ� Ÿ�̸ӿ��� �̹� ������ ������Ʈ�� property�� �����ϱ� ����
	// destroy�� ���� �� õõ�� �ϵ��� ����
	timer.Delay(this, 0.5, false, Destroy, this);
}


void PauseMonster(GameObject* this)
{
	MonsterProp* prop = this->property;
	if(prop->characterState !=Collision)
		prop->characterState = Pause;
}

void LoadNextStage(GameObject* this, void* etc)
{
	if (currentStage < NUMBER_OF_STAGE)
	{
		PropIngame* prop = this->property;
		OverlayProp* overlayProp = prop->Overlay->property;
		currentStage++;
		ClearMonster();
		InitializeStageManager(this, stageData[currentStage].MonsterFileName, stageData[currentStage].SolutionFileName);
		Animate(prop->Overlay, &overlayProp->fadeFilter, PLAYBACK_ONCE_FORWARD, 0, EASING_OUTCIRC, 4, NULL);
		Animate(prop->Overlay, &overlayProp->fadeStage[currentStage], PLAYBACK_ONCE_PINGPONG, 1, EASING_OUTCIRC, 3, PlayFalse);
		CurrentCoin = stageData[currentStage].coin;
		Animate(prop->BottomUI, &prop->BottomUI->transform.position.y, PLAYBACK_ONCE_FORWARD, prop->BottomUI->transform.position.y - 800, EASING_INOUTBOUNCE, 1, NULL);
		Animate(prop->MonsterBook, &prop->MonsterBook->transform.position.x, PLAYBACK_ONCE_FORWARD, -170, EASING_INOUTBOUNCE, 1, NULL);
		ClearBoard(prop->BlockManager);
	}
	else
	{
		ClearMonster();
		ChangeScene(GameScene[3]);
	}
	
	
	
	
}

void GameClear(GameObject* this)
{
	PropIngame* prop = this->property;
	OverlayProp* overlayProp = prop->Overlay->property;
	timer.Delay(this, 3, false, LoadNextStage,NULL);
	AUDIO_PlayAudio("Resources\\Sound\\StageClear.wav", 6);
	Animate(prop->Overlay, &overlayProp->fadeFilter, PLAYBACK_ONCE_FORWARD, 0.5, EASING_OUTCIRC, 1, NULL);
	Animate(prop->Overlay, &overlayProp->fadeClear, PLAYBACK_ONCE_PINGPONG, 1, EASING_OUTSINE, 2, NULL);
}


void GameOver(GameObject* this)
{
	PropIngame* prop = this->property;
	OverlayProp* overlayProp = prop->Overlay->property;
	for (int i = 0; i < MonsterList->count; i++)
	{
		PauseMonster(MonsterList->Content[i]);
	}
	AUDIO_PlayAudio("Resources\\Sound\\Fail.wav", 6);
	Animate(prop->Overlay, &overlayProp->fadeFilter, PLAYBACK_ONCE_FORWARD, 0.5, EASING_OUTCIRC, 1, NULL);
	Animate(prop->Overlay, &overlayProp->fadeRetry, PLAYBACK_ONCE_FORWARD, 1, EASING_OUTSINE, 1, NULL);
}

void Play(GameObject* this)
{
	PropIngame* prop = this->property;
	IsPlaying = true;
	Animate(prop->BottomUI, &prop->BottomUI->transform.position.y, PLAYBACK_ONCE_FORWARD, prop->BottomUI->transform.position.y + 800, EASING_INOUTBOUNCE, 1, NULL);
	Animate(prop->MonsterBook, &prop->MonsterBook->transform.position.x, PLAYBACK_ONCE_FORWARD, prop->MonsterBook->transform.position.x - 1000, EASING_INOUTBOUNCE, 1, NULL);
	GenerateMonster(this);
}

void Reset(GameObject* this)
{
	PropIngame* prop = this->property;
	OverlayProp* overlayProp = prop->Overlay->property;
	if (IsPlaying)
	{
		IsPlaying = false;
		ClearMonster();
		Animate(prop->BottomUI, &prop->BottomUI->transform.position.y, PLAYBACK_ONCE_FORWARD, prop->BottomUI->transform.position.y - 800, EASING_INOUTBOUNCE, 1, NULL);
		Animate(prop->MonsterBook, &prop->MonsterBook->transform.position.x, PLAYBACK_ONCE_FORWARD,-170, EASING_INOUTBOUNCE, 1, NULL);
	}
	ClearBoard(prop->BlockManager);
	CurrentCoin = stageData[currentStage].coin;
	overlayProp->fadeFilter = 0;
	overlayProp->fadeRetry = 0;
	overlayProp->fadeClear = 0;

	// reset ������ �� �̹� ���� ĳ���� ���������� �ٽ� ���������
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			StageSolution[i][j].type = StageSolutionType[i][j];
		}
	}
}
void IngameStart(GameObject* this)
{
	PropIngame* prop = this->property;
	OverlayProp* overlayProp = prop->Overlay->property;
	//InitializeStageManager(this, stageData[currentStage].MonsterFileName, stageData[currentStage].SolutionFileName);
	Animate(prop->Overlay, &overlayProp->fadeFilter, PLAYBACK_ONCE_PINGPONG, 0.5, EASING_OUTCIRC, 4, NULL);
	Animate(prop->Overlay, &overlayProp->fadeStage[currentStage], PLAYBACK_ONCE_PINGPONG, 1, EASING_OUTCIRC, 3, PlayFalse);
}



void IngameOnDestroy(GameObject* this)
{
	ingame = NULL;
	free(this->property);
}