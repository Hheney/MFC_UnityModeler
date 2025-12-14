#include "pch.h"
#include "MyScreen.h"
#include "OglTransform.h"

MyScreen::MyScreen(void)
{
	SetBackColor(RGB(0, 0, 255));
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

	SampleMultiGameObj();
	//m_sphere.SetRgba(RGB(0, 255, 0));
	//m_sphere.Draw(100.);
}