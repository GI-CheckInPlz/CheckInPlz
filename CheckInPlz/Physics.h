#pragma once
#include "define.h"
#include "Engine.h"
#include "vmath.h"
typedef struct RaycastResponse { //����ĳ���� ����, ����ü. 
	Bool hit; //������ Ray�� ��ü�� ��Ҵ��� ���� Bool��.
	vector2 position; //Ray�� ���� ��ġ ����.
	char tag[30];  //���� ��ü�� �±� ����.
}RaycastResponse;

typedef struct RaycastData { //����ĳ���� ����, ����ü. 
	int count; //������ Ray�� ��ü�� ��Ҵ��� ���� Bool��.
	GameObject* obj;
	char** tags;
	int tagsize;
	vector2 d;
	vector2 from;
	RaycastResponse result;
	Bool exit;
}RaycastData;


typedef struct Physics { //�ɸ� ����ü ����

	Bool (* InBound)(GameObject*, vector2);
	Bool (* InBoundRect)(rect2D, vector2);
	RaycastResponse (* Raycast)(vector2, vector2, char*[], int);
}Physics;



Bool InBound(GameObject*, vector2);
//�� GameObject*�� Rect�ȿ�, ���� vector2 ��ǥ�� �ִ��� Bool�� ��ȯ.
Bool InBoundRect(rect2D, vector2);
//�� rect2D ���� �ȿ�, ���� vector2 ��ǥ�� �ִ��� Bool�� ��ȯ.


RaycastResponse Raycast(vector2, vector2, char *[], int);
//RaycastResponse���·� ��ȯ,
//(Ray ��� ��ǥ, Ray ��ǥ ��ǥ, �±׵��� ���)

extern Physics physics;
//�ܺ� ��� ���� ���� ����.