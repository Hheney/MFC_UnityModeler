#pragma once
#include "afxdialogex.h"


// CDlgGameObj 대화 상자

class MyScreen;

class CDlgGameObj : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgGameObj)

public:
	CDlgGameObj(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgGameObj();

	void SetLbGameObj(CListBox* ptr) { m_pLbGameObj = ptr; }		// 리스트 박스 포인터 설정(inline 함수)
	void SetScreen(MyScreen* pScreen) { m_pScreen = pScreen; }		// 스크린 포인터 설정(inline 함수)

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAMEOBJ };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

private:
	CListBox* m_pLbGameObj;
	MyScreen* m_pScreen;

public:
	CString m_sGameObjName;
	afx_msg void OnBnClickedButton1();
};
