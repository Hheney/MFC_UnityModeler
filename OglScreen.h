#pragma once
#include <afxwin.h>
#include <GL/glew.h>

class OglScreen :
	public CStatic
{
public:
	OglScreen(void);

	COLORREF GetBackColor(void) const { return m_nBackColor; }
	GLfloat GetBackAlpha(void) const { return m_backAlpha; }
	void SetBackColor(COLORREF col) { m_nBackColor = col; }
	void SetBackAlpha(GLfloat alpha) { m_backAlpha = alpha; }
	void SetTexImage2D(const CString& imageFile);
	static void colorrefToRgb(GLfloat& r, GLfloat& g, GLfloat& b, COLORREF color);

protected:
	HDC m_hDC = NULL;      // OpenGL용 RC를 위한 DC의 핸들(handle)
	HGLRC m_hRC = NULL;    // OpenGL용 RC(rendering context)의 핸들(handle)

	COLORREF m_nBackColor;
	GLfloat m_backAlpha;

	void SetViewport(void);
	void AdjustPixelFormat(void);
	void StartRC(void);
	void StopRC(void);
	virtual void InitOpenGL(void);
	virtual void InitRender(void);
	virtual void RenderScene(void);

public:
	BOOL Create(int nId, CWnd* pParent);
	virtual BOOL Create(LPCTSTR lpszText, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID = 0xffff);

	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

