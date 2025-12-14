// CDlgGameObj.cpp: 구현 파일
//

#include "pch.h"
#include "UnityModeler.h"
#include "afxdialogex.h"
#include "CDlgGameObj.h"


// CDlgGameObj 대화 상자

IMPLEMENT_DYNAMIC(CDlgGameObj, CDialogEx)

CDlgGameObj::CDlgGameObj(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAMEOBJ, pParent)
	, m_sGameObjName(_T(""))
{
	m_pLbGameObj = nullptr;
}

CDlgGameObj::~CDlgGameObj()
{
}

void CDlgGameObj::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_sGameObjName);
}


BEGIN_MESSAGE_MAP(CDlgGameObj, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgGameObj::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDlgGameObj 메시지 처리기

// add game object
void CDlgGameObj::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_pLbGameObj->AddString(m_sGameObjName);
}
