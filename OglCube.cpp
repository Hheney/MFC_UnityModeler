#include "pch.h"
#include "OglCube.h"
#include "OglScreen.h"

OglCube::OglCube(void)
{
	SetRgbaDef();
}

void OglCube::SetRgba(const COLORREF arColor[], const GLfloat arAlpha[])
{
	for (int i = 0; i < 6; i++)
	{
		m_arColor[i] = arColor[i];
		m_arAlpha[i] = arAlpha[i];
	}
}

void OglCube::SetRgba(COLORREF col, GLfloat alpha)
{
	// alpha < 0이면 디폴트 색깔로 설정
	if (alpha < 0.f) SetRgbaDef();
	else
	{
		for (int i = 0; i < 6; i++)
		{
			m_arColor[i] = col;
			m_arAlpha[i] = alpha;
		}
	}
}

void OglCube::SetRgbaDef(void)
{
	m_arColor[0] = RGB(255, 0, 0);
	m_arColor[1] = RGB(0, 255, 0);
	m_arColor[2] = RGB(0, 0, 255);
	m_arColor[3] = RGB(255, 255, 0);
	m_arColor[4] = RGB(0, 255, 255);
	m_arColor[5] = RGB(255, 0, 255);

	for (int i = 0; i < 6; i++)
		m_arAlpha[i] = 1.0f;
}

void OglCube::Draw(GLfloat len) const
{
	GLfloat r, g, b;
	glBegin(GL_QUADS);
	// front facet: 전면(#0)
	OglScreen::colorrefToRgb(r, g, b, m_arColor[0]);
	glColor4f(r, g, b, m_arAlpha[0]);
	glVertex3f(-len, -len, len);
	glVertex3f(len, -len, len);
	glVertex3f(len, len, len);
	glVertex3f(-len, len, len);
	// back facet: 후면(#2)
	OglScreen::colorrefToRgb(r, g, b, m_arColor[2]);
	glColor4f(r, g, b, m_arAlpha[2]);
	glVertex3f(len, -len, -len);
	glVertex3f(-len, -len, -len);
	glVertex3f(-len, len, -len);
	glVertex3f(len, len, -len);
	// right facet: 우면(#1)
	OglScreen::colorrefToRgb(r, g, b, m_arColor[1]);
	glColor4f(r, g, b, m_arAlpha[1]);
	glVertex3f(len, -len, len);
	glVertex3f(len, -len, -len);
	glVertex3f(len, len, -len);
	glVertex3f(len, len, len);
	// left facet: 좌면(#3)
	OglScreen::colorrefToRgb(r, g, b, m_arColor[3]);
	glColor4f(r, g, b, m_arAlpha[3]);
	glVertex3f(-len, -len, -len);
	glVertex3f(-len, -len, len);
	glVertex3f(-len, len, len);
	glVertex3f(-len, len, -len);
	// top facet: 상면(#4)
	OglScreen::colorrefToRgb(r, g, b, m_arColor[4]);
	glColor4f(r, g, b, m_arAlpha[4]);
	glVertex3f(-len, len, len);
	glVertex3f(len, len, len);
	glVertex3f(len, len, -len);
	glVertex3f(-len, len, -len);
	// bottom facet: 하면(#5)
	OglScreen::colorrefToRgb(r, g, b, m_arColor[5]);
	glColor4f(r, g, b, m_arAlpha[5]);
	glVertex3f(-len, -len, -len);
	glVertex3f(len, -len, -len);
	glVertex3f(len, -len, len);
	glVertex3f(-len, -len, len);
	glEnd();
}

void OglCube::Draw(GLfloat len, GLuint texId) const
{
	glBindTexture(GL_TEXTURE_2D, texId); // texture를 texId로 선택(묶음)
	glBegin(GL_QUADS);
	// front facet: 전면(#0)
	glColor3f(1.f, 1.f, 1.f); // texture mapping할 영역은 흰색으로 설정
	// 텍셀 위치와 픽셀 위치를 순서대로 연결
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-len, -len, len);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(len, -len, len);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(len, len, len);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-len, len, len);
	// back facet: 후면(#2)
	glTexCoord2f(0.0f, 0.0f); glVertex3f(len, -len, -len);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-len, -len, -len);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-len, len, -len);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(len, len, -len);
	// right facet: 우면(#1)
	glTexCoord2f(0.0f, 0.0f); glVertex3f(len, -len, len);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(len, -len, -len);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(len, len, -len);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(len, len, len);
	// left facet: 좌면(#3)
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-len, -len, -len);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-len, -len, len);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-len, len, len);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-len, len, -len);
	// top facet: 상면(#4)
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-len, len, len);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(len, len, len);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(len, len, -len);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-len, len, -len);
	// bottom facet: 하면(#5)
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-len, -len, -len);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(len, -len, -len);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(len, -len, len);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-len, -len, len);
	glEnd();
}

void OglCube::Draw(const OglTransform& ot)
{
	glPushMatrix();
	glLoadIdentity();
	ot.Transform();
	SetRgba(ot.m_nColor, ot.m_alpha);
	DrawDef();
	glPopMatrix();
}

void OglCube::DrawDef(void)
{
	Draw(m_defHalfLen);
}