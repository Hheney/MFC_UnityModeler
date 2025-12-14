#include "pch.h"
#include "MyScreen.h"
#include "OglTransform.h"

MyScreen::MyScreen(void)
{
	SetBackColor(RGB(128, 128, 128));
}

void MyScreen::AddGameObject(const OglTransform& ot)
{
	m_arGameObj.Add(ot);	// 게임 객체 변환 정보 배열에 추가
	Invalidate(FALSE);		// 화면 갱신 요청
}

void MyScreen::ClearGameObjects(void)
{
	m_arGameObj.RemoveAll();	// 게임 객체 변환 정보 배열 비우기
	Invalidate(FALSE);			// 화면 갱신 요청
}

int MyScreen::GetGameObjectCount(void) const
{
	return (int)m_arGameObj.GetCount();	// 게임 객체 변환 정보 배열의 원소 개수 반환
}

void MyScreen::SampleMultiGameObj(void)
{
	// CArray: MFC가 제공하는 가변 배열; 크기 조정 가능(크기 조정할 때는 속도가 느려짐)
	CArray<OglTransform, OglTransform&> ar; // <,> 의미: template; < data type, argument(access) type>
	OglTransform ot;
	// #0 element
	ot.m_nType = GameObjType::SPHERE;
	ot.m_nColor = RGB(255, 0, 0);
	ot.m_alpha = 1.f;
	ot.m_translate = Vector3(100.f, 100.f, 0.f);
	ot.m_scale = Vector3(0.5f, 1.f, 1.f);
	ar.Add(ot);
	// #1 element
	ot.m_nType = GameObjType::SPHERE;
	ot.m_nColor = RGB(0, 255, 0);
	ot.m_alpha = 1.f;
	ot.m_translate = Vector3(-100.f, 100.f, 0.f);
	ot.m_scale = Vector3(1.f, 1.f, 1.f);
	ar.Add(ot);
	// #2 element
	ot.m_nType = GameObjType::CUBE;
	ot.m_nColor = RGB(0, 0, 255);
	ot.m_alpha = 1.f;
	ot.m_translate = Vector3(-100.f, -100.f, 0.f);
	ot.m_scale = Vector3(1.f, 1.f, 1.f);
	ot.m_rotate = Vector3(45.f, 45.f, 0.f);
	ar.Add(ot);

	// #2 element
	ot.m_nType = GameObjType::CUBE;
	ot.m_nColor = RGB(0, 0, 0);
	ot.m_alpha = -1.f;
	ot.m_translate = Vector3(100.f, -100.f, 0.f);
	ot.m_scale = Vector3(2.f, 2.f, 2.f);
	ot.m_rotate = Vector3(45.f, 45.f, 0.f);
	ar.Add(ot);

	// #3 element
	ot.m_nType = GameObjType::CYLINDER;
	ot.m_nColor = RGB(255, 0, 255);
	ot.m_alpha = 1.f;
	ot.m_translate = Vector3(0.f, 0.f, 0.f);
	ot.m_scale = Vector3(1.f, 1.f, 1.f);
	ot.m_rotate = Vector3(45.f, 0.f, 0.f);
	ar.Add(ot);

	// 배열의 모든 원소를 렌더링
	for (int i = 0; i < ar.GetCount(); i++)
	{
		OglTransform elt = ar[i]; // 현재 렌더링할 원소
		switch (elt.m_nType)
		{
		case GameObjType::SPHERE:
			m_sphere.Draw(elt);
			break;
		case GameObjType::CUBE:
			m_cube.Draw(elt);
			break;
		case GameObjType::CYLINDER:
			m_cylinder.Draw(elt);
			break;
		}
	}
}

void MyScreen::InitOpenGL(void)
{
	OglScreen::InitOpenGL();

	StartRC();

	m_lightMtl.SetLightParam();
	m_sphere.Create();
	m_cylinder.Create();
	SetViewport();

	StopRC();
}

void MyScreen::InitRender(void)
{
	OglScreen::InitRender();
}

void MyScreen::RenderScene(void)
{
	OglScreen::RenderScene();

	//SampleMultiGameObj();
	
	RenderAllGameObjects(); // 배열의 모든 게임 객체를 렌더링
}

void MyScreen::RenderAllGameObjects(void)
{
	// 배열의 모든 게임 객체를 렌더링
	for (int i = 0; i < m_arGameObj.GetCount(); i++)
	{
		const OglTransform& elt = m_arGameObj[i];

		switch (elt.m_nType)
		{
		case GameObjType::SPHERE:
			m_sphere.Draw(elt);
			break;

		case GameObjType::CUBE:
			m_cube.Draw(elt);
			break;

		case GameObjType::CYLINDER:
			m_cylinder.Draw(elt);
			break;

		default:
			break;
		}
	}
}
