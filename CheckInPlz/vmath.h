#pragma once
#include <math.h>
typedef struct vector2
{
	float x;
	float y; //2���� ���������� ���� ���� ���.
}vector2;


float Length(vector2 v);
//������ ���� 

vector2 Normalize(vector2 v); //���� ����ȭ
//vector2 Normalize(���� ��ü);

float Dot(vector2 v1, vector2 v2); //���� ����
//vector2 Dot(���Ͱ�ü1, ���Ͱ�ü2);

float Distance(vector2 v1, vector2 v2);  //��ǥ ������ �Ÿ�
//vector2 Distance(���Ͱ�ü1, ���Ͱ�ü2);

vector2 Cross(vector2 v1, vector2 v2); //���� ��
//vector2 Cross(���Ͱ�ü1, ���Ͱ�ü2);

typedef struct Vmath {
	float (*Length)(vector2 v);
	vector2 (*Normalize)(vector2 v);
	float (*Dot)(vector2 v1, vector2 v2);
	float (*Distance)(vector2 v1, vector2 v2);
}Vmath;

typedef struct rect2D
{
	vector2 min; //�ּ��� 2���� ���Ͱ�
	vector2 max; //�ִ��� 2���� ���Ͱ�
}rect2D;

extern Vmath vmath;