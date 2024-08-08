#include "ChandLeftLight.h"
#include <time.h>
#include <math.h>

static AnimationData* anim;

typedef struct ChandLeftLightProp
{
	HBITMAP leftLight;
	//HBITMAP rightLight;
	int cntInverter;
	

}ChandLeftLightProp;

///

HBITMAP GetRotatedBitmapOffset(HDC hdc, HBITMAP hBitmap, int source_x, int source_y, int dest_width, int dest_height, float angle, int xOffset, int yOffset)
{
	HDC sourceDC = CreateCompatibleDC(hdc);
	HDC destDC = CreateCompatibleDC(hdc);
	HBITMAP hbmResult = CreateCompatibleBitmap(hdc, dest_width, dest_height);
	HBITMAP hbmOldSource = (HBITMAP)SelectObject(sourceDC, hBitmap);
	HBITMAP hbmOldDest = (HBITMAP)SelectObject(destDC, hbmResult);
	HBRUSH hbrBack = CreateSolidBrush(RGB(255, 0, 255));
	HBRUSH hbrOld = (HBRUSH)SelectObject(destDC, hbrBack);
	PatBlt(destDC, 0, 0, dest_width, dest_height, PATCOPY);
	DeleteObject(SelectObject(destDC, hbrOld));
	angle = (float)(angle * PI / 180);
	float cosine = (float)cos(angle);
	float sine = (float)sin(angle);

	SetGraphicsMode(destDC, GM_ADVANCED);

	XFORM xform;
	xform.eM11 = cosine;
	xform.eM12 = sine;
	xform.eM21 = -sine;
	xform.eM22 = cosine;
	xform.eDx = (FLOAT)dest_width / 2.0f;
	xform.eDy = (FLOAT)dest_height / 2.0f;

	SetWorldTransform(destDC, &xform);
	BitBlt(destDC, -(dest_width / 2) + xOffset, -(dest_height / 2)+ yOffset, dest_width + xOffset, dest_height + yOffset, sourceDC, source_x, source_y, SRCCOPY);


	SelectObject(sourceDC, hbmOldSource);
	SelectObject(destDC, hbmOldDest);
	DeleteObject(sourceDC);
	DeleteObject(destDC);
	return hbmResult;
}



void DrawBitmapOffset(GameObject* this, HBITMAP bmp, float alpha, int xOffset, int yOffset)
{
	if (alpha > 0)
	{
		HDC tmp;
		HDC tmpAlpha;
		HBITMAP OldBit = (HBITMAP)SelectObject(MemDC, hBit);
		BITMAP btSize;
		HBITMAP tBit;
		HBITMAP hTempBitmap, hOldBitmap;
		tmp = CreateCompatibleDC(hdc);
		tmpAlpha = CreateCompatibleDC(hdc);

		GetObject(bmp, sizeof(BITMAP), &(btSize));
		tBit = CreateCompatibleBitmap(hdc, (int)(screen.resolution.x), (int)(screen.resolution.y));
		SelectObject(tmpAlpha, tBit);
		int size_x = (int)(btSize.bmWidth * this->transform.scale.x);
		int size_y = (int)(btSize.bmHeight * this->transform.scale.y);
		hTempBitmap = GetRotatedBitmapOffset(hdc, bmp, 0, 0, btSize.bmWidth, btSize.bmHeight, this->transform.rotation, xOffset, yOffset);
		hOldBitmap = (HBITMAP)SelectObject(tmp, hTempBitmap);

		int pos_x = (int)(this->transform.position.x - size_x / 2);
		int pos_y = (int)(this->transform.position.y - size_y / 2);

		BLENDFUNCTION bf;
		bf.AlphaFormat = 0; // 비트맵 종류로 일반 비트맵의 경우 0, 32비트 비트맵의 경우 AC_SRC_ALPHA
		bf.BlendFlags = 0; // 무조건 0이어야 한다
		bf.BlendOp = AC_SRC_OVER; // 무조건 AC_SRC_OVER이어야 하고 원본과 대상 이미지를 합친다는 의미
		bf.SourceConstantAlpha = 255 * alpha; // 투명도(투명 0 - 불투명 255)
		BitBlt(tmpAlpha, 0, 0, size_x, size_y, MemDC, pos_x, pos_y, SRCCOPY);
		TransparentBlt(tmpAlpha, 0, 0, size_x, size_y, tmp, 0, 0, btSize.bmWidth, btSize.bmHeight, RGB(255, 0, 255));
		if (alpha < 1)
		{
			AlphaBlend(MemDC, pos_x, pos_y, size_x, size_y, tmpAlpha, 0, 0, size_x, size_y, bf);
		}
		else
		{
			BitBlt(MemDC, pos_x, pos_y, size_x, size_y, tmpAlpha, 0, 0, SRCCOPY);
		}
		SelectObject(tmp, hOldBitmap);
		DeleteObject(hTempBitmap);
		DeleteObject(tBit);
		DeleteDC(tmp);
		DeleteDC(tmpAlpha);


	}

}

///


GameObject* CreateChandLeftLight()
{
	ChandLeftLightProp* property = (ChandLeftLightProp*)malloc(sizeof(ChandLeftLightProp));
	if (property == NULL)
	{
		return NULL;
	}

	Transform transform = { {300.f,60.f},0.f,{0.7f,0.7f} };
	GameObject* obj = CreateGameObject();
	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Start = ChandLeftLightStart;
	obj->Draw = ChandLeftLightDraw;
	obj->Update = ChandLeftLightUpdate;
	obj->property = property;

	property->leftLight = render.LoadBitmapImage(L"Resources\\TitleUI\\NEWChandLeft.bmp");
	//property->rightLight = render.LoadBitmapImage(L"Resources\\TitleUI\\NEWChandRight.bmp");

	property->cntInverter = 1;
	//property->dirChand = false;

	//obj->SetRect(obj, 407,676);
	obj->SetRect(obj, 1200, 1400);
	obj->SetTag(obj, "ChandLeftLight");
	obj->collider = false;
	obj->renderOrder = UI_ORDER - 5;

	//Pre 밑으로 내려서 돌려서 y값으로 돌려라. 

	obj->OnDestroy = ChandLeftLightOnDestroy;
	return obj;
}



void ChandLeftLightStart(GameObject* this)
{
	anim=Animate(this, &this->transform.rotation, PLAYBACK_LOOP_PINGPONG, 12, EASING_OUTQUAD, 9.3f, NULL);
}

void ChandLeftLightUpdate(GameObject* this, double dt)
{
	ChandLeftLightProp* prop = this->property;
	
}

DWORD WINAPI ChandLeftLightDraw(GameObject* this)
{
	ChandLeftLightProp* prop = this->property;

	DrawBitmapOffset(this, prop->leftLight, 1, 0, 500);

	return 0;
}

void ChandLeftLightOnDestroy(GameObject* this)
{
	ChandLeftLightProp* prop = this->property;
	CancelAnimation(anim);
	free(prop);

}


