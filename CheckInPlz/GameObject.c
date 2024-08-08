#include "GameObject.h"

Bool AABB_to_AABB(rect2D a, rect2D b)
{
	if (a.max.x < b.min.x || a.min.x > b.max.x) return false;
	if (a.max.y < b.min.y || a.min.y > b.max.y) return false;
	return true;
}
Bool CompareTag(char*a, char*b)
{
	return strcmp(a, b)==0?true:false;
}

CollisionResponse CheckAABB(GameObject* t, GameObject*  other, Bool collided)
{
	CollisionResponse result;
	result.state = Not;
	rect2D A,B;
	A.min.x = t->rect.min.x * t->transform.scale.x + t->transform.position.x;
	A.min.y = t->rect.min.y * t->transform.scale.y + t->transform.position.y;
	A.max.x = t->rect.max.x * t->transform.scale.x + t->transform.position.x;
	A.max.y = t->rect.max.y * t->transform.scale.y + t->transform.position.y;

	B.min.x = other->rect.min.x * other->transform.scale.x + other->transform.position.x;
	B.min.y = other->rect.min.y * other->transform.scale.y + other->transform.position.y;
	B.max.x = other->rect.max.x * other->transform.scale.x + other->transform.position.x;
	B.max.y = other->rect.max.y * other->transform.scale.y + other->transform.position.y;

	Bool check = AABB_to_AABB(A,B);
	//AABB_to_AABB(shape + transform->position, other->shape + other->transform->position);
	result.other = other;


	if (!collided && check)
	{
		result.state = Enter;
	}
	else if (collided && check)
	{
		result.state = Stay;
	}
	else if (!collided && !check)
	{
		result.state = Not;
	}
	else if (collided && !check)
	{
		result.state = Exit;
	}

	return result;
}
void Enable(GameObject* t)
{
	if (!t->isEnabled)
	{
		t->isEnabled = true;
		t->OnEnable(t);
	}
}

void Disable(GameObject* t)
{
	if (t->isEnabled)
	{
		t->isEnabled = false;
		t->OnDisable(t);
	}
}

GameObject* CreateGameObject()
{
	GameObject* obj = (GameObject*)malloc(sizeof(GameObject));
	if (obj == NULL)
	{
		return NULL;
	}
	rect2D rect = { {0,0}, {0,0} };
	Transform transform = { {0,0},0,{0,0} };
	obj->t=obj;
	obj->SetRect= GameObjectSetRect;
	obj->SetTag = SetTag;
	obj->Start= DefaultGameObjectFunction;
	obj->Update = DefaultUpdate;
	obj->Draw = DefaultDrawFunction;
	obj->OnDestroy = DefaultGameObjectFunction;
	obj->OnEnable = DefaultGameObjectFunction;
	obj->OnDisable = DefaultGameObjectFunction;
	obj->OnCollisionEnter = DefaultCollisionFunction;
	obj->OnCollisionExit = DefaultCollisionFunction;
	obj->OnCollisionStay = DefaultCollisionFunction;
	obj->Collide = GameObjectCollide;
	obj->collider = false;
	obj->enter = false;
	obj->rect = rect;
	obj->started = false;
	obj->isEnabled = true;
	obj->transform = transform;//주의!!!! 내부 구조체 복사안됨
	obj->property = NULL;
	obj->renderOrder = 0;
	obj->rigidbody = false;
	return obj;
}

void GameObjectSetRect(GameObject* t, int size_x, int size_y)
{
	rect2D rect = { { (float)(- size_x / 2), (float)( - size_y / 2)},{(float)(size_x / 2),(float)(size_y / 2)}};
	t->rect = rect;
}

DWORD WINAPI DefaultDrawFunction(GameObject* t)
{
	return 0;
}
void DefaultUpdate(GameObject* t, double dt)
{

}

void DefaultGameObjectFunction(GameObject* t)
{

}

void DefaultCollisionFunction(GameObject* t, CollisionResponse response)
{

}

void SetTag(GameObject* t, char* tag)
{
	strcpy_s(t->tag, 30, tag);
}

Bool GameObjectCollide(GameObject* t, GameObject* other,Bool collided)
{
	CollisionResponse result = CheckAABB(t, other, collided);
	if (result.state == Enter)
	{
		t->OnCollisionEnter(t, result);
		return true;
	}
	else if (result.state == Exit)
	{
		t->OnCollisionExit(t, result);
		return false;
	}
	else if (result.state == Stay)
	{
		t->OnCollisionStay(t, result);
		return true;
	}
	else if (result.state == Not)
	{
		return false;
	}
	else
	{
		return false;
	}
}