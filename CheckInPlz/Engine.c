#include "Engine.h"
#include "Render.h"


Screen screen = { {1920,1080} };
static Bool rendering;
void RunEngine(Scene* scene)
{
	input.Init();
	objectBuffer = CreateGameObjectList();
	removeObjectBuffer = CreateGameObjectList();
	currentScene = scene;
	currentScene->gameObjectList = scene->gameObjectList;
	currentScene->gameObjectList->Content = scene->gameObjectList->Content;
	currentScene->drawList = currentScene->gameObjectList;
	currentScene->drawList->Content = currentScene->gameObjectList->Content;
	double dt = 0;
	__int64  s = 0, e = 0, periodFrequency;
	QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency);
	double timeScale = 1.0 / (double)periodFrequency;
	state = Run;
	MSG msg;


	timer.Init();
	currentScene->OnEnable(currentScene);
	Bool Drawing = false;
	HANDLE renderThread = CreateThread(NULL, 0, EngineRender, &Drawing, 0, NULL);
	CloseHandle(renderThread);
	while (state == Run)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&s);
		state = UpdateMsg(&msg);
		
		if (!objectBuffer->isEmpty(objectBuffer))
		{
			while (Drawing)
			{
			}
			for (int i = 0; i < objectBuffer->count; i++)
			{
				currentScene->Push(currentScene,objectBuffer->Content[i]);
			}
			objectBuffer->Clear(objectBuffer);
		}
		if (!removeObjectBuffer->isEmpty(removeObjectBuffer))
		{
			while (Drawing)
			{
			}
			for (int i = 0; i < removeObjectBuffer->count; i++)
			{
				currentScene->Pop(currentScene, removeObjectBuffer->Content[i]);
			}
			removeObjectBuffer->Clear(removeObjectBuffer);
		}
		if (nextScene)
		{
			//timerHandlerList->Clear(timerHandlerList);
			// timerHandlerList->clear�� �ϸ� count�� 0���� ����µ� ���� OnDestroy�� timerCancelAllInObject����
			// ����Ʈ�� �������� Ÿ�̸Ӱ� �������� count�� 0�̶� �׳� �Ѿ�� ��찡 debug ������Ʈ���� �߻���
			// debug ������Ʈ�� Ÿ�̸� ������ true�� ��Ȯ�ϰ� �����ؾ���
			currentScene->OnDisable(currentScene);
			currentScene = nextScene;
			currentScene->gameObjectList = nextScene->gameObjectList;
			currentScene->gameObjectList->Content = nextScene->gameObjectList->Content;
			currentScene->OnEnable(currentScene);
			nextScene = NULL;
		}

		currentScene->Start(currentScene);
		currentScene->Update(currentScene,dt);
		input.Update();
		timer.Update(dt);
		currentScene->Collide(currentScene);
	
		QueryPerformanceCounter((LARGE_INTEGER*)&e);
		dt = (double)(e - s) * timeScale;
		//Sleep(dt * 1000 > 25 ? dt * 1000 - 25 : 0);
	}
	release();
}

DWORD WINAPI EngineRender(LPVOID data)
{
	render.Init();
	while(1)
	{
		render.Update(data);
	}

}

EngineState EngineDraw(Bool* cancel)
{
	currentScene->Draw(currentScene,cancel);
	return Run;
}

GameObject* Instantiate(GameObject* newObject)
{
	objectBuffer->Add(objectBuffer,newObject);
	return newObject;
}


void Destroy(GameObject* obj)
{
	if(!removeObjectBuffer->Exist(removeObjectBuffer,obj))
		removeObjectBuffer->Add(removeObjectBuffer,obj);
}

void ChangeScene(Scene* scene)
{
	AUDIO_StopAllAudio();
	nextScene = scene;
}

void SetRenderOrder(GameObject* t, int order)
{
	t->renderOrder = order;
	RenderSort(currentScene->gameObjectList);
}