// CDlgLight.cpp: 구현 파일
//

#include "pch.h"
#include "UnityModeler.h"
#include "afxdialogex.h"
#include "CDlgLight.h"


// CDlgLight 대화 상자

IMPLEMENT_DYNAMIC(CDlgLight, CDialogEx)

CDlgLight::CDlgLight(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LIGHT, pParent)
{

}

CDlgLight::~CDlgLight()
{
}

void CDlgLight::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgLight, CDialogEx)
END_MESSAGE_MAP()


// CDlgLight 메시지 처리기
