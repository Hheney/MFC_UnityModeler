#include "pch.h"
#include "UnityModeler.h"
#include "afxdialogex.h"
#include "CDlgGameObj.h"

#include "MyScreen.h"
#include "OglTransform.h"

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

	DDX_Text(pDX, IDC_EDIT1, m_sGameObjName);

	DDX_Control(pDX, IDC_LIST_OBJ_TYPE, m_lbObjType);
	DDX_Control(pDX, IDC_OBJ_COLORBTN, m_btnColor);

	DDX_Text(pDX, IDC_EDIT_OBJ_ALPHA, m_dAlpha);

	DDX_Text(pDX, IDC_EDIT_T_X, m_dTx);
	DDX_Text(pDX, IDC_EDIT_T_Y, m_dTy);
	DDX_Text(pDX, IDC_EDIT_T_Z, m_dTz);

	DDX_Text(pDX, IDC_EDIT_R_X, m_dRx);
	DDX_Text(pDX, IDC_EDIT_R_Y, m_dRy);
	DDX_Text(pDX, IDC_EDIT_R_Z, m_dRz);

	DDX_Text(pDX, IDC_EDIT_S_X, m_dSx);
	DDX_Text(pDX, IDC_EDIT_S_Y, m_dSy);
	DDX_Text(pDX, IDC_EDIT_S_Z, m_dSz);
}

BOOL CDlgGameObj::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_lbObjType.ResetContent();
	m_lbObjType.AddString(_T("Sphere"));   // 0
	m_lbObjType.AddString(_T("Cube"));     // 1
	m_lbObjType.AddString(_T("Cylinder")); // 2
	m_lbObjType.AddString(_T("Quad"));     // 3
	m_lbObjType.AddString(_T("Tri"));      // 4
	m_lbObjType.AddString(_T("OBJ"));      // 5
	m_lbObjType.SetCurSel(0);

	m_nSelectedObjTypeIndex = 0;

	m_btnColor.SetColor(RGB(255, 255, 255));

	ApplyPresetByTypeIndex(m_nSelectedObjTypeIndex);
	UpdateData(FALSE);

	return TRUE;
}

BEGIN_MESSAGE_MAP(CDlgGameObj, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgGameObj::OnBnClickedButton1)
	ON_LBN_SELCHANGE(IDC_LIST_OBJ_TYPE, &CDlgGameObj::OnLbnSelchangeListObjType)
END_MESSAGE_MAP()

void CDlgGameObj::ApplyPresetByTypeIndex(int nIndex)
{
	m_dTx = 0.0; m_dTy = 0.0; m_dTz = 0.0;
	m_dRx = 0.0; m_dRy = 0.0; m_dRz = 0.0;
	m_dAlpha = 1.0;

	switch (nIndex)
	{
	case 0: // Sphere
		m_dSx = 1.0; m_dSy = 1.0; m_dSz = 1.0;
		m_btnColor.SetColor(RGB(255, 0, 0));
		break;

	case 1: // Cube
		m_dSx = 1.0; m_dSy = 1.0; m_dSz = 1.0;
		m_btnColor.SetColor(RGB(0, 255, 0));
		break;

	case 2: // Cylinder
		m_dSx = 1.0; m_dSy = 1.0; m_dSz = 1.0;
		m_btnColor.SetColor(RGB(0, 128, 255));
		m_dRx = 45.0; // 가시성 프리셋
		break;

	case 3: // Quad
		m_dSx = 1.0; m_dSy = 1.0; m_dSz = 1.0;
		m_btnColor.SetColor(RGB(255, 255, 0));
		break;

	case 4: // Tri
		m_dSx = 1.0; m_dSy = 1.0; m_dSz = 1.0;
		m_btnColor.SetColor(RGB(255, 0, 255));
		break;

	case 5: // OBJ
		m_dSx = 1.0; m_dSy = 1.0; m_dSz = 1.0;
		m_btnColor.SetColor(RGB(255, 255, 255));
		break;

	default:
		m_dSx = 1.0; m_dSy = 1.0; m_dSz = 1.0;
		m_btnColor.SetColor(RGB(255, 255, 255));
		break;
	}
}

void CDlgGameObj::OnBnClickedButton1()
{
	UpdateData(TRUE);

	if (m_pLbGameObj)
	{
		m_pLbGameObj->AddString(m_sGameObjName);
	}

	if (!m_pScreen) return;

	// Alpha clamp
	if (m_dAlpha < 0.0) m_dAlpha = 0.0;
	if (m_dAlpha > 1.0) m_dAlpha = 1.0;

	OglTransform ot;
	ot.SetDef();

	// 타입 매핑
	switch (m_nSelectedObjTypeIndex)
	{
	case 0: ot.m_nType = GameObjType::SPHERE; break;
	case 1: ot.m_nType = GameObjType::CUBE; break;
	case 2: ot.m_nType = GameObjType::CYLINDER; break;
	case 3: ot.m_nType = GameObjType::QUAD; break;
	case 4: ot.m_nType = GameObjType::TRI; break;
	case 5: ot.m_nType = GameObjType::OBJ; break;
	default: ot.m_nType = GameObjType::SPHERE; break;
	}

	// OBJ 선택이면: 파일 선택 후 메시 로드
	if (ot.m_nType == GameObjType::OBJ)
	{
		CFileDialog dlg(TRUE, _T("obj"), NULL,
			OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
			_T("OBJ Files (*.obj)|*.obj||"));

		if (dlg.DoModal() == IDOK)
		{
			m_pScreen->LoadObjMesh(dlg.GetPathName());
		}
	}

	ot.m_nColor = m_btnColor.GetColor();
	ot.m_alpha = (GLfloat)m_dAlpha;

	ot.m_translate = Vector3((GLfloat)m_dTx, (GLfloat)m_dTy, (GLfloat)m_dTz);
	ot.m_rotate = Vector3((GLfloat)m_dRx, (GLfloat)m_dRy, (GLfloat)m_dRz);
	ot.m_scale = Vector3((GLfloat)m_dSx, (GLfloat)m_dSy, (GLfloat)m_dSz);

	m_pScreen->AddGameObject(ot);
}

void CDlgGameObj::OnLbnSelchangeListObjType()
{
	int nSelect = m_lbObjType.GetCurSel();
	if (nSelect < 0) return;

	m_nSelectedObjTypeIndex = nSelect;
	ApplyPresetByTypeIndex(m_nSelectedObjTypeIndex);
	UpdateData(FALSE);
}
