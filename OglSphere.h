#pragma once
#include <GL/glew.h>

#define DEF_SPH_SLICE	(30)
#define DEF_SPH_STACK	(30)

#include "OglTransform.h"

class OglSphere
{
public:
	OglSphere(void);
	~OglSphere();

	void SetRgba(COLORREF col, GLfloat alpha = 1.0f)
	{
		m_nColor = col;
		m_alpha = alpha;
	}
	void Create(void);
	void Draw(GLdouble radius, GLint slice = DEF_SPH_SLICE, GLint stack = DEF_SPH_STACK) const;
	void Draw(const OglTransform& ot);
	void DrawDef(void);

protected:
	GLUquadric* m_pQobj;
	COLORREF m_nColor;
	GLfloat m_alpha;
	const GLdouble m_defRad = 20.; // Áö¸§ = m_defRad*2
};

#undef DEF_SPH_SLICE
#undef DEF_SPH_STACK

