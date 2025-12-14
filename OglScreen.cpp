#include "pch.h"
#include "OglScreen.h"
#include <GL/GLU.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

OglScreen::OglScreen(void)
{
	m_nBackColor = RGB(127, 127, 127);
	m_backAlpha = 1.0f;
}

void OglScreen::SetTexImage2D(const CString& imageFile)
{
	// 비트맵 읽기 -> 텍셀로 사용
	int wid, ht, chan; // bmp, jpg -> 3(RGB); png, gif -> 4(RGBA)
	// CStringA: ASCII를 위한 CString
	unsigned char* data = stbi_load(CStringA(imageFile), &wid, &ht, &chan, 0); // 비트맵 형태의 메모리 할당; ./res/logo.jpg 의미: 현재 폴더(.) 아래에 있는 폴더 res에 있는 logo.jpg
	if (chan == 3) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, wid, ht, 0, GL_RGB, GL_UNSIGNED_BYTE, data); // bmp, jpg
	else if (chan == 4) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, wid, ht, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); // png, gif
	stbi_image_free(data); // 메모리 해제
}

void OglScreen::colorrefToRgb(GLfloat& r, GLfloat& g, GLfloat& b, COLORREF color)
{
	// OpenGL 색깔 범위: 0~1, COLORREF 색깔 범위: 0~255
	r = GetRValue(color) / GLfloat(255);
	g = GetGValue(color) / GLfloat(255);
	b = GetBValue(color) / GLfloat(255);
}

void OglScreen::SetViewport(void)
{
	// viewport 설정
	CRect rect;
	GetClientRect(rect);
	int range = __min(rect.Width(), rect.Height());
	int diff = abs(rect.Width() - rect.Height());
	if (rect.Width() >= rect.Height()) glViewport(diff / 2, 0, range, range); // 가로가 긴 경우
	else glViewport(0, diff / 2, range, range); // 세로가 긴 경우

	// 투영 행렬
	GLdouble ranHalf = range / 2.;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// ranHalf - (-ranHalf) = range
	glOrtho(-ranHalf, ranHalf, -ranHalf, ranHalf, -ranHalf, ranHalf);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void OglScreen::AdjustPixelFormat(void)
{
	// 구조체 초기화
	PIXELFORMATDESCRIPTOR PFD = {
sizeof(PIXELFORMATDESCRIPTOR), // size of PFD 
1,                              // version number 
PFD_DRAW_TO_WINDOW |      // support window 
PFD_SUPPORT_OPENGL |         // support OpenGL 
PFD_DOUBLEBUFFER,              // double buffered 
PFD_TYPE_RGBA,           // RGBA type 
32,                             // 32-bit color depth 
0, 0, 0, 0, 0, 0,               // color bits ignored 
0,                               // no alpha buffer 
0,                               // shift bit ignored 
0,                               // no accumulation buffer 
0, 0, 0, 0,                     // accum bits ignored 
32,                             // 32-bit z-buffer     
0,                               // no stencil buffer 
0,                               // no auxiliary buffer 
PFD_MAIN_PLANE,         // Main layer 
0,                               // reserved 
0, 0, 0                         // layer masks ignored 
	};
	int nFormat = ::ChoosePixelFormat(m_hDC, &PFD);
	::SetPixelFormat(m_hDC, nFormat, &PFD);
}

void OglScreen::StartRC(void)
{
	::wglMakeCurrent(m_hDC, m_hRC);
}

void OglScreen::StopRC(void)
{
	::wglMakeCurrent(m_hDC, NULL);
}

void OglScreen::InitOpenGL(void)
{
	StartRC();

	// OpenGL 코드
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE); // 특정 면(face)을 도태시키기(cull)를 가능하게(enable)
	glFrontFace(GL_CCW); // 정면(front face)의 법선 벡터를 반시계(CCW) 방향으로 설정
	glCullFace(GL_BACK); // 뒷면(back face)를 도태시키기(cull)
	glEnable(GL_NORMALIZE); // scale 연산을 할 때 법선 벡터 방향이 바뀌지 않도록 정규화

	StopRC();
}

void OglScreen::InitRender(void)
{
	GLfloat r, g, b;

	// 초기 설정 + 배경색 설정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1.0f); // 물체는 카메라에서 가장 멀리(1.0f) 있다고 초기화(clear)
	OglScreen::colorrefToRgb(r, g, b, m_nBackColor);
	glClearColor(r, g, b, m_backAlpha);
}

void OglScreen::RenderScene(void)
{
}

BOOL OglScreen::Create(int nId, CWnd* pParent)
{
	CWnd* pWnd = pParent->GetDlgItem(nId);
	pWnd->ShowWindow(SW_HIDE);
	CRect rect;
	pWnd->GetWindowRect(rect); // 스크린(문서) 좌표계를 기준으로 현재 pWnd의 사각형 영역 얻기
	pParent->ScreenToClient(rect); // 스크린 좌표계 -> dialog의 client 좌표계로 변환
	return Create(NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, rect, pParent); // 스크린 생성
}

BOOL OglScreen::Create(LPCTSTR lpszText, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	BOOL bResult = CStatic::Create(lpszText, dwStyle, rect, pParentWnd, nID);
	return bResult;
}

BEGIN_MESSAGE_MAP(OglScreen, CStatic)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

int OglScreen::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	//m_hDC = ::GetDC(m_hWnd); // m_hWnd: 현재 window의 핸들
	m_hDC = ::GetDC(GetSafeHwnd()); // 안전한 window 핸들 얻기
	AdjustPixelFormat();
	m_hRC = ::wglCreateContext(m_hDC);
	InitOpenGL();

	return 0;
}

void OglScreen::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CStatic::OnPaint()을(를) 호출하지 마십시오.
	StartRC();

	// OpenGL 코드
	InitRender();
	RenderScene();

	::SwapBuffers(m_hDC); // double buffer 때문에 필요
	StopRC();
}

void OglScreen::OnDestroy()
{
	CStatic::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	StopRC();
	::wglDeleteContext(m_hRC);
	::ReleaseDC(GetSafeHwnd(), m_hDC);
}

// OpenGL이 배경 처리하기 때문에 필요없는 메시지 핸들러
BOOL OglScreen::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return TRUE;
	//return CStatic::OnEraseBkgnd(pDC);
}
