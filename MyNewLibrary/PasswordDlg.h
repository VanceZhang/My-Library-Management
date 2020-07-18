#pragma once


// PasswordDlg 对话框

class PasswordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PasswordDlg)

public:
	PasswordDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~PasswordDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PasswordDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_email;
//	CEdit m_password;
	CString m_password;
	CString m_passwordAgain;
	afx_msg void OnBnClickedOk();
};
