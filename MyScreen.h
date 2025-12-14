#pragma once

#include "OglScreen.h"
#include "OglLightMtl.h"
#include "OglSphere.h"
#include "OglCube.h"
#include "OglCylinder.h"

class MyScreen :
	public OglScreen
{
public:
	MyScreen(void);

protected:
	OglLightMtl m_lightMtl;
	OglSphere m_sphere;
	OglCube m_cube;
	OglCylinder m_cylinder;

	void SampleMultiGameObj(void);

	virtual void InitOpenGL(void);
	virtual void InitRender(void);
	virtual void RenderScene(void);
};

