#pragma once
#include <math.h>
typedef struct vector2
{
	float x;
	float y; //2차원 공간에서의 벡터 묘사 방법.
}vector2;


float Length(vector2 v);
//벡터의 길이 

vector2 Normalize(vector2 v); //벡터 정규화
//vector2 Normalize(벡터 객체);

float Dot(vector2 v1, vector2 v2); //벡터 내적
//vector2 Dot(벡터객체1, 벡터객체2);

float Distance(vector2 v1, vector2 v2);  //좌표 사이의 거리
//vector2 Distance(벡터객체1, 벡터객체2);

vector2 Cross(vector2 v1, vector2 v2); //벡터 곱
//vector2 Cross(벡터객체1, 벡터객체2);

typedef struct Vmath {
	float (*Length)(vector2 v);
	vector2 (*Normalize)(vector2 v);
	float (*Dot)(vector2 v1, vector2 v2);
	float (*Distance)(vector2 v1, vector2 v2);
}Vmath;

typedef struct rect2D
{
	vector2 min; //최소의 2차원 벡터값
	vector2 max; //최대의 2차원 벡터값
}rect2D;

extern Vmath vmath;