#include "pch.h"
#include "OglSphere.h"
#include "OglScreen.h"

OglSphere::OglSphere(void)
{
	m_pQobj = nullptr; // null pointer; NULL도 가능
	m_nColor = RGB(255, 0, 0);
	m_alpha = 1.0f;
}

OglSphere::~OglSphere()
{
	if (m_pQobj) gluDeleteQuadric(m_pQobj);
}

void OglSphere::Create(void)
{
	if (m_pQobj) gluDeleteQuadric(m_pQobj);
	m_pQobj = gluNewQuadric();
	gluQuadricDrawStyle(m_pQobj, GLU_FILL);
	gluQuadricNormals(m_pQobj, GLU_SMOOTH);
}

void OglSphere::Draw(GLdouble radius, GLint slice, GLint stack) const
{
	if (m_pQobj)
	{
		GLfloat r, g, b;
		OglScreen::colorrefToRgb(r, g, b, m_nColor);
		glColor4f(r, g, b, m_alpha); // glColor3f() 써도 됨: alpha = 1인 경우
		gluSphere(m_pQobj, radius, slice, stack);
	}
}

void OglSphere::Draw(const OglTransform& ot)
{
	glPushMatrix();
	glLoadIdentity();
	ot.Transform();
	SetRgba(ot.m_nColor, ot.m_alpha);
	DrawDef();
	glPopMatrix();
}

void OglSphere::DrawDef(void)
{
	Draw(m_defRad);
}
