#include "HBITMAPList.h"
HBITMAPList* CreateHBITMAPList()
{
	HBITMAPList* list = (HBITMAPList*)malloc(sizeof(HBITMAPList));
	list->Content = (int*)malloc(sizeof(int) * 100);
	list->count = 0;
	list->Add = AddHBITMAP;
	list->Remove = RemoveHBITMAP;
	list->Clear = ClearHBITMAP;
	list->isEmpty = HBITMAPisEmpty;
	list->Exist = HBITMAPExist;
	return list;
}

Bool HBITMAPExist(HBITMAPList* list, HBITMAP obj)
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

void AddHBITMAP(HBITMAPList* list, HBITMAP obj)
{
	list->Content[list->count] = obj;
	list->count++;
}

HBITMAP RemoveHBITMAP(HBITMAPList* list, HBITMAP obj)
{
	HBITMAP check=NULL;
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

Bool HBITMAPisEmpty(HBITMAPList* list)
{
	return list->count ? 0 : 1;
}

void ClearHBITMAP(HBITMAPList* list)
{
	list->count = 0;
}