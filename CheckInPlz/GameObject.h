#pragma once
#include "define.h"


typedef enum CollisionState //콜리젼 상태 정의하는 열거형
{
	Enter, //막 충돌했다. 
	Exit, //막 충돌 상태에서 벗어났다. 
	Stay, //충돌 상태가 유지되고 있다.
	Not //충돌하지 않고 있다.
}CollisionState;

//collision
typedef struct CollisionResponse //충돌시, 총돌 상태와 함께 부딪힌 겜옵젝까지 표시
{
	CollisionState state;  //충돌 상태 나타내는 객체.
	struct GameObject* other;  //본 겜옵젝과 충돌한 타 옵젝 정보.
}CollisionResponse;

CollisionResponse CheckAABB(GameObject* t, GameObject* other);
//AABB형(꼭짓점 비교) 충돌 체크 함수이다. 
//(자신, 상대 옵젝) 순서대로 들어감, 
//CollisionResponse 리턴.

Bool GameObjectCollide(GameObject* t, struct 
GameObject* other, Bool collide);
//Bool GameObjectCollide(겜옵젝 자신, 체크할 게임 오브젝트, 충돌했는지에 대한 Bool);
//내부 CheckAABB 활용 위해
//부딪혔는지 Bool 자료형으로 리턴하는 함수

void GameObjectSetRect(GameObject* t, int size_x, int size_y);
//GameObject의 물리적 범위(사이즈)를 설정하는 함수

void SetTag(GameObject* t, char* tag);
//void SetTag(겜옵젝 자신, 태그);
//게임 오브젝트에 태그를 부여한다.

extern Bool CompareTag(char*, char*);
//extern Bool CompareTag(태그, 태그);
//매개변수 두 개에는 모두 태그가 들어가고, 이가 같은지 Bool형으로 리턴.

//virtual func
void DefaultGameObjectFunction(GameObject* t);
void DefaultUpdate(GameObject* t, double dt);
void DefaultCollisionFunction(GameObject* t, CollisionResponse response);
DWORD WINAPI DefaultDrawFunction(GameObject*);
//C에서 가상함수에 대응하는 역할이다.
//각 오브젝트에서 '상속' (실질적으로는 함수 포인터 재참조)를 통해
//커스텀 동작 가능.

//register
 struct GameObject {
	GameObject* t; //본 오브젝트
	///여기서부터 다른 겜옵젝의 c/h에서 재정의해야 하는 내용.
	void (*Start)(GameObject* t);
	//씬 시작시 발동되는 함수
	void (*Update)(GameObject* t,double dt);
	//매 순간 업데이트되는 함수.
	DWORD (WINAPI *Draw)(LPVOID t);
	void (*OnDestroy)(GameObject* t);
	void (*OnEnable)(GameObject* t);
	void (*OnDisable)(GameObject* t);
	void (*OnCollisionEnter)(GameObject*, CollisionResponse);
	void (*OnCollisionExit)(GameObject* , CollisionResponse);
	void (*OnCollisionStay)(GameObject* , CollisionResponse);
	void (*SetRect)(GameObject* t, int size_x, int size_y);
	void (*SetTag)(GameObject* t, char* tag);

	Bool (*Collide)(GameObject* t, GameObject* other, Bool collided);
	//충돌했는지 Bool값을 리턴하는 함수, 위에 상술.
	Transform transform; //Transform 값 정의(2차원 좌표, 기울기, 사이즈)
	Bool collider; //true면 콜라이더를 키는 것(충돌 처리 가능)
	Bool enter;
	Bool started;
	Bool isEnabled;
	rect2D rect;  //오브젝트의 범위를 규정하는 rect.
	char tag[30]; //오브젝트가 갖고 있는 태그 규정.
	void* property; //추가적으로 void 포인터형 property, 
	//추가 구조체 지정으로 추가적인 옵젝별 특정 지정 가능. 
	int renderOrder;
	Bool rigidbody;
};
//


extern void Enable(GameObject* t); //옵젝 활성화
extern void Disable(GameObject* t); //옵젝 비활성화
GameObject* CreateGameObject(); //외부에서 겜옵젝 만들 때 실행하는 함수. 