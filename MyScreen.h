#pragma once

#include "OglScreen.h"
#include "OglLightMtl.h"
#include "OglSphere.h"
#include "OglCube.h"
#include "OglCylinder.h"
#include "OglTransform.h"

class MyScreen :
	public OglScreen
{
public:
	MyScreen(void);

	// Scene 데이터 조작 API (Dialog/UI에서 호출)
	void AddGameObject(const OglTransform& ot);
	void ClearGameObjects(void);

	// Getter
	int GetGameObjectCount(void) const; // 게임 객체 변환 정보 배열의 원소 개수 반환

protected:
	OglLightMtl m_lightMtl;		// 조명 및 재질 정보
	OglSphere m_sphere;			// 구체 객체
	OglCube	m_cube;				// 정육면체 객체
	OglCylinder m_cylinder;		// 원기둥 객체

	CArray<OglTransform, const OglTransform&> m_arGameObj; // 게임 객체 변환 정보 배열

	void SampleMultiGameObj(void);

	virtual void InitOpenGL(void);
	virtual void InitRender(void);
	virtual void RenderScene(void);

private:
	void RenderAllGameObjects(void);	// 배열의 모든 게임 객체를 렌더링

};

