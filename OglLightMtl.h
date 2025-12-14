#pragma once

#include <GL/glew.h>

// OpenGL light & material
class OglLightMtl
{
public:
	OglLightMtl(void);

	void SetDCRC(HDC dc, HGLRC rc)
	{
		m_hDC = dc, m_hRC = rc;
	}
	void SetLightParam(bool bStartRC = false);
	void DefLightParam(void);

	GLfloat m_lightAmbient[4]; // ambient light(주변광): RGBA
	GLfloat m_lightDiffuse[4]; // diffuse light(확산광): RGBA
	GLfloat m_lightSpecular[4]; // specular light(직사광): RGBA
	GLfloat m_lightPos[4];		// 광원 위치 (x, y, z, w): w = 0이면 직사광선, w != 0이면 점 광원
	GLfloat m_mtlEmit[4];		// 물체의 발광(emission) 특성: RGBA
	GLfloat m_mtlShine;			// 물체의 광택: 값이 높을수록 금속처럼 광택이 남

protected:
	HDC m_hDC = NULL;      // OpenGL용 RC를 위한 DC의 핸들(handle)
	HGLRC m_hRC = NULL;    // OpenGL용 RC(rendering context)의 핸들(handle)

	void StartRC(void);
	void StopRC(void);
};

