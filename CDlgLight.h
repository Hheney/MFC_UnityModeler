#pragma once
#include "afxdialogex.h"

class MyScreen;

class CDlgLight : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLight)

public:
	CDlgLight(CWnd* pParent = nullptr);
	virtual ~CDlgLight();

	void SetScreen(MyScreen* pScreen) { m_pScreen = pScreen; }

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIGHT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog() override;

	DECLARE_MESSAGE_MAP()

private:
	MyScreen* m_pScreen = nullptr;

	CMFCColorButton m_btnBackColor;
	double m_dBackAlpha = 1.0;

	CMFCColorButton m_btnAmbient;
	CMFCColorButton m_btnDiffuse;
	CMFCColorButton m_btnSpecular;

	double m_dLightX = 1.0;
	double m_dLightY = 1.0;
	double m_dLightZ = 1.0;

	double m_dShine = 100.0;

public:
	afx_msg void OnBnClickedApplyLight();
};
