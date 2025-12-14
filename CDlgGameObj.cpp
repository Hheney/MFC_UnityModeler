// CDlgGameObj.cpp: 구현 파일
//

#include "pch.h"
#include "UnityModeler.h"
#include "afxdialogex.h"
#include "CDlgGameObj.h"

#include "MyScreen.h"
#include "OglTransform.h"

// CDlgGameObj 대화 상자

IMPLEMENT_DYNAMIC(CDlgGameObj, CDialogEx)

CDlgGameObj::CDlgGameObj(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAMEOBJ, pParent)
	, m_sGameObjName(_T(""))
{
	m_pLbGameObj = nullptr;
	m_pScreen = nullptr;
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

	// Scene(ListBox)에 이름 추가
	if (m_pLbGameObj)
	{
		m_pLbGameObj->AddString(m_sGameObjName);
	}

	// Screen에 실제 GameObject 추가
	if (m_pScreen)
	{
		OglTransform ot;
		ot.SetDef();

		// 기본값으로 “잘 보이는 세팅”
		ot.m_nType = GameObjType::SPHERE;
		ot.m_nColor = RGB(255, 0, 0);
		ot.m_alpha = 1.0f;

		// 계속 눌러도 겹치지 않게 X 위치를 조금씩 이동
		const int nCount = m_pScreen->GetGameObjectCount();
		ot.m_translate = Vector3(-200.0f + 40.0f * (GLfloat)(nCount % 12), 0.0f, 0.0f);
		ot.m_scale = Vector3(1.0f, 1.0f, 1.0f);

		m_pScreen->AddGameObject(ot); // 내부에서 Invalidate(FALSE) 수행
	}
}
