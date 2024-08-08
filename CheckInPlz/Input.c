#include "Input.h"

int MouseWheel = 1;

void InitializeInput()
{
	Pressed = CreateIntegerList();
	Released = CreateIntegerList();
	KeyStructure L = { VK_LBUTTON,false,false };
	KeyStructure R = { VK_RBUTTON,false,false };
	KeyStructure M = { VK_MBUTTON,false,false };
	Mouse[0] = L;
	Mouse[1] = R; 
	Mouse[2] = M;
}

void UpdateInput()
{
	static Bool PressedCheck[3] = { false,false,false };
	static Bool ReleasedCheck[3] = { false,false,false };
	for (int i = 0; i < 2; i++)
	{
		if (GetAsyncKeyState(Mouse[i].keyCode))
		{
			if (!Mouse[i].pressed && !PressedCheck[i])
			{
				Mouse[i].pressed = true;
				PressedCheck[i] = true;
			}
			else
			{
				Mouse[i].pressed = false;
			}
		}
		else
		{
				Mouse[i].pressed = false;
				PressedCheck[i] = false;
		}
	}
	for (int i = 0; i < 2; i++)
	{
		if (GetAsyncKeyState(Mouse[i].keyCode))
		{
			Mouse[i].released = false;
			ReleasedCheck[i] = false;
		}
		else
		{
			if (!Mouse[i].released && !ReleasedCheck[i])
			{
				Mouse[i].released = true;
				ReleasedCheck[i] = true;
			}
			else
			{
				Mouse[i].released = false;
			}

		}
	}
	
}

vector2 GetMousePosition()
{
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(m_hWnd, &p);
	vector2 vec = { (float)(p.x), (float)(p.y) };
	return vec;
}

Bool GetMouseButton(int btn)
{
	if (GetAsyncKeyState(Mouse[btn].keyCode))
		return true;
	else
		return false;
}

Bool GetMouseButtonDown(int btn)
{
	
	if (Mouse[btn].pressed)
	{
		return true;
	}
	return false;
}

Bool GetMouseButtonUp(int btn)
{
	if (Mouse[btn].released)
	{
		return true;
	}
	return false;
}

int GetMouseWheel()
{
	return MouseWheel;
}

Bool GetKeyDown(int key)
{
	if (GetAsyncKeyState(key) )
	{
		if (!Pressed->Exist(Pressed, key))
		{
			Pressed->Add(Pressed, key);
			return true;
		}
	}
	else
	{
		if (Pressed->Exist(Pressed, key))
			Pressed->Remove(Pressed, key);
	}
	return false;
}

Bool GetKeyUp(int key)
{
	if (GetAsyncKeyState(key))
	{
		if (!Released->Exist(Released, key))
		{
			Released->Add(Released, key);
		}
	}
	else
	{
		if (Released->Exist(Released, key))
		{
			Released->Remove(Released, key);
			return true;
		}

	}
	return false;
}

Bool GetKey(int key)
{
	if (GetAsyncKeyState(key))
		return true;
	else
		return false;
}

void KeyPressed(int key)
{
	Pressed->Add(Pressed,key);
	Released->Remove(Released,key);
}

void KeyReleased(int key)
{
	Released->Add(Released, key);
	Pressed->Remove(Pressed, key);
}

void MousePressed(int btn)
{
	Mouse[btn].pressed = true;
	Mouse[btn].released = false;
}
void MouseReleased(int btn)
{
	Mouse[btn].pressed = false;
	Mouse[btn].released = true;
}

const Input input = {
	InitializeInput,
	UpdateInput,
	GetMousePosition,
	GetMouseButton,
	GetMouseButtonDown,
	GetMouseButtonUp,
	GetKeyDown,
	GetKeyUp,
	GetKey,
	KeyPressed,
	KeyReleased,
	MousePressed,
	MouseReleased,
};