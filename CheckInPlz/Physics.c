#include "Physics.h"

Scene* currentScene;
Bool CompareAllTags(char *tags[], int size, char* tag)
{
	for (int i = 0; i < size; i++)
	{
		if (CompareTag(tags[i], tag))
			return true;
	}
	return false;
}

Bool InBound(GameObject* obj, vector2 v)
{
	rect2D  rect = obj->rect;
	vector2 pos = obj->transform.position;
	vector2 scale = obj->transform.scale;
	return rect.min.x * scale.x+ pos.x < v.x&& rect.max.x * scale.x + pos.x > v.x && rect.min.y * scale.y + pos.y < v.y && rect.max.y * scale.y + pos.y > v.y;
}

//임의로 rect2D값을 대입해, 해당 공간 안에 vector2가 있는지 체크해주는 함수
Bool InBoundRect(rect2D _rect, vector2 v)
{
	//rect2D  rect = _rect;
	return (_rect.min.x <= v.x && _rect.min.y <= v.y && _rect.max.x >= v.x && _rect.max.y >= v.y);
}

RaycastResponse CheckAllDot(RaycastData* data)
{
	int count = data->count;
	vector2 from = data->from;
	vector2 d = data->d;
	data->result.hit = false;
	
}

RaycastResponse Raycast(vector2 from, vector2 to, char* tags[],int size)
{
	RaycastResponse result;
	result.hit = false;
	result.hit = false;
	vector2 v = { to.x - from.x,to.y - from.y };
	int count = abs(v.x) > abs(v.y) ? abs(v.x) : abs(v.y);
	int checkCount=0;
	from.x = (float)round(from.x);
	from.y = (float)round(from.y);
	vector2 d = { v.x/ count,v.y/ count };
	for (int i = 0; i < currentScene->gameObjectList->count; i++)
	{
		GameObject* obj = currentScene->gameObjectList->Content[i];
		vector2 objectV = { obj->transform.position.x - from.x,obj->transform.position.y - from.y};
		float objectRange = vmath.Distance(obj->rect.min, obj->rect.max);
		if (obj->isEnabled && obj->collider && CompareAllTags(tags, size, obj->tag) && vmath.Dot(v,objectV)>=0 && vmath.Length(v) >= vmath.Length(objectV)-objectRange)
		{
			for (int k = 0; k < count; k++)
			{
				vector2 check = { from.x + d.x * k, from.y + d.y * k };
				if (InBound(obj, check))
				{
					strcpy_s(result.tag, 30, obj->tag);
					result.position = check;
					result.hit = true;
					return result;
				}
			}
		}
	}
	return result;
}

Physics physics = {
	InBound,
	InBoundRect,
	Raycast
};