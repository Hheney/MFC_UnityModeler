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
	virtual BOOL OnInitDialog() override;				// 초기화 함수 재정의

	DECLARE_MESSAGE_MAP()

private:
	CListBox* m_pLbGameObj;
	MyScreen* m_pScreen;

	// 오브젝트 타입 선택 리스트
	CListBox m_lbObjType;

	// UI 컨트롤 변수
	CMFCColorButton m_btnColor;

	// 현재 선택된 타입
	int m_nSelectedObjTypeIndex;

	void ApplyPresetByTypeIndex(int nIndex);	// 선택된 타입 인덱스에 따른 프리셋 적용 함수

public:
	// 게임 오브젝트 이름 변수
	CString m_sGameObjName;

	// Transform, Alpha 값 변수
	double m_dTx, m_dTy, m_dTz;	// Translation
	double m_dRx, m_dRy, m_dRz;	// Rotation
	double m_dSx, m_dSy, m_dSz;	// Scale
	double m_dAlpha;			// Alpha

	afx_msg void OnBnClickedButton1(); // Add Game Object 버튼 클릭 핸들러
	afx_msg void OnLbnSelchangeListObjType();
};
