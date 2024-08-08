#include "vmath.h"
float Length(vector2 v)
{
	return (float)(pow(v.x* v.x + v.y* v.y, 0.5));
}
float Distance(vector2 v1, vector2 v2)
{
	float result = (float)pow((v1.x - v2.x)* (v1.x - v2.x) + (v1.y - v2.y)* (v1.y - v2.y),0.5);
	return result;
}

vector2 Normalize(vector2 v)
{
	vector2 result = { v.x / Length(v),v.y / Length(v) };
	return result;
}

float Dot(vector2 v1,vector2 v2)
{
	float result = v1.x * v2.x + v1.y * v2.y;
	return result;
}


extern Vmath vmath = {
	Length,
	Normalize,
	Dot,
	Distance
};