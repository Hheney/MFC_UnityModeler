
// UnityModelerDlg.h: 헤더 파일
//

#pragma once

#include "MyScreen.h"
#include "CDlgGameObj.h"
#include "CDlgLight.h"

// CUnityModelerDlg 대화 상자
class CUnityModelerDlg : public CDialogEx
{
	// 생성입니다.
public:
	CUnityModelerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	~CUnityModelerDlg(); // 파괴자, 소멸자

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITYMODELER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


	// 구현입니다.
protected:
	HICON m_hIcon;
	MyScreen m_screen;
	CDlgGameObj* m_pDlgGameObj;
	CDlgLight* m_pDlgLight;

	void SetTabCtrl(void);

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CTabCtrl m_tabCtrl;
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	CListBox m_lbGameObj;
};
