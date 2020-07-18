#pragma once


// bookManagerDlg 对话框

class bookManagerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(bookManagerDlg)

public:
	bookManagerDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~bookManagerDlg();

	virtual BOOL OnInitDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADMINBOOKSDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CListCtrl m_list;
	afx_msg void OnBnClickedButton4();
	CFont m_editFont;
	CStatic m_picture;
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
};
