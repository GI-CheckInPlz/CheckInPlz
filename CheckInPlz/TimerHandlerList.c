#include "TimerHandlerList.h"

TimerHandlerList* CreateTimerHandlerList()
{
	TimerHandlerList* list = (TimerHandlerList*)malloc(sizeof(TimerHandlerList));
	list->Content = (TimerHandler**)malloc(sizeof(TimerHandler*) * MAX_TIMER);
	list->count = 0;
	list->Add = AddTimerHandler;
	list->Remove = RemoveTimerHandler;
	list->RemoveAt = RemoveAtTimerHandler;
	list->Clear = ClearTimerHandler;
	list->isEmpty = TimerHandlerisEmpty;
	return list;
}

void AddTimerHandler(TimerHandlerList* list, TimerHandler** obj)
{
	list->Content[list->count] = obj;
	list->count++;
}


TimerHandler* RemoveAtTimerHandler(TimerHandlerList* list, int index)
{
	TimerHandler* check = NULL;
	for (int i = 0; i < list->count; i++)
	{
		if (check)
		{
			list->Content[i - 1] = list->Content[i];
		}
		if (i == index)
		{
			check = list->Content[i];
		}
	}
	list->count--;
	return check;
}

TimerHandler* RemoveTimerHandler(TimerHandlerList* list, TimerHandler** obj)
{
	TimerHandler* check = NULL;
	for (int i = 0; i < list->count; i++)
	{
		if (check)
		{
			list->Content[i - 1] = list->Content[i];
		}
		if (list->Content[i] == *obj)
		{
			check = list->Content[i];
		}
	}
	list->count--;
	return check;
}
Bool TimerHandlerisEmpty(TimerHandlerList* list)
{
	return list->count ? 0 : 1;
}

void ClearTimerHandler(TimerHandlerList* list)
{
	list->count = 0;
}