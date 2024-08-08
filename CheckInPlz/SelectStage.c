#include "SelectStage.h"

extern Bool _isStageSelectOn;
Bool _isBGMSelectOn;


typedef struct SelectStageProp
{
	HBITMAP selectStageUI;
	HBITMAP stageOneBtn;
	HBITMAP stageOneBtnPressed;
	HBITMAP stageTwoBtn;
	HBITMAP stageTwoBtnPressed;
	HBITMAP stageThreeBtn;
	HBITMAP stageThreeBtnPressed;
	HBITMAP stageFourBtn;
	HBITMAP stageFourBtnPressed;

	HBITMAP currentStageOne;
	HBITMAP currentStageTwo;
	HBITMAP currentStageThree;
	HBITMAP currentStageFour;

	rect2D stageOneArea;
	rect2D stageTwoArea;
	rect2D stageThreeArea;
	rect2D stageFourArea;


}SelectStageProp;

GameObject* CreateSelectStage()
{
	SelectStageProp* property = (SelectStageProp*)malloc(sizeof(SelectStageProp));
	if (property == NULL)
	{
		return NULL;
	}

	Transform transform = { {960,540},0,{1,1} };
	GameObject* obj = CreateGameObject();

	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Start = SelectStageStart;
	obj->Draw = SelectStageDraw;
	obj->Update = SelectStageUpdate;
	obj->OnDestroy = SelectStageOnDestroy;

	obj->property = property;
	property->selectStageUI = LoadBitmapImage(L"Resources\\TitleUI\\SelectStage\\StageSelectUI.bmp");
	property->stageOneBtn = LoadBitmapImage(L"Resources\\TitleUI\\SelectStage\\StageOneBtn.bmp");
	property->stageOneBtnPressed = LoadBitmapImage(L"Resources\\TitleUI\\SelectStage\\StageOneBtnPressed.bmp");
	property->stageTwoBtn = LoadBitmapImage(L"Resources\\TitleUI\\SelectStage\\StageTwoBtn.bmp");
	property->stageTwoBtnPressed = LoadBitmapImage(L"Resources\\TitleUI\\SelectStage\\StageTwoBtnPressed.bmp");
	property->stageThreeBtn = LoadBitmapImage(L"Resources\\TitleUI\\SelectStage\\StageThreeBtn.bmp");
	property->stageThreeBtnPressed = LoadBitmapImage(L"Resources\\TitleUI\\SelectStage\\StageThreeBtnPressed.bmp");
	property->stageFourBtn = LoadBitmapImage(L"Resources\\TitleUI\\SelectStage\\StageFourBtn.bmp");
	property->stageFourBtnPressed = LoadBitmapImage(L"Resources\\TitleUI\\SelectStage\\StageFourBtnPressed.bmp");

	property->stageOneArea.min.x = 809;
	property->stageOneArea.max.x = 1111;
	property->stageOneArea.min.y = 512;
	property->stageOneArea.max.y = 568;

	property->stageTwoArea.min.x = 809;
	property->stageTwoArea.max.x = 1111;
	property->stageTwoArea.min.y = 612;
	property->stageTwoArea.max.y = 668;

	property->stageThreeArea.min.x = 809;
	property->stageThreeArea.max.x = 1111;
	property->stageThreeArea.min.y = 712;
	property->stageThreeArea.max.y = 768;

	property->stageFourArea.min.x = 809;
	property->stageFourArea.max.x = 1111;
	property->stageFourArea.min.y = 812;
	property->stageFourArea.max.y = 868;
	obj->SetRect(obj, 950, 800);
	obj->SetTag(obj, "SelectStage");
	obj->renderOrder = UI_ORDER;
	obj->collider = false;
	
	return obj;
}

void SelectStageStart(GameObject* this)
{

}

