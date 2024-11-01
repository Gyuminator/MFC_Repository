
// MFC_ProblemDlg.h : 헤더 파일
//

#pragma once


// CMFC_ProblemDlg 대화 상자
class CMFC_ProblemDlg : public CDialogEx
{
	// 생성입니다.
public:
	CMFC_ProblemDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_PROBLEM_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	// private 멤버 함수 _
	void _CreateImage();
	void _DrawImage();
	void _DrawCircle(int nCenterX, int nCenterY, int nRadius);
	bool _IsValidPos(int nX, int nY)
	{
		return (nX >= 0) && (nX < m_Image.GetWidth()) && (nY >= 0) && (nY < m_Image.GetHeight());
	}
	void _SetPixel(int nX, int nY, UINT8 color)
	{
		if (_IsValidPos(nX, nY))
			((UINT8*)m_Image.GetBits())[nY*m_Image.GetPitch() + nX] = color;
	}


private:
	CImage m_Image;

	int m_nStartX;
	int m_nStartY;
	int m_nEndX;
	int m_nEndY;
public:
	afx_msg void OnBnClickedBtnDraw();
};
