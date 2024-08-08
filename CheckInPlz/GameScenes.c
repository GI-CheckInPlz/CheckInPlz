#include "GameScenes.h"

Scene* GameScene[SCENE_NUMBER];

void InitScenes()
{
	//Scene �ʱ�ȭ
	for (int i = 0; i < SCENE_NUMBER; i++)
	{
		GameScene[i] = CreateScene();
	}
	//Object �ʱ�ȭ


	//Object Hold (Scene0) (Ÿ��Ʋ ȭ��)
	GameScene[0]->Hold(GameScene[0], CreateTitleBackground);
	GameScene[0]->Hold(GameScene[0], CreateStartBtn);
	GameScene[0]->Hold(GameScene[0], CreateSelectStageBtn);
	GameScene[0]->Hold(GameScene[0], CreateExitBtn);
	GameScene[0]->Hold(GameScene[0], CreateGearIcon);
	GameScene[0]->Hold(GameScene[0], CreateChandLeftLight);
	GameScene[0]->Hold(GameScene[0], CreateChandRightLight);
	//Object Hold (Scene0) (����Ʈ ���� ȭ��)
	GameScene[0]->Hold(GameScene[0], CreateSelectStage);
	//Object Hold (Scene0) (BGM Select ȭ��)
	GameScene[0]->Hold(GameScene[0], CreateBGMSelect);

	GameScene[1]->Hold(GameScene[1], CreateCutSceneManager);


	//Object Hold (Scene2) (���� ���� ��, Stage1)
	GameScene[2]->Hold(GameScene[2], CreateInGame);//stage ���� ������� �ʱ�ȭ �Ǿ����

	//Stage Credits
	GameScene[3]->Hold(GameScene[3], CreateCredits);
	GameScene[3]->Hold(GameScene[3], CreateCreditsText);

#if DEBUG 
	GameScene[0]->Hold(GameScene[0], CreateDebug);
	GameScene[1]->Hold(GameScene[1], CreateDebug);
	GameScene[2]->Hold(GameScene[2], CreateDebug);
	GameScene[3]->Hold(GameScene[3], CreateDebug);
#endif

}