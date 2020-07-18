#pragma once


// addBookDlg 对话框

class addBookDlg : public CDialogEx
{
	DECLARE_DYNAMIC(addBookDlg)

public:
	addBookDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~addBookDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDBOOKS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_bookId;
	CString m_bookName;
//	CString m_price;
//	CString m_num;
	CString author;
	CString m_publisher;
	double m_price;
	unsigned int m_num;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel2();
};
