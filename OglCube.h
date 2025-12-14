#pragma once
#include <GL/glew.h>

#include "OglTransform.h"

class OglCube
{
public:
	OglCube(void);

	void SetRgba(const COLORREF arColor[], const GLfloat arAlpha[]);
	void SetRgba(COLORREF col, GLfloat alpha = 1.0f);
	void SetRgbaDef(void);
	void Draw(GLfloat halfLen) const; // 정육면체의 길이 = halfLen*2
	void Draw(GLfloat halfLen, GLuint texId) const; // texture mapping; 정육면체의 길이 = halfLen*2
	void Draw(const OglTransform& ot);
	void DrawDef(void);

protected:
	COLORREF m_arColor[6];
	GLfloat m_arAlpha[6];
	const GLfloat m_defHalfLen = 20.f; // 길이 = m_defHalfLen*2
};

