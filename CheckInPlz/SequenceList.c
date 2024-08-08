#include "SequenceList.h"


SequenceList* CreateSequenceList()
{
	SequenceList* list = (SequenceList*)malloc(sizeof(SequenceList));
	list->Content = (Sequence**)malloc(sizeof(Sequence*) * 100);
	list->count = 0;
	list->Add = AddSequence;
	list->Remove = RemoveSequence;
	list->Clear = ClearSequence;
	list->isEmpty = SequenceisEmpty;
	list->Exist = SequenceExist;
	return list;
}

Bool SequenceExist(SequenceList* list, int obj)
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

void AddSequence(SequenceList* list, int obj)
{
	list->Content[list->count] = obj;
	list->count++;
}

Sequence* RemoveSequence(SequenceList* list, int obj)
{
	Sequence* check = 0;
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
Bool SequenceisEmpty(SequenceList* list)
{
	return list->count ? 0 : 1;
}
void ClearSequence(SequenceList* list)
{
	for (int i = 0; i < list->count; i++)
	{
		free(list->Content[i]);
	}
	list->count = 0;
}