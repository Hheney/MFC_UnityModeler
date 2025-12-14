#include "pch.h"
#include "OglCylinder.h"
#include "OglScreen.h"

OglCylinder::OglCylinder(void)
{
	m_pQobj = nullptr; // null pointer; NULL도 가능
	m_nColor = RGB(255, 0, 0);
	m_alpha = 1.0f;
}

OglCylinder::~OglCylinder()
{
	if (m_pQobj) gluDeleteQuadric(m_pQobj);
}

void OglCylinder::Create(void)
{
	if (m_pQobj) gluDeleteQuadric(m_pQobj);
	m_pQobj = gluNewQuadric();
	gluQuadricDrawStyle(m_pQobj, GLU_FILL);
	gluQuadricNormals(m_pQobj, GLU_SMOOTH);
}

void OglCylinder::Draw(GLdouble radius, GLdouble ht, GLint slice, GLint stack) const
{
	if (m_pQobj)
	{
		GLfloat r, g, b;
		OglScreen::colorrefToRgb(r, g, b, m_nColor);
		glColor4f(r, g, b, m_alpha); // glColor3f() 써도 됨: alpha = 1인 경우
		gluCylinder(m_pQobj, radius, radius, ht, slice, stack); // gluSphere에서 함수만 교체
	}
}

void OglCylinder::Draw(const OglTransform& ot)
{
	glPushMatrix();
	glLoadIdentity();
	ot.Transform();
	SetRgba(ot.m_nColor, ot.m_alpha);
	DrawDef();
	glPopMatrix();
}

void OglCylinder::DrawDef(void)
{
	Draw(m_defRad, m_defRad * 4.);
}
