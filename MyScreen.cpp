#include "pch.h"
#include "MyScreen.h"
#include "OglScreen.h"
#include <cmath>

MyScreen::MyScreen(void)
{
	SetBackColor(RGB(128, 128, 128));
	SetBackAlpha(1.0f);
}

void MyScreen::AddGameObject(const OglTransform& ot)
{
	m_arGameObj.Add(ot);
	Invalidate(FALSE);
}

void MyScreen::ClearGameObjects(void)
{
	m_arGameObj.RemoveAll();
	Invalidate(FALSE);
}

int MyScreen::GetGameObjectCount(void) const
{
	return (int)m_arGameObj.GetCount();
}

bool MyScreen::LoadObjMesh(const CString& sObjPath)
{
	m_objFile.LoadObj(sObjPath);
	m_bObjLoaded = (m_objFile.GetVtx3Ptr() != nullptr && m_objFile.GetVtx3Size() > 0);
	Invalidate(FALSE);
	return m_bObjLoaded;
}

void MyScreen::ApplyLightMaterial(
	const GLfloat ambient[4],
	const GLfloat diffuse[4],
	const GLfloat specular[4],
	const GLfloat lightPos[4],
	const GLfloat emit[4],
	GLfloat shininess)
{
	for (int i = 0; i < 4; i++)
	{
		m_lightMtl.m_lightAmbient[i] = ambient[i];
		m_lightMtl.m_lightDiffuse[i] = diffuse[i];
		m_lightMtl.m_lightSpecular[i] = specular[i];
		m_lightMtl.m_lightPos[i] = lightPos[i];
		m_lightMtl.m_mtlEmit[i] = emit[i];
	}
	m_lightMtl.m_mtlShine = shininess;

	StartRC();
	m_lightMtl.SetLightParam(false);
	StopRC();

	Invalidate(FALSE);
}

void MyScreen::ApplyBackground(COLORREF col, GLfloat alpha)
{
	if (alpha < 0.0f) alpha = 0.0f;
	if (alpha > 1.0f) alpha = 1.0f;

	SetBackColor(col);
	SetBackAlpha(alpha);
	Invalidate(FALSE);
}

void MyScreen::InitOpenGL(void)
{
	OglScreen::InitOpenGL();

	StartRC();

	// LightMtl이 RC/DC를 쓸 수 있도록 전달
	m_lightMtl.SetDCRC(m_hDC, m_hRC);
	m_lightMtl.SetLightParam(false);

	// 기본 프리미티브 준비
	m_sphere.Create();
	m_cylinder.Create();
	// cube는 Create 없이 Draw 가능하지만, 안정적으로 맞추려면 Create가 있어도 무방
	// (현재 OglCube에 Create는 없음)

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
	RenderAllGameObjects();
}

void MyScreen::RenderAllGameObjects(void)
{
	for (int i = 0; i < m_arGameObj.GetCount(); i++)
	{
		const OglTransform& elt = m_arGameObj[i];

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

		case GameObjType::QUAD:
			DrawQuad(elt);
			break;

		case GameObjType::TRI:
			DrawTri(elt);
			break;

		case GameObjType::OBJ:
			DrawObj(elt);
			break;

		default:
			break;
		}
	}
}

void MyScreen::DrawQuad(const OglTransform& ot) const
{
	GLfloat r, g, b;
	OglScreen::colorrefToRgb(r, g, b, ot.m_nColor);

	glPushMatrix();
	glLoadIdentity();
	ot.Transform();

	glColor4f(r, g, b, ot.m_alpha);

	// XY 평면에 사각형 1장 (OpenGL은 내부적으로 QUAD를 2 TRI로 처리)
	glBegin(GL_QUADS);
	glVertex3f(-50.f, -50.f, 0.f);
	glVertex3f(50.f, -50.f, 0.f);
	glVertex3f(50.f, 50.f, 0.f);
	glVertex3f(-50.f, 50.f, 0.f);
	glEnd();

	glPopMatrix();
}

void MyScreen::DrawTri(const OglTransform& ot) const
{
	GLfloat r, g, b;
	OglScreen::colorrefToRgb(r, g, b, ot.m_nColor);

	glPushMatrix();
	glLoadIdentity();
	ot.Transform();

	glColor4f(r, g, b, ot.m_alpha);

	glBegin(GL_TRIANGLES);
	glVertex3f(0.f, 60.f, 0.f);
	glVertex3f(-60.f, -60.f, 0.f);
	glVertex3f(60.f, -60.f, 0.f);
	glEnd();

	glPopMatrix();
}

void MyScreen::ComputeFaceNormal(
	const Vector3& a, const Vector3& b, const Vector3& c,
	GLfloat& nx, GLfloat& ny, GLfloat& nz)
{
	// (b-a) x (c-a)
	GLfloat ux = b.x - a.x;
	GLfloat uy = b.y - a.y;
	GLfloat uz = b.z - a.z;

	GLfloat vx = c.x - a.x;
	GLfloat vy = c.y - a.y;
	GLfloat vz = c.z - a.z;

	nx = uy * vz - uz * vy;
	ny = uz * vx - ux * vz;
	nz = ux * vy - uy * vx;

	GLfloat len = std::sqrt(nx * nx + ny * ny + nz * nz);
	if (len > 0.00001f)
	{
		nx /= len; ny /= len; nz /= len;
	}
}

void MyScreen::DrawObj(const OglTransform& ot) const
{
	if (!m_bObjLoaded) return;

	GLfloat r, g, b;
	OglScreen::colorrefToRgb(r, g, b, ot.m_nColor);

	const PVertex3 ptr = m_objFile.GetVtx3Ptr();
	const int nFace = m_objFile.GetVtx3Size();

	glPushMatrix();
	glLoadIdentity();
	ot.Transform();

	glColor4f(r, g, b, ot.m_alpha);

	// 매우 단순 렌더: face 단위로 TRIANGLES
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < nFace; i++)
	{
		const Vertex3& f = ptr[i];

		GLfloat nx, ny, nz;
		ComputeFaceNormal(f.pt1, f.pt2, f.pt3, nx, ny, nz);
		glNormal3f(nx, ny, nz);

		glVertex3f(f.pt1.x, f.pt1.y, f.pt1.z);
		glVertex3f(f.pt2.x, f.pt2.y, f.pt2.z);
		glVertex3f(f.pt3.x, f.pt3.y, f.pt3.z);
	}
	glEnd();

	glPopMatrix();
}
