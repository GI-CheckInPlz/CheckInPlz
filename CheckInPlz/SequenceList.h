#pragma once
#include "define.h"
typedef struct Sequence
{
	float delay;
	int type;
	int floor;
}Sequence;

typedef struct SequenceList
{
	Sequence** Content;
	int count;
	void (*Add)(struct SequenceList*, Sequence*);
	Sequence* (*Remove)(struct SequenceList*, Sequence*);
	void (*Clear)(struct SequenceList*);
	Bool (*isEmpty)(struct SequenceList* sPtr);
	Bool(*Exist)(struct SequenceList* list, Sequence* obj);
}SequenceList;

extern SequenceList* CreateSequenceList();

void AddSequence(SequenceList*, Sequence*);
Sequence* RemoveSequence(SequenceList*, Sequence*);
Bool SequenceisEmpty(SequenceList*);
void ClearSequence(SequenceList*);
Bool SequenceExist(SequenceList* list, Sequence* obj);



