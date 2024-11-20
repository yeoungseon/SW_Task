
// SW_MFCDlg.h: 헤더 파일
//

#pragma once


// CSWMFCDlg 대화 상자
class CSWMFCDlg : public CDialogEx
{
// 생성입니다.
public:
	CSWMFCDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SW_MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	int m_drawRadius;
	
	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonDraw();
	CEdit m_editX1;
	CEdit m_editX2;
	CEdit m_editY1;
	CEdit m_editY2;
	afx_msg void OnBnClickedButtonAction();
};
