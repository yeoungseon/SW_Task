
// SW_MFCDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "SW_MFC.h"
#include "SW_MFCDlg.h"
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


// CSWMFCDlg 대화 상자



CSWMFCDlg::CSWMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SW_MFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSWMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_X1, m_editX1);
	DDX_Control(pDX, IDC_EDIT_X2, m_editX2);
	DDX_Control(pDX, IDC_EDIT_Y1, m_editY1);
	DDX_Control(pDX, IDC_EDIT_Y2, m_editY2);
}

BEGIN_MESSAGE_MAP(CSWMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CSWMFCDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_DRAW, &CSWMFCDlg::OnBnClickedButtonDraw)
	ON_BN_CLICKED(IDC_BUTTON_ACTION, &CSWMFCDlg::OnBnClickedButtonAction)
END_MESSAGE_MAP()


// CSWMFCDlg 메시지 처리기

BOOL CSWMFCDlg::OnInitDialog()
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

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSWMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSWMFCDlg::OnPaint()
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
HCURSOR CSWMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSWMFCDlg::OnBnClickedButtonOpen()
{
	CFileDialog dlg(TRUE, L"bmp", NULL, OFN_FILEMUSTEXIST, L"Image Files (*.bmp;*.jpg;*.jpeg)|*.bmp;*.jpg;*.jpeg||");
	if (dlg.DoModal() == IDOK)
	{
		CString filePath = dlg.GetPathName();

		// CImage로 이미지 로드
		CImage image;
		if (FAILED(image.Load(filePath))) {
			AfxMessageBox(L"이미지 로드 실패");
			return;
		}

		// 이미지 픽셀 데이터 접근
		int width = image.GetWidth();
		int height = image.GetHeight();

		int sumX = 0, sumY = 0, pixelCount = 0;

		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				COLORREF color = image.GetPixel(x, y);

				//검정색 확인
				if (GetRValue(color) < 50 && GetGValue(color) < 50 && GetBValue(color) < 50) // 어두운 픽셀
				{
					sumX += x;
					sumY += y;
					pixelCount++;
				}
			}
		}

		// 중심 좌표 계산
		int centerX = (pixelCount > 0) ? sumX / pixelCount : 0;
		int centerY = (pixelCount > 0) ? sumY / pixelCount : 0;

		// Picture Control의 DC 가져오기
		CClientDC dc(GetDlgItem(IDC_IMAGE_DISPLAY));
		CRect rect;
		GetDlgItem(IDC_IMAGE_DISPLAY)->GetClientRect(&rect);

		// 이미지 출력 (Picture Control 크기에 맞춤)
		image.StretchBlt(dc.m_hDC, rect, SRCCOPY);

		// 스케일링 계산
		double scaleX = static_cast<double>(rect.Width()) / width;
		double scaleY = static_cast<double>(rect.Height()) / height;

		// 중심 좌표 스케일링
		centerX = static_cast<int>(centerX * scaleX);
		centerY = static_cast<int>(centerY * scaleY);

		// 중심 좌표에 X 표시
		dc.MoveTo(centerX - 10, centerY);
		dc.LineTo(centerX + 10, centerY);
		dc.MoveTo(centerX, centerY - 10);
		dc.LineTo(centerX, centerY + 10);

		// 중심 좌표 텍스트 출력
		CString coords;
		coords.Format(L"(%d, %d)", centerX, centerY);
		dc.TextOutW(centerX + 15, centerY, coords);

		// 디버깅 메시지
		CString debugMsg;
		debugMsg.Format(L"Detected Center: (%d, %d)", centerX, centerY);
		AfxMessageBox(debugMsg);
	}
}


void CSWMFCDlg::OnBnClickedButtonDraw()
{
	CString strX1, strY1;
	int x1, y1;

	m_editX1.GetWindowTextW(strX1);
	m_editY1.GetWindowTextW(strY1);

	x1 = _ttoi(strX1); // x1 값
	y1 = _ttoi(strY1); // y1 값

	// 랜덤 반지름 생성 (10 ~ 50)
	m_drawRadius = rand() % 41 + 10; // 반지름 저장

	// 원 그리기
	CClientDC dc(this);
	dc.Ellipse(x1 - m_drawRadius, y1 - m_drawRadius, x1 + m_drawRadius, y1 + m_drawRadius);

	// 중심 좌표와 반지름 디버그 출력 (옵션)
	CString debugMsg;
	debugMsg.Format(L"Drawn Circle: Center(%d, %d), Radius(%d)", x1, y1, m_drawRadius);
	AfxMessageBox(debugMsg);
}


void CSWMFCDlg::OnBnClickedButtonAction()
{
	CString strX1, strY1, strX2, strY2;
	int x1, y1, x2, y2;

	// 입력값 가져오기
	m_editX1.GetWindowTextW(strX1);
	m_editY1.GetWindowTextW(strY1);
	m_editX2.GetWindowTextW(strX2);
	m_editY2.GetWindowTextW(strY2);

	x1 = _ttoi(strX1);
	y1 = _ttoi(strY1);
	x2 = _ttoi(strX2);
	y2 = _ttoi(strY2);

	// 이동 단계 계산
	int steps = 10;
	int dx = (x2 - x1) / steps;
	int dy = (y2 - y1) / steps;

	// 이미지 저장 폴더 생성
	CString folderPath = L".\\image";
	CreateDirectory(folderPath, NULL);

	CClientDC dc(this); // 디바이스 컨텍스트

	for (int i = 0; i <= steps; ++i)
	{
		// 현재 중심 좌표 계산
		int cx = x1 + i * dx;
		int cy = y1 + i * dy;

		// 화면에 원 그리기
		RedrawWindow();
		dc.Ellipse(cx - m_drawRadius, cy - m_drawRadius, cx + m_drawRadius, cy + m_drawRadius);

		// 이미지 저장
		CImage image;
		image.Create(300, 300, 32); // 임의 크기 설정
		CDC* pImageDC = CDC::FromHandle(image.GetDC());
		pImageDC->FillSolidRect(0, 0, 300, 300, RGB(255, 255, 255)); // 배경 색상

		// 이미지의 원 좌표는 (cx, cy)를 기준으로 그리기
		pImageDC->Ellipse(150 + (cx - x1) - m_drawRadius, 150 + (cy - y1) - m_drawRadius,
			150 + (cx - x1) + m_drawRadius, 150 + (cy - y1) + m_drawRadius);

		image.ReleaseDC();

		CString filename;
		filename.Format(L"%s\\frame_%02d.bmp", folderPath, i);
		image.Save(filename); // 파일 저장

		Sleep(200); // 애니메이션 효과 지연
		RedrawWindow(); // 화면 갱신
	}
}
