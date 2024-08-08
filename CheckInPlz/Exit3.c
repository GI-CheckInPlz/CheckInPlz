#include "Exit3.h"
Bool toggleDebug;
GameObject* CreateExit3()
{
	Transform transform = { {1660, 460}, 0, {1,1} };
	vector2 s1 = { transform.position.x,transform.position.y + 70 };
	vector2 s2 = { transform.position.x + 100,transform.position.y + 70 };
	PropExit3* property = (PropExit3*)malloc(sizeof(PropExit3));
	if (property == NULL)
	{
		return NULL;
	}
	property->sprite = render.LoadBitmapImage(L"Resources\\Map\\Room.bmp");
	property->solutionPos[0] = s1;
	property->solutionPos[1] = s2;
	GameObject* obj = CreateGameObject();
	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Draw = DrawExit3;
	obj->Start = StartExit3;
	obj->Update = UpdateExit3;
	obj->OnCollisionEnter = EnterExit3;
	obj->OnCollisionExit = ExitExit3;
	obj->OnCollisionStay = StayExit3;
	obj->SetRect(obj, 250, 170);
	obj->SetTag(obj, "exit");
	obj->property = property;
	obj->renderOrder = 3;
	obj->collider = true;
	obj->rigidbody = true;
	obj->OnDestroy = Exit3OnDestroy;

	return obj;
}

void Exit3OnDestroy(GameObject* this)
{
	free(this->property);
}

DWORD WINAPI DrawExit3(GameObject* this)
{
	PropExit3* prop = this->property;
	render.DrawBitmapPreSize(this, prop->sprite, 1, 520, 200);
	if (StageSolution[2][0].type != -1)
	{
		BITMAP btSize;
		GetObject(StageSolution[2][0].sprite, sizeof(BITMAP), &(btSize));
		render.DrawBitmapPre(this, StageSolution[2][0].sprite, 0.5, (int)prop->solutionPos[0].x, (int)prop->solutionPos[0].y, (int)(btSize.bmWidth * 0.4), (int)(btSize.bmHeight * 0.4));
	}
	if (StageSolution[2][1].type != -1)
	{
		BITMAP btSize;
		GetObject(StageSolution[2][1].sprite, sizeof(BITMAP), &(btSize));
		render.DrawBitmapPre(this, StageSolution[2][1].sprite, 0.5, (int)prop->solutionPos[1].x, (int)prop->solutionPos[1].y, (int)(btSize.bmWidth * 0.4), (int)(btSize.bmHeight * 0.4));
	}

#if DEBUG
	if (toggleDebug)
	{
		DrawDebugRectangle(this);
	}
#endif
	return 0;
}

void UpdateExit3(GameObject* this, double dt)
{

}

void EnterExit3(GameObject* this, CollisionResponse res)
{
	PropExit3* prop = this->property;
	if (CompareTag(res.other->tag, "Monster"))
	{
		MonsterProp* otherProp = res.other->property;
		for (int i = 0; i < 2; i++)
		{
			if (otherProp->type == StageSolution[2][i].type && otherProp->characterState != Rest && otherProp->characterState != Arrive)
			{
				otherProp->characterState = Arrive;
				timer.Delay(res.other, 0.1, false, EnterAnimation, NULL);
				StageSolution[2][i].type = -1;
				PlayerSolution[2][i] = true;
				float duration = (prop->solutionPos[i].x - res.other->transform.position.x) / otherProp->speed;
				AUDIO_PlayAudio("Resources\\Sound\\CharacterEnter.wav", 6);
				Animate(res.other, &res.other->transform.position.x, PLAYBACK_ONCE_FORWARD, prop->solutionPos[i].x, EASING_LINEAR, duration, otherProp->TakeARest);
				if (CheckClear())
				{
					GameClear(ingame);
				}
				break;
			}
		}
		if (!(otherProp->characterState == Rest || otherProp->characterState == Arrive) )
		{
			GameOver(ingame);
			MonsterOut(res.other);
		}

	}
}

void ExitExit3(GameObject* this, CollisionResponse res)
{

}

void StayExit3(GameObject* this, CollisionResponse res)
{

}

void StartExit3(GameObject* this)
{

}
