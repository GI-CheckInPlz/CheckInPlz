#include "CharacterState.h"
void TakeARest(GameObject* this, void* etc)
{
	MonsterProp* prop = this->property;
	prop->characterState = Rest;
}

void EnterAnimation(GameObject* this, void* etc)
{
	this->renderOrder = 2;
}