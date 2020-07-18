#pragma once


// AdminDlg 对话框

class AdminDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AdminDlg)

public:
	AdminDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AdminDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADIMINDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_tree;
	CListCtrl m_list;
	CString m_publisher;
	CString m_author;
	CString m_bookName;
	CString m_bookId;
//	CString m_lowPrice;
//	CString m_highPrice;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton2();
	double m_highPrice;
	double m_lowPrice;
	afx_msg void OnBnClickedCancel3();
	afx_msg void OnBnClickedCancel4();

	virtual BOOL OnInitDialog();
	CFont m_editFont;
	CFont m_editFont1;
	CStatic m_picture;
//	BOOL m_check;
	
	afx_msg void OnEnChangeEdit2();
};
