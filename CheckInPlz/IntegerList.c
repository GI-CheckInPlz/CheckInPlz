#include "IntegerList.h"


IntegerList* CreateIntegerList()
{
	IntegerList* list = (IntegerList*)malloc(sizeof(IntegerList));
	if (list == NULL)
	{
		return NULL;
	}
	list->Content = (int*)malloc(sizeof(int) * 100);
	list->count = 0;
	list->Add = AddInteger;
	list->Remove = RemoveInteger;
	list->Clear = ClearInteger;
	list->isEmpty = IntegerisEmpty;
	list->Exist = IntegerExist;
	return list;
}

Bool IntegerExist(IntegerList* list, int obj)
{
	for (int i = 0; i < list->count; i++)
	{
		if (list->Content[i] == obj)
		{
			return true;
		}
	}
	return false;
}

void AddInteger(IntegerList* list, int obj)
{
	list->Content[list->count] = obj;
	list->count++;
}

int RemoveInteger(IntegerList* list, int obj)
{
	int check = 0;
	for (int i = 0; i < list->count; i++)
	{
		if (check)
		{
			list->Content[i - 1] = list->Content[i];
		}
		if (list->Content[i] == obj)
		{
			check = list->Content[i];
		}
	}
	if (check)
	{
		list->count--;
	}
	return check;
}
Bool IntegerisEmpty(IntegerList* list)
{
	return list->count ? 0 : 1;
}
void ClearInteger(IntegerList* list)
{
	for (int i = 0; i < list->count; i++)
	{
		free(list->Content[i]);
	}
	list->count = 0;
}