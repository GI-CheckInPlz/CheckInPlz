#include "Scene.h"

void RenderSort(GameObjectList* list)
{
	int i,j;
	if (list->count >= 1)
	{
		for (i = 1; i < list->count; i++)
		{
			GameObject* key = list->Content[i];
			for (j = i - 1; j >= 0 && list->Content[j]->renderOrder > key->renderOrder; j--)
			{
				list->Content[j + 1] = list->Content[j];
			}
			list->Content[j + 1] = key;
		}
	}
}

Scene* CreateScene()
{
	Scene* scene = (Scene*)malloc(sizeof(Scene));
	scene->t = scene;
	scene->Start = StartScene;
	scene->Update = UpdateScene;
	scene->Draw = DrawScene;
	scene->Push = Push;
	scene->Hold = Hold;
	scene->Pop = Pop;
	scene->Collide = CollideScene;
	scene->OnEnable = OnEnableScene;
	scene->OnDisable = OnDisableScene;
	scene->gameObjectList=CreateGameObjectList();
	scene->constructorList = CreateConstructorList();
	return scene;
}

void StartScene(Scene* this)
{
	for (int i = 0; i < this->gameObjectList->count; i++)
	{
		if (this->gameObjectList->Content[i]->isEnabled && !this->gameObjectList->Content[i]->started)
		{
			this->gameObjectList->Content[i]->Start(this->gameObjectList->Content[i]);
			this->gameObjectList->Content[i]->started = true;
		}
		
	}
}


void DrawScene(Scene* this,Bool *Drawing)
{
	*Drawing = true;
	this->drawList = this->gameObjectList;
	this->drawList->Content = this->gameObjectList->Content;
	RenderSort(this->drawList);
	for (int i = 0; i < this->drawList->count; i++)
	{
		if (this->drawList->Content[i]->isEnabled)
		{
			//DrawThread[i]=CreateThread(NULL, 0, tmpList->Content[i]->Draw, tmpList->Content[i],0,NULL);
			//Sleep(1L);
			this->drawList->Content[i]->Draw(this->drawList->Content[i]);
		}
	}
	*Drawing = false;
	//WaitForMultipleObjects(this->gameObjectList->count, DrawThread, TRUE, INFINITE);
}

void UpdateScene(Scene* this,double dt)
{
	for (int i = 0; i < this->gameObjectList->count; i++)
	{
		if (this->gameObjectList->Content[i]->isEnabled)
			this->gameObjectList->Content[i]->Update(this->gameObjectList->Content[i],dt);
	}
}

void CollideScene(Scene* this)
{
	static Bool Collided[MAX_GAMEOBJECT][MAX_GAMEOBJECT]={ {false,}, };
	static int count = 0;
	for (int i = 0; i < this->gameObjectList->count; i++)
	{
		if (this->gameObjectList->Content[i]->isEnabled && this->gameObjectList->Content[i]->collider && this->gameObjectList->Content[i]->rigidbody)
		{
			for (int j = 0; j < this->gameObjectList->count; j++)
			{
				if (this->gameObjectList->Content[j]->isEnabled && this->gameObjectList->Content[j]->collider && i != j)
				{
					Bool result = this->gameObjectList->Content[i]->Collide(this->gameObjectList->Content[i], this->gameObjectList->Content[j], Collided[i][j]);
					if(result)
						Collided[i][j] = true;
					else
						Collided[i][j] = false;
				}
				else
				{
					Collided[i][j] = false;

				}
			}
		}
	}
}

void Hold(Scene* this, Constructor constructor)
{
	this->constructorList->Add(this->constructorList, constructor);
}

void Push(Scene* this, GameObject* newObject)
{
	this->gameObjectList->Add(this->gameObjectList, newObject);
}

void Pop(Scene* this, GameObject* newObject)
{
	this->gameObjectList->Remove(this->gameObjectList, newObject);
	newObject->OnDestroy(newObject);
	free(newObject);
}

void OnEnableScene(Scene* this)
{
	for (int i = 0; i < this->constructorList->count; i++)
	{
		Push(this, this->constructorList->Content[i]());
	}
	for (int i = 0; i < this->gameObjectList->count; i++)
	{
		if(this->gameObjectList->Content[i]->isEnabled)
			this->gameObjectList->Content[i]->OnEnable(this->gameObjectList->Content[i]);
	}
}

void OnDisableScene(Scene* this)
{
	
	for (int i = 0; i < this->gameObjectList->count; i++)
	{
		if (this->gameObjectList->Content[i]->isEnabled)
			this->gameObjectList->Content[i]->OnDisable(this->gameObjectList->Content[i]);
	}
	for (int i = 0; i < this->gameObjectList->count; i++)
	{
		this->gameObjectList->Content[i]->OnDestroy(this->gameObjectList->Content[i]);
		free(this->gameObjectList->Content[i]);
	}
	this->gameObjectList->Clear(this->gameObjectList);
}