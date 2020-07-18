#pragma once


// BorrowDlg 对话框

class BorrowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(BorrowDlg)

public:
	BorrowDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~BorrowDlg();
	virtual BOOL OnInitDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BORROWDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	CString m_userId;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit1();
	CFont m_editFont;
	CStatic m_picture;
};
