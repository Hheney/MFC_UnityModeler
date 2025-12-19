#include "pch.h"
#include "UnityModeler.h"
#include "afxdialogex.h"
#include "CDlgLight.h"

#include "MyScreen.h"
#include "OglScreen.h"

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

	DDX_Control(pDX, IDC_BACK_COLORBTN, m_btnBackColor);
	DDX_Text(pDX, IDC_BACK_ALPHA, m_dBackAlpha);

	DDX_Control(pDX, IDC_LIGHT_AMBIENT_BTN, m_btnAmbient);
	DDX_Control(pDX, IDC_LIGHT_DIFFUSE_BTN, m_btnDiffuse);
	DDX_Control(pDX, IDC_LIGHT_SPECULAR_BTN, m_btnSpecular);

	DDX_Text(pDX, IDC_LIGHT_POS_X, m_dLightX);
	DDX_Text(pDX, IDC_LIGHT_POS_Y, m_dLightY);
	DDX_Text(pDX, IDC_LIGHT_POS_Z, m_dLightZ);

	DDX_Text(pDX, IDC_MTL_SHINE, m_dShine);
}

BOOL CDlgLight::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 기본값
	m_btnBackColor.SetColor(RGB(127, 127, 127));
	m_dBackAlpha = 1.0;

	m_btnAmbient.SetColor(RGB(51, 51, 51));    // 0.2 정도
	m_btnDiffuse.SetColor(RGB(128, 128, 128)); // 0.5 정도
	m_btnSpecular.SetColor(RGB(230, 230, 230));// 0.9 정도

	m_dLightX = 1.0;
	m_dLightY = 1.0;
	m_dLightZ = 1.0;
	m_dShine = 100.0;

	UpdateData(FALSE);
	return TRUE;
}

BEGIN_MESSAGE_MAP(CDlgLight, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_APPLY_LIGHT, &CDlgLight::OnBnClickedApplyLight)
END_MESSAGE_MAP()

void CDlgLight::OnBnClickedApplyLight()
{
	UpdateData(TRUE);
	if (!m_pScreen) return;

	// 배경 RGBA 적용 (0)
	GLfloat backA = (GLfloat)m_dBackAlpha;
	if (backA < 0.f) backA = 0.f;
	if (backA > 1.f) backA = 1.f;
	m_pScreen->ApplyBackground(m_btnBackColor.GetColor(), backA);

	// Light/Material 적용 (3)
	auto ColorToRGBA = [](COLORREF c, GLfloat out[4])
		{
			out[0] = GetRValue(c) / 255.f;
			out[1] = GetGValue(c) / 255.f;
			out[2] = GetBValue(c) / 255.f;
			out[3] = 1.f;
		};

	GLfloat amb[4], dif[4], spe[4], pos[4], emi[4];
	ColorToRGBA(m_btnAmbient.GetColor(), amb);
	ColorToRGBA(m_btnDiffuse.GetColor(), dif);
	ColorToRGBA(m_btnSpecular.GetColor(), spe);

	pos[0] = (GLfloat)m_dLightX;
	pos[1] = (GLfloat)m_dLightY;
	pos[2] = (GLfloat)m_dLightZ;
	pos[3] = 0.0f; // directional

	// emission은 0 고정(최소 구현)
	emi[0] = emi[1] = emi[2] = 0.f;
	emi[3] = 1.f;

	GLfloat shine = (GLfloat)m_dShine;

	m_pScreen->ApplyLightMaterial(amb, dif, spe, pos, emi, shine);
}
