#pragma once
#include "define.h"
#include "Engine.h"
#include "vmath.h"
typedef struct RaycastResponse { //레이캐스팅 반응, 구조체. 
	Bool hit; //가상의 Ray가 물체에 닿았는지 대한 Bool값.
	vector2 position; //Ray가 닿은 위치 저장.
	char tag[30];  //닿은 물체의 태그 저장.
}RaycastResponse;

typedef struct RaycastData { //레이캐스팅 반응, 구조체. 
	int count; //가상의 Ray가 물체에 닿았는지 대한 Bool값.
	GameObject* obj;
	char** tags;
	int tagsize;
	vector2 d;
	vector2 from;
	RaycastResponse result;
	Bool exit;
}RaycastData;


typedef struct Physics { //믈리 구조체 정의

	Bool (* InBound)(GameObject*, vector2);
	Bool (* InBoundRect)(rect2D, vector2);
	RaycastResponse (* Raycast)(vector2, vector2, char*[], int);
}Physics;



Bool InBound(GameObject*, vector2);
//앞 GameObject*의 Rect안에, 뒤의 vector2 좌표가 있는지 Bool형 반환.
Bool InBoundRect(rect2D, vector2);
//앞 rect2D 형태 안에, 뒤의 vector2 좌표가 있는지 Bool형 반환.


RaycastResponse Raycast(vector2, vector2, char *[], int);
//RaycastResponse형태로 반환,
//(Ray 출발 좌표, Ray 목표 좌표, 태그들의 목록)

extern Physics physics;
//외부 사용 위한 물리 정의.