#pragma once


// UserDlg 对话框

class UserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(UserDlg)

public:
	UserDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~UserDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel2();
	afx_msg void OnBnClickedCancel();
	CString m_bookId;
	CString m_bookName;
	CString m_author;
	CString m_publisher;
	double m_highPrice;
	double m_lowPrice;
	afx_msg void OnLvnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTvnSelchangedTree2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedCancel3();
	CTreeCtrl m_tree;
	virtual BOOL OnInitDialog();
	CListCtrl m_list;
	afx_msg void OnBnClickedButton2();
	CString m_userId;
	CFont m_editFont;
	CFont m_editFont1;
	CStatic m_picture;
	
	afx_msg void OnBnClickedCheck1();
	BOOL m_check;
};
