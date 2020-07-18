#pragma once


// userManagerDlg 对话框

class userManagerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(userManagerDlg)

public:
	userManagerDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~userManagerDlg();

	virtual BOOL OnInitDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADMINUSERDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	CFont m_editFont;
	CStatic m_picture;
};
