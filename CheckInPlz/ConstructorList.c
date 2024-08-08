#include "ConstructorList.h"

ConstructorList* CreateConstructorList()
{
	ConstructorList* list = (ConstructorList*)malloc(sizeof(ConstructorList));
	if (list == NULL)
	{
		return NULL;
	}
	list->Content = (Constructor*)malloc(sizeof(Constructor) * MAX_GAMEOBJECT);
	list->count = 0;
	list->Add = AddConstructor;
	list->Remove = RemoveConstructor;
	list->Clear = ClearConstructor;
	list->isEmpty = ConstructorisEmpty;
	return list;
}


void AddConstructor(ConstructorList* list, Constructor obj)
{
	list->Content[list->count] = obj;
	list->count++;
}
Constructor RemoveConstructor(ConstructorList* list, Constructor obj)
{
	Constructor check = NULL;
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
	list->count--;
	return check;
}
Bool ConstructorisEmpty(ConstructorList* list)
{
	return list->count ? 0 : 1;
}
void ClearConstructor(ConstructorList* list)
{
	list->count = 0;
}