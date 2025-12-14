#pragma once
#define DEF_CYL_SLICE	(30)
#define DEF_CYL_STACK	(30)

#include "OglTransform.h"

class OglCylinder
{
public:
	OglCylinder(void);
	~OglCylinder();

	void SetRgba(COLORREF col, GLfloat alpha = 1.0f)
	{
		m_nColor = col;
		m_alpha = alpha;
	}
	void Create(void);
	void Draw(GLdouble radius, GLdouble ht, GLint slice = DEF_CYL_SLICE, GLint stack = DEF_CYL_STACK) const;
	void Draw(const OglTransform& ot);
	void DrawDef(void);

protected:
	GLUquadric* m_pQobj;
	COLORREF m_nColor;
	GLfloat m_alpha;
	const GLdouble m_defRad = 20.; // Áö¸§ = m_defRad*2
};

#undef DEF_CYL_SLICE
#undef DEF_CYL_STACK