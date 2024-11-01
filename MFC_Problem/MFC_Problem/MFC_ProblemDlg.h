
// MFC_ProblemDlg.h : 헤더 파일
//

#pragma once


// CMFC_ProblemDlg 대화 상자
class CMFC_ProblemDlg : public CDialogEx
{
private:
	constexpr static int PATH_LENG = 256;
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
	void _CreateImage(UINT8 nGrayOfBG = 255);
	void _DrawImage();
	void _DrawCircle(int nCenterX, int nCenterY, int nRadius, UINT8 nGray = 0, bool bIsDraw = true);
	void _DrawRect(CRect rect, UINT8 nGray = 0, bool bIsDraw = true);
	void _SetPixel(const int nX, const int nY, const UINT8 color)
	{
		if (_IsValidPos(nX, nY))
			((UINT8*)m_Image.GetBits())[nY*m_Image.GetPitch() + nX] = color;
	}
	void _MoveCircle(const int nRadius, const  POINT startPos, const  POINT endPos);
	void _CaptureImage(CString filePath);

	bool _IsValidPos(const int nX, const int nY) const { return CRect(0, 0, m_Image.GetWidth(), m_Image.GetHeight()).PtInRect({ nX, nY }); }
	bool _IsInCircle(const int nX, const int nY, const int nRadius) const { return nX * nX + nY * nY <= nRadius * nRadius; }

	int _LerpInt(const int nStart, const int nEnd, const float fAlpha) const { return nStart + (int)((nEnd - nStart) * fAlpha); }

	CRect _MakeRectbyCenter(POINT centerPos, SIZE size) const
	{ return CRect(centerPos.x - size.cx / 2, centerPos.y - size.cy / 2, centerPos.x + size.cx / 2, centerPos.y + size.cy / 2); }

public:
	afx_msg void OnBnClickedBtnDraw();
	afx_msg void OnBnClickedBtnAction();
private:
	CImage m_Image;
	CString m_ImageDirPath;

	int m_nStartX;
	int m_nStartY;
	int m_nEndX;
	int m_nEndY;
	int m_nFrams;
	int m_nMsPerFrame;
	int m_nRadius;
};
