#pragma once


// RegDlg 对话框

class RegDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RegDlg)

public:
	RegDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~RegDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REGDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_userName;
	CString m_password;
	CString m_passwordAgain;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	CString m_email;
};
