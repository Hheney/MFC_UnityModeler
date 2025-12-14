#include "pch.h"
#include "OglLightMtl.h"

OglLightMtl::OglLightMtl(void)
{
	DefLightParam();
}

void OglLightMtl::SetLightParam(bool bStartRC)
{
	if (bStartRC) StartRC();

	// 광원
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0); // 0번 광원을 사용 가능하게 함

	glLightfv(GL_LIGHT0, GL_AMBIENT, m_lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, m_lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, m_lightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, m_lightPos);

	// material
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_lightAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_lightDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_lightSpecular);
	glMaterialfv(GL_FRONT, GL_EMISSION, m_mtlEmit);
	glMaterialf(GL_FRONT, GL_SHININESS, m_mtlShine);

	if (bStartRC) StopRC();
}

void OglLightMtl::DefLightParam(void)
{
	// light
	m_lightAmbient[0] = m_lightAmbient[1] = m_lightAmbient[2] = 0.2f; // RGB 순서
	m_lightAmbient[3] = 1.0f; // alpha
	m_lightDiffuse[0] = m_lightDiffuse[1] = m_lightDiffuse[2] = 0.5f; // RGB 순서
	m_lightDiffuse[3] = 1.0f; // alpha
	m_lightSpecular[0] = m_lightSpecular[1] = m_lightSpecular[2] = 0.9f; // RGB 순서
	m_lightSpecular[3] = 1.0f; // alpha
	m_lightPos[0] = m_lightPos[1] = m_lightPos[2] = 1.0f; // (x, y, z) 순서
	m_lightPos[3] = 0.0f; // 직사광선(태양광) 선택

	// material
	m_mtlEmit[0] = m_mtlEmit[1] = m_mtlEmit[2] = 0.0f; // RGB 순서
	m_mtlEmit[3] = 1.0f; // alpha
	m_mtlShine = 100.0f;
}

void OglLightMtl::StartRC(void)
{
	::wglMakeCurrent(m_hDC, m_hRC);
}

void OglLightMtl::StopRC(void)
{
	::wglMakeCurrent(m_hDC, NULL);
}