void SelectStageUpdate(GameObject* this, double dt)
{
	SelectStageProp* prop = this->property;
	vector2 pos = GetMousePosition();
	
	//스타트 버튼 등 조정할 필요 있음. (다른 레이어 열려 있음에도 문제 발생)
	if (!(physics.InBound(this, pos)) && input.GetMouseButton(0))
	{
		_isStageSelectOn = false;
	}

	if (_isStageSelectOn == true)
	{

		if (physics.InBoundRect(prop->stageOneArea, pos) && input.GetMouseButton(0))
		{
			prop->currentStageOne = prop->stageOneBtnPressed;
		}
		else
		{
			prop->currentStageOne = prop->stageOneBtn;
		}

		if (physics.InBoundRect(prop->stageTwoArea, pos) && input.GetMouseButton(0))
		{
			prop->currentStageTwo = prop->stageTwoBtnPressed;
		}
		else
		{
			prop->currentStageTwo = prop->stageTwoBtn;
		}

		if (physics.InBoundRect(prop->stageThreeArea, pos) && input.GetMouseButton(0))
		{
			prop->currentStageThree = prop->stageThreeBtnPressed;
		}
		else
		{
			prop->currentStageThree = prop->stageThreeBtn;
		}

		if (physics.InBoundRect(prop->stageFourArea, pos) && input.GetMouseButton(0))
		{
			prop->currentStageFour = prop->stageFourBtnPressed;
		}
		else
		{
			prop->currentStageFour = prop->stageFourBtn;
		}

		if (physics.InBoundRect(prop->stageOneArea, pos) && input.GetMouseButtonUp(0))
		{
			currentStage = 0;
			ChangeScene(GameScene[2]);
		}
		if (physics.InBoundRect(prop->stageTwoArea, pos) && input.GetMouseButtonUp(0))
		{
			currentStage = 1;
			ChangeScene(GameScene[2]);
		}

		if (physics.InBoundRect(prop->stageThreeArea, pos) && input.GetMouseButtonUp(0))
		{
			currentStage = 2;
			ChangeScene(GameScene[2]);
		}

		if (physics.InBoundRect(prop->stageFourArea, pos) && input.GetMouseButtonUp(0))
		{
			currentStage = 3;
			ChangeScene(GameScene[2]);
		}

		//
		if (_isBGMSelectOn == false)
		{
			if (physics.InBoundRect(prop->stageOneArea, pos) && input.GetMouseButtonDown(0))
			{
				AUDIO_PlayAudio("Resources\\Sound\\ButtonClick.wav", 1);
			}


			if (physics.InBoundRect(prop->stageTwoArea, pos) && input.GetMouseButtonDown(0))
			{
				AUDIO_PlayAudio("Resources\\Sound\\ButtonClick.wav", 1);
			}


			if (physics.InBoundRect(prop->stageThreeArea, pos) && input.GetMouseButtonDown(0))
			{
				AUDIO_PlayAudio("Resources\\Sound\\ButtonClick.wav", 1);
			}

			if (physics.InBoundRect(prop->stageFourArea, pos) && input.GetMouseButtonDown(0))
			{
				AUDIO_PlayAudio("Resources\\Sound\\ButtonClick.wav", 1);
			}
		}
		
	}
}

DWORD WINAPI SelectStageDraw(GameObject* this)
{
	SelectStageProp* prop = this->property;
	if (_isStageSelectOn == true)
	{
		//이제부터 창을 키는 형식.
		render.DrawBitmapPreSize(this, prop->selectStageUI, 1, 950, 800);
		render.DrawBitmapWithCustom(this, prop->currentStageOne, 1, 302, 57, 0, 0); //960,540
		render.DrawBitmapWithCustom(this, prop->currentStageTwo, 1, 302, 57, 0, 100);
		render.DrawBitmapWithCustom(this, prop->currentStageThree, 1, 302, 57, 0, 200);
		render.DrawBitmapWithCustom(this, prop->currentStageFour, 1, 302, 57, 0, 300);
	}
	return 0;
}

void SelectStageOnDestroy(GameObject* this)
{
	SelectStageProp* prop = this->property;
	free(prop);
}

