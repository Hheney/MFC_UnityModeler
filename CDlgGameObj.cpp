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
	, m_dTx(0.0), m_dTy(0.0), m_dTz(0.0)
	, m_dRx(0.0), m_dRy(0.0), m_dRz(0.0)
	, m_dSx(1.0), m_dSy(1.0), m_dSz(1.0)
	, m_dAlpha(1.0)
	, m_nSelectedObjTypeIndex(0)
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

	// 게임 오브젝트 이름
	DDX_Text(pDX, IDC_EDIT1, m_sGameObjName);

	DDX_Control(pDX, IDC_LIST_OBJ_TYPE, m_lbObjType);	// 오브젝트 타입 리스트 박스
	DDX_Control(pDX, IDC_OBJ_COLORBTN, m_btnColor);		// 색상 선택 버튼

	DDX_Text(pDX, IDC_EDIT_OBJ_ALPHA, m_dAlpha); // Alpha

	// Transform 값
	DDX_Text(pDX, IDC_EDIT_T_X, m_dTx);
	DDX_Text(pDX, IDC_EDIT_T_Y, m_dTy);
	DDX_Text(pDX, IDC_EDIT_T_Z, m_dTz);

	// Rotation 값
	DDX_Text(pDX, IDC_EDIT_R_X, m_dRx);
	DDX_Text(pDX, IDC_EDIT_R_Y, m_dRy);
	DDX_Text(pDX, IDC_EDIT_R_Z, m_dRz);

	// Scale 값
	DDX_Text(pDX, IDC_EDIT_S_X, m_dSx);
	DDX_Text(pDX, IDC_EDIT_S_Y, m_dSy);
	DDX_Text(pDX, IDC_EDIT_S_Z, m_dSz);
}

BOOL CDlgGameObj::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 오브젝트 타입 리스트 박스 초기화
	m_lbObjType.ResetContent();
	m_lbObjType.AddString(_T("Sphere"));
	m_lbObjType.AddString(_T("Cube"));
	m_lbObjType.AddString(_T("Cylinder"));
	m_lbObjType.SetCurSel(0);
	m_nSelectedObjTypeIndex = 0;

	// 기본 색상 설정
	m_btnColor.SetColor(RGB(255, 255, 255)); // 흰색

	// 선택 타입에 맞는 프리셋 적용
	ApplyPresetByTypeIndex(m_nSelectedObjTypeIndex);
	UpdateData(FALSE);

	return TRUE;
}


BEGIN_MESSAGE_MAP(CDlgGameObj, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgGameObj::OnBnClickedButton1)
	ON_LBN_SELCHANGE(IDC_LIST_OBJ_TYPE, &CDlgGameObj::OnLbnSelchangeListObjType)
END_MESSAGE_MAP()


// CDlgGameObj 메시지 처리기

void CDlgGameObj::ApplyPresetByTypeIndex(int nIndex)
{
	// 공통 기본값
	m_dTx = 0.0; m_dTy = 0.0; m_dTz = 0.0;
	m_dRx = 0.0; m_dRy = 0.0; m_dRz = 0.0;
	m_dAlpha = 1.0;

	// 타입별 프리셋
	switch (nIndex)
	{
	case 0: // Sphere
		m_dSx = 1.0; m_dSy = 1.0; m_dSz = 1.0;
		m_btnColor.SetColor(RGB(255, 0, 0));	// 빨강
		break;

	case 1: // Cube
		m_dSx = 1.0; m_dSy = 1.0; m_dSz = 1.0;
		m_btnColor.SetColor(RGB(0, 255, 0));	// 초록
		break;

	case 2: // Cylinder
		m_dSx = 1.0; m_dSy = 1.0; m_dSz = 1.0;
		m_btnColor.SetColor(RGB(0, 128, 255));	// 파랑

		// 원기둥은 기본 축 방향 때문에 화면에서 안보일 수 있어 기본 회전값 추가(BackFace Culling 영향)
		m_dRx = 45.0;
		m_dRy = 0.0;
		m_dRz = 0.0;
		break;

	default:
		m_dSx = 1.0; m_dSy = 1.0; m_dSz = 1.0;
		m_btnColor.SetColor(RGB(255, 255, 255));
		break;
	}

}

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
		// Alpha 값 범위 제한
		if (m_dAlpha < 0.0) m_dAlpha = 0.0;
		if (m_dAlpha > 1.0) m_dAlpha = 1.0;

		OglTransform ot;
		ot.SetDef();

		// 오브젝트 선택된 타입에 따른 설정
		switch (m_nSelectedObjTypeIndex)
		{
		case 0: ot.m_nType = GameObjType::SPHERE; break;		// Sphere
		case 1: ot.m_nType = GameObjType::CUBE; break;			// Cube
		case 2: ot.m_nType = GameObjType::CYLINDER; break;		// Cylinder
		default: ot.m_nType = GameObjType::SPHERE; break;		// 선택 안된 경우 기본 Sphere 타입
		}

		// 색상/알파: Inspector 값
		ot.m_nColor = m_btnColor.GetColor();
		ot.m_alpha = (GLfloat)m_dAlpha;

		// Transform: Inspector 값
		ot.m_translate = Vector3((GLfloat)m_dTx, (GLfloat)m_dTy, (GLfloat)m_dTz);
		ot.m_rotate = Vector3((GLfloat)m_dRx, (GLfloat)m_dRy, (GLfloat)m_dRz);
		ot.m_scale = Vector3((GLfloat)m_dSx, (GLfloat)m_dSy, (GLfloat)m_dSz);

		m_pScreen->AddGameObject(ot);

		TRACE(_T("[Add] m_nObjType=%d\n"), m_nSelectedObjTypeIndex);
	}
}

void CDlgGameObj::OnLbnSelchangeListObjType()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nSelect = m_lbObjType.GetCurSel();
	if (nSelect < 0) return;

	m_nSelectedObjTypeIndex = nSelect;

	// 선택된 타입에 맞는 프리셋을 Inspector에 반영
	ApplyPresetByTypeIndex(m_nSelectedObjTypeIndex);
	UpdateData(FALSE);
}
