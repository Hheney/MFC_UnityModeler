
// UnityModelerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "UnityModeler.h"
#include "UnityModelerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CUnityModelerDlg 대화 상자



CUnityModelerDlg::CUnityModelerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UNITYMODELER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// dialog pointer 초기화
	m_pDlgGameObj = nullptr;
	m_pDlgLight = nullptr;
}

CUnityModelerDlg::~CUnityModelerDlg()
{
	// dialog pointer의 메모리 해제
	if (m_pDlgGameObj) delete m_pDlgGameObj;
	if (m_pDlgLight) delete m_pDlgLight;
}

void CUnityModelerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tabCtrl);
	DDX_Control(pDX, IDC_LIST1, m_lbGameObj);
}

BEGIN_MESSAGE_MAP(CUnityModelerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CUnityModelerDlg::OnBnClickedButton1)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CUnityModelerDlg::OnSelchangeTab1)
END_MESSAGE_MAP()


// CUnityModelerDlg 메시지 처리기

void CUnityModelerDlg::SetTabCtrl(void)
{
	m_tabCtrl.InsertItem(0, _T("Game Object"));
	m_tabCtrl.InsertItem(1, _T("Light"));
	m_tabCtrl.SetCurSel(0); // 0번 탭을 현재 선택으로 설정

	// 탭별로 dialog 생성
	CRect rect;
	m_tabCtrl.GetClientRect(&rect); // tab control의 사각형 영역 얻기
	// 0번 탭
	m_pDlgGameObj = new CDlgGameObj;
	m_pDlgGameObj->Create(IDD_GAMEOBJ, &m_tabCtrl); // m_pDlgGameObj의 부모를 m_tabCtrl로 선택
	m_pDlgGameObj->MoveWindow(0, 20, rect.Width(), rect.Height());
	m_pDlgGameObj->ShowWindow(SW_SHOW);
	m_pDlgGameObj->SetLbGameObj(&m_lbGameObj); // m_lbGameObj인 CListBox의 포인터를 CDlgGameObj에 전달
	// 1번 탭
	m_pDlgLight = new CDlgLight;
	m_pDlgLight->Create(IDD_LIGHT, &m_tabCtrl); // m_pDlgGameObj의 부모를 m_tabCtrl로 선택
	m_pDlgLight->MoveWindow(0, 20, rect.Width(), rect.Height());
	m_pDlgLight->ShowWindow(SW_HIDE);
}

BOOL CUnityModelerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_screen.Create(IDC_SCREEN, this);
	SetTabCtrl();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CUnityModelerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CUnityModelerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CUnityModelerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CUnityModelerDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_screen.Invalidate(FALSE);
}

// noti(통지): 메시지의 일정; 자식 -> 부모에게 전달하는 메시지
// TCN: tab control noti
// NMHDR: noti message header
// IDC_TAB_OPT > TCN_SELCHANGE
void CUnityModelerDlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (pNMHDR->idFrom == IDC_TAB_OPT) // IDC_TAB_OPT ID를 가진 자식에게서(idFrom) 오는 통지 메시지(NM)
	{
		int nSel = m_tabCtrl.GetCurSel();
		switch (nSel)
		{
		case 0: // game object tab
			m_pDlgGameObj->ShowWindow(SW_SHOW);
			m_pDlgLight->ShowWindow(SW_HIDE);
			break;
		case 1: // light tab
			m_pDlgGameObj->ShowWindow(SW_HIDE);
			m_pDlgLight->ShowWindow(SW_SHOW);
			break;
		}
	}
	*pResult = 0;
}
