#pragma once
#include "define.h"




typedef struct IntegerList
{
	int* Content; //���� ����Ʈ �� ���빰.
	int count; //����Ʈ�� ����
	void (*Add)(struct IntegerList*, int); 
	//void (*Add)(�ְ� ���� ��Ƽ�� ����Ʈ ������, �߰��� ��Ƽ�� ��);
	char (*Remove)(struct IntegerList*, int);
	//char (*Remove)(�����ϰ� ���� ��Ƽ�� ����Ʈ ������, ������ ��Ƽ�� ��);
	void (*Clear)(struct IntegerList*);
	//void (*Clear)(���� Ŭ�����ϰ� ���� ��Ƽ�� ����Ʈ ������);
	int (*isEmpty)(struct IntegerList* sPtr);
	//int (*IsEmpty)(������ ������� Ȯ���ϰ� ���� ��Ƽ�� ����Ʈ ������);

	Bool(*Exist)(struct IntegerList* list, int obj);
	//Bool(*Exist)(Ȯ���� ��Ƽ�� ����Ʈ ������, �˻��� ������Ʈ int ���̵�);
}IntegerList;

extern IntegerList* CreateIntegerList();

void AddInteger(IntegerList*, int);
int RemoveInteger(IntegerList*, int);
Bool IntegerisEmpty(IntegerList*);
void ClearInteger(IntegerList*);
Bool IntegerExist(IntegerList* list, int obj);



