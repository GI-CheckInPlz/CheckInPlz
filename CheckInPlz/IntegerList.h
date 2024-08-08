#pragma once
#include "define.h"




typedef struct IntegerList
{
	int* Content; //실제 리스트 내 내용물.
	int count; //리스트의 길이
	void (*Add)(struct IntegerList*, int); 
	//void (*Add)(넣고 싶은 인티저 리스트 포인터, 추가할 인티저 값);
	char (*Remove)(struct IntegerList*, int);
	//char (*Remove)(변경하고 싶은 인티저 리스트 포인터, 삭제할 인티저 값);
	void (*Clear)(struct IntegerList*);
	//void (*Clear)(내용 클리어하고 싶은 인티저 리스트 포인터);
	int (*isEmpty)(struct IntegerList* sPtr);
	//int (*IsEmpty)(내용이 비었는지 확인하고 싶은 인티저 리스트 포인터);

	Bool(*Exist)(struct IntegerList* list, int obj);
	//Bool(*Exist)(확인할 인티저 리스트 포인터, 검색할 오브젝트 int 아이디);
}IntegerList;

extern IntegerList* CreateIntegerList();

void AddInteger(IntegerList*, int);
int RemoveInteger(IntegerList*, int);
Bool IntegerisEmpty(IntegerList*);
void ClearInteger(IntegerList*);
Bool IntegerExist(IntegerList* list, int obj);



