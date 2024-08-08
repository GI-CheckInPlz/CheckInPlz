#pragma once
#include "define.h"
#include "GameObject.h"
#include "define.h"
#include "GameObject.h"


typedef struct ConstructorList
{
	Constructor* Content;
	int count;

	void (*Add)(struct ConstructorList*, Constructor);
	char (*Remove)(struct ConstructorList*, Constructor);
	void (*Clear)(struct ConstructorList*);
	int (*isEmpty)(struct ConstructorList* sPtr);
}ConstructorList;

extern ConstructorList* CreateConstructorList();

void AddConstructor(ConstructorList*, Constructor);
Constructor RemoveConstructor(ConstructorList*, Constructor);
Bool ConstructorisEmpty(ConstructorList*);
void ClearConstructor(ConstructorList*);




