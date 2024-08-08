#include "ChandRightLight.h"
#include <time.h>
#include <math.h>

static AnimationData* anim;
typedef struct ChandRightLightProp
{
	HBITMAP RightLight;
	//HBITMAP rightLight;
	int cntInverter;


}ChandRightLightProp;

///

HBITMAP GetRotatedBitmapOffset2(HDC hdc, HBITMAP hBitmap, int source_x, int source_y, int dest_width, int dest_height, float angle, int xOffset, int yOffset)
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
	BitBlt(destDC, -(dest_width / 2) + xOffset, -(dest_height / 2) + yOffset, dest_width + xOffset, dest_height + yOffset, sourceDC, source_x, source_y, SRCCOPY);


	SelectObject(sourceDC, hbmOldSource);
	SelectObject(destDC, hbmOldDest);
	DeleteObject(sourceDC);
	DeleteObject(destDC);
	return hbmResult;
}



void DrawBitmapOffset2(GameObject* this, HBITMAP bmp, float alpha, int xOffset, int yOffset)
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
		hTempBitmap = GetRotatedBitmapOffset2(hdc, bmp, 0, 0, btSize.bmWidth, btSize.bmHeight, this->transform.rotation, xOffset, yOffset);
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


GameObject* CreateChandRightLight()
{
	ChandRightLightProp* property = (ChandRightLightProp*)malloc(sizeof(ChandRightLightProp));
	if (property == NULL)
	{
		return NULL;
	}

	Transform transform = { {1600.f,80.f},0.f,{0.7f,0.7f} };
	GameObject* obj = CreateGameObject();
	obj->transform = transform;
	obj->transform.position = transform.position;
	obj->transform.scale = transform.scale;
	obj->Start = ChandRightLightStart;
	obj->Draw = ChandRightLightDraw;
	obj->Update = ChandRightLightUpdate;
	obj->property = property;

	property->RightLight = render.LoadBitmapImage(L"Resources\\TitleUI\\NEWChandRight.bmp");
	//property->rightLight = render.LoadBitmapImage(L"Resources\\TitleUI\\NEWChandRight.bmp");

	property->cntInverter = 1;
	//property->dirChand = false;

	//obj->SetRect(obj, 407,676);
	obj->SetRect(obj, 1200, 1400);
	obj->SetTag(obj, "ChandRightLight");
	obj->collider = false;
	obj->renderOrder = UI_ORDER - 5;

	//Pre 밑으로 내려서 돌려서 y값으로 돌려라. 

	obj->OnDestroy = ChandRightLightOnDestroy;
	return obj;
}



void ChandRightLightStart(GameObject* this)
{
	anim=Animate(this, &this->transform.rotation, PLAYBACK_LOOP_PINGPONG, -10, EASING_OUTQUAD, 9.2f, NULL);
}

void ChandRightLightUpdate(GameObject* this, double dt)
{
	ChandRightLightProp* prop = this->property;

}

DWORD WINAPI ChandRightLightDraw(GameObject* this)
{
	ChandRightLightProp* prop = this->property;

	DrawBitmapOffset2(this, prop->RightLight, 1, 0, 500);

	return 0;
}

void ChandRightLightOnDestroy(GameObject* this)
{
	ChandRightLightProp* prop = this->property;
	CancelAnimation(anim);
	free(prop);
}


