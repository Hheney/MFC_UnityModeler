#pragma once

#include "OglScreen.h"
#include "OglLightMtl.h"
#include "OglSphere.h"
#include "OglCube.h"
#include "OglCylinder.h"
#include "OglTransform.h"
#include "ObjFile.h"

class MyScreen : public OglScreen
{
public:
	MyScreen(void);

	// Scene 데이터 조작 API (Dialog/UI에서 호출)
	void AddGameObject(const OglTransform& ot);
	void ClearGameObjects(void);

	// OBJ 로드(단일 로드 후, OBJ 타입 오브젝트들이 같은 메시를 사용)
	bool LoadObjMesh(const CString& sObjPath);

	// Light/Material 적용 (Dialog에서 호출)
	void ApplyLightMaterial(
		const GLfloat ambient[4],
		const GLfloat diffuse[4],
		const GLfloat specular[4],
		const GLfloat lightPos[4],
		const GLfloat emit[4],
		GLfloat shininess);

	// 배경 RGBA 적용 (Dialog에서 호출)
	void ApplyBackground(COLORREF col, GLfloat alpha);

	// Getter
	int GetGameObjectCount(void) const;

protected:
	OglLightMtl m_lightMtl;
	OglSphere   m_sphere;
	OglCube     m_cube;
	OglCylinder m_cylinder;

	// OBJ
	ObjFile m_objFile;
	bool    m_bObjLoaded = false;

	CArray<OglTransform, const OglTransform&> m_arGameObj;

	virtual void InitOpenGL(void);
	virtual void InitRender(void);
	virtual void RenderScene(void);

private:
	void RenderAllGameObjects(void);

	// 신규: Quad/Tri/Obj Draw
	void DrawQuad(const OglTransform& ot) const;
	void DrawTri(const OglTransform& ot) const;
	void DrawObj(const OglTransform& ot) const;

	static void ComputeFaceNormal(
		const Vector3& a, const Vector3& b, const Vector3& c,
		GLfloat& nx, GLfloat& ny, GLfloat& nz);
};
