#pragma once
#include "afxdialogex.h"


// CDlgLight 대화 상자

class CDlgLight : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLight)

public:
	CDlgLight(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgLight();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIGHT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
