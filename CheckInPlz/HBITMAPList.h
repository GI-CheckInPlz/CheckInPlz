#pragma once
#pragma once
#include "define.h"




typedef struct HBITMAPList
{
	HBITMAP* Content; //내용
	int count; //비트맵 리스트의 길이
	void (*Add)(struct HBITMAPList*, HBITMAP);
	//	void (*Add)(비트맵 리스트 포인터, 추가하려는 이미지 아이디);

	HBITMAP(*Remove)(struct HBITMAPList*, HBITMAP);
	//	char (*Remove)(비트맵 리스트 포인터, 추가하려는 이미지 아이디);

	void (*Clear)(struct HBITMAPList*);
	//	void (*Clear)(내용을 클리어할 비트맵 리스트 포인터);

	int (*isEmpty)(struct HBITMAPList* sPtr);
	//	int (*isEmpty)(내용이 비었는지를 확인할 비트맵 리스트 포인터);

	Bool(*Exist)(struct HBITMAPList* list, int obj);
	//	Bool(*Exist)(확인할 비트맵 리스트 포인터, 추가하려는 이미지 아이디);

}HBITMAPList;

//외부 사용, 생성할 때
extern HBITMAPList* CreateHBITMAPList();

//1대1 대응
void AddHBITMAP(HBITMAPList*, HBITMAP);
HBITMAP RemoveHBITMAP(HBITMAPList*, HBITMAP);
Bool HBITMAPisEmpty(HBITMAPList*);
void ClearHBITMAP(HBITMAPList*);
Bool HBITMAPExist(HBITMAPList* list, HBITMAP obj);



