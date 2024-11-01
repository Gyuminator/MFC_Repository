
// MFC_ProblemDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MFC_Problem.h"
#include "MFC_ProblemDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
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


// CMFC_ProblemDlg 대화 상자



CMFC_ProblemDlg::CMFC_ProblemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_PROBLEM_DIALOG, pParent)
	, m_Image()
	, m_ImageDirPath()
	, m_nStartX(0)
	, m_nStartY(0)
	, m_nEndX(0)
	, m_nEndY(0)
	, m_nFrams(10)
	, m_nMsPerFrame(500)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	LPWSTR pBuffer = m_ImageDirPath.GetBuffer(PATH_LENG);
	GetCurrentDirectory(PATH_LENG, pBuffer);
	m_ImageDirPath.ReleaseBuffer();
	m_ImageDirPath += _T("\\img\\");
}

void CMFC_ProblemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_START_X, m_nStartX);
	DDX_Text(pDX, IDC_EDIT_START_Y, m_nStartY);
	DDX_Text(pDX, IDC_EDIT_END_X, m_nEndX);
	DDX_Text(pDX, IDC_EDIT_END_Y, m_nEndY);
	DDX_Text(pDX, IDC_EDIT_FRAMES, m_nFrams);
	DDX_Text(pDX, IDC_EDIT_MSPF, m_nMsPerFrame);
}

BEGIN_MESSAGE_MAP(CMFC_ProblemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_DRAW, &CMFC_ProblemDlg::OnBnClickedBtnDraw)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CMFC_ProblemDlg::OnBnClickedBtnAction)
END_MESSAGE_MAP()


// CMFC_ProblemDlg 메시지 처리기

BOOL CMFC_ProblemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFC_ProblemDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFC_ProblemDlg::OnPaint()
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
HCURSOR CMFC_ProblemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFC_ProblemDlg::_CreateImage(UINT8 nGrayOfBG)
{
	int nWidth = 640;
	int nHeight = 480;
	int nBpp = 8;
	constexpr int RGBSIZE = 256;

	m_Image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8)
	{
		static RGBQUAD rgb[RGBSIZE];
		for (int i = 0; i < RGBSIZE; ++i)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_Image.SetColorTable(0, 256, rgb);
	}
	memset(m_Image.GetBits(), nGrayOfBG, m_Image.GetWidth() * m_Image.GetHeight());
}

void CMFC_ProblemDlg::_DrawImage()
{
	if (m_Image.IsNull())
		_CreateImage();

	CClientDC dc(this);
	m_Image.Draw(dc, 0, 0);
}

void CMFC_ProblemDlg::_DrawCircle(int nCenterX, int nCenterY, int nRadius, UINT8 nGray, bool bIsDraw)
{
	//CRect rect(nCenterX - nRadius, nCenterY - nRadius, nCenterX + nRadius, nCenterY + nRadius);
	int nDiameter = nRadius * 2;
	CRect rect = _MakeRectbyCenter({ nCenterX, nCenterY }, { nDiameter, nDiameter });

	for (int y = rect.top; y < rect.bottom; ++y)
	{
		for (int x = rect.left; x < rect.right; ++x)
		{
			if (_IsInCircle(x - nCenterX, y - nCenterY, nRadius))
				_SetPixel(x, y, nGray);
		}
	}

	if (bIsDraw)
	{
		_DrawImage();
	}
}

void CMFC_ProblemDlg::_DrawRect(CRect rect, UINT8 nGray, bool bIsDraw)
{
	for (int y = rect.top; y < rect.bottom; ++y)
	{
		for (int x = rect.left; x < rect.right; ++x)
		{
			_SetPixel(x, y, nGray);
		}
	}

	if (bIsDraw)
	{
		_DrawImage();
	}
}

void CMFC_ProblemDlg::_MoveCircle(int nRadius, POINT startPos, POINT endPos)
{
	// m_nFrams = GetDlgItemInt(IDC_EDIT_FRAMES);
	float fAlpha = 0.f;
	float fPrevAlpha = 0.f;
	float fEndAlpha = 1.f;
	m_nFrams = (m_nFrams < 2) ? 2 : m_nFrams;
	float fDeltaAlpha = fEndAlpha / (m_nFrams - 1);

	int nDiameter = nRadius * 2;
	int nGrayOfBG = 0xff;
	int nX = _LerpInt(startPos.x, endPos.x, fAlpha);
	int nY = _LerpInt(startPos.y, endPos.y, fAlpha);
	bool bKeep = true;

	_DrawCircle(m_nStartX, m_nStartY, m_nRadius);
	// 캡쳐
	Sleep(m_nMsPerFrame);

	while (bKeep)
	{
		// 이전 원 클리어
		_DrawRect(_MakeRectbyCenter({ nX,nY }, { nDiameter, nDiameter }), nGrayOfBG, false); // bIsDraw = false: _DrawCircle에서 한번에 합니다.

		fAlpha += fDeltaAlpha;
		if (fAlpha >= fEndAlpha)
		{
			fAlpha = fEndAlpha;
			bKeep = false;
		}
		nX = _LerpInt(startPos.x, endPos.x, fAlpha);
		nY = _LerpInt(startPos.y, endPos.y, fAlpha);

		_DrawCircle(nX, nY, nRadius);
		// 캡쳐

		Sleep(m_nMsPerFrame);
	}
}

void CMFC_ProblemDlg::_CaptureImage(CString filePath)
{


	//m_Image.Save()
}

void CMFC_ProblemDlg::OnBnClickedBtnDraw()
{
	// TODO: Add your control notification handler code here
	UINT8 nGrayOfBG = 0xff;
	if (m_Image.IsNull())
		_CreateImage();
	else
		memset(m_Image.GetBits(), nGrayOfBG, m_Image.GetWidth() * m_Image.GetHeight());

	UpdateData(TRUE);

	int nRadiusMin = 10;
	int nRadiusMax = 100;
	m_nRadius = rand() % (nRadiusMax - nRadiusMin) + nRadiusMin;

	_DrawCircle(m_nStartX, m_nStartY, m_nRadius);
}

void CMFC_ProblemDlg::OnBnClickedBtnAction()
{
	// TODO: Add your control notification handler code here
	if (m_Image.IsNull())
		_CreateImage();

	m_nEndX = GetDlgItemInt(IDC_EDIT_END_X);
	m_nEndY = GetDlgItemInt(IDC_EDIT_END_Y);
	m_nFrams = GetDlgItemInt(IDC_EDIT_FRAMES);
	m_nMsPerFrame = GetDlgItemInt(IDC_EDIT_MSPF);

	_MoveCircle(m_nRadius, { m_nStartX, m_nStartY }, { m_nEndX, m_nEndY });
}
