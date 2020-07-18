// UserDlg.cpp: 实现文件
//

#include "pch.h"
#include "MyNewLibrary.h"
#include "UserDlg.h"
#include "afxdialogex.h"
#include"BorrowDlg.h"
#include"MyNewLibraryDlg.h"
#include "Controller.h"
#include <iostream>


// UserDlg 对话框

IMPLEMENT_DYNAMIC(UserDlg, CDialogEx)

UserDlg::UserDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USER, pParent)
	, m_bookId(_T(""))
	, m_bookName(_T(""))
	, m_author(_T(""))
	, m_publisher(_T(""))
	, m_highPrice(0)
	, m_lowPrice(0)
	, m_userId(_T(""))
	, m_check(FALSE)
{

}

UserDlg::~UserDlg()
{
}

void UserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_bookId);
	DDX_Text(pDX, IDC_EDIT3, m_bookName);
	DDX_Text(pDX, IDC_EDIT5, m_author);
	DDX_Text(pDX, IDC_EDIT6, m_publisher);
	DDX_Text(pDX, IDC_EDIT4, m_highPrice);
	DDX_Text(pDX, IDC_EDIT2, m_lowPrice);
	DDX_Control(pDX, IDC_TREE2, m_tree);
	DDX_Control(pDX, IDC_LIST2, m_list);
	DDX_Text(pDX, IDC_EDIT11, m_userId);
	DDX_Control(pDX, IDC_PICTURE, m_picture);
	DDX_Check(pDX, IDC_CHECK1, m_check);
}


BEGIN_MESSAGE_MAP(UserDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL2, &UserDlg::OnBnClickedCancel2)
	ON_BN_CLICKED(IDCANCEL, &UserDlg::OnBnClickedCancel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &UserDlg::OnLvnItemchangedList2)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE2, &UserDlg::OnTvnSelchangedTree2)
	ON_BN_CLICKED(IDCANCEL3, &UserDlg::OnBnClickedCancel3)
	ON_BN_CLICKED(IDC_BUTTON2, &UserDlg::OnBnClickedButton2)
	
	ON_BN_CLICKED(IDC_CHECK1, &UserDlg::OnBnClickedCheck1)
END_MESSAGE_MAP()

BOOL UserDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

	m_picture.ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
#define HBMP(filepath, width, height)(HBITMAP)LoadImage(AfxGetInstanceHandle(), filepath, IMAGE_BITMAP, width, height, LR_LOADFROMFILE|LR_CREATEDIBSECTION)
	CRect rect;
	m_picture.GetWindowRect(rect);
	m_picture.SetBitmap(HBMP(TEXT("./title1.bmp"), rect.Width(), rect.Height()));

	m_editFont.CreatePointFont(140, _T("微软雅黑"));
	m_list.SetFont(&m_editFont);
	m_editFont1.CreatePointFont(120, _T("微软雅黑"));
	m_tree.SetFont(&m_editFont);

	HTREEITEM root = m_tree.InsertItem("图书分类", 0, 1, NULL);

	CString strArr[] = { "编号", "书名", "作者","出版社","价格","总数","库存" };
	for (int i = 0; i < 7; i++) {
		m_list.InsertColumn(i, strArr[i], LVCFMT_LEFT, 110);//参数 索引 内容 对齐 列宽
	}

	Controller control;
	ifstream infile;
	infile.open("book.dat");
	vector<Book> bookInfo = control.readBookFile(infile);
	vector<Book>::iterator it;
	int i = 0;
	for (it = bookInfo.begin(); it != bookInfo.end(); it++)
	{
		int j = 0;

		CString str1, str2, str3;
		//m_list.InsertItem(i,_T(""));
		m_list.InsertItem(i, it->bookId.c_str());
		m_list.SetItemText(i, ++j, it->bookName.c_str());
		m_list.SetItemText(i, ++j, it->author.c_str());
		m_list.SetItemText(i, ++j, it->publisher.c_str());
		str1.Format("%f", it->price);
		m_list.SetItemText(i, ++j, str1);
		str2.Format("%d", it->num);
		m_list.SetItemText(i, ++j, str2);
		str3.Format("%d", it->stock);
		m_list.SetItemText(i, ++j, str3);
		i++;

	}

	infile.close();
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES | LVS_EX_GRIDLINES);

	
	
	return  TRUE;
}

// UserDlg 消息处理程序


//打开借阅情况
void UserDlg::OnBnClickedCancel2()//打开借阅情况
{
	// TODO: 在此添加控件通知处理程序代码
	BorrowDlg borrowDlg;
	borrowDlg.DoModal();
}

//注销
void UserDlg::OnBnClickedCancel()//注销按钮
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();

}

//无
void UserDlg::OnLvnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

//无
void UserDlg::OnTvnSelchangedTree2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

}

//借阅选中书籍
void UserDlg::OnBnClickedCancel3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	string tem = m_userId.GetBuffer(0);
	if (!tem.empty())
	{
		bool state;
		Controller control;
		ofstream outfile;
		outfile.open("borrow.dat", ios::app);
		for (int i = 0; i < m_list.GetItemCount(); i++) {
			state = m_list.GetCheck(i);

			if (state == TRUE) {
				if (control.borrowBook(tem, m_list.GetItemText(i, 0).GetBuffer(0), m_list.GetItemText(i, 1).GetBuffer(0)))
					MessageBox("借阅成功");
				else
					MessageBox("借阅失败");

			}
		}
		outfile.close();
	}
	else
		MessageBox("请输入用户名！");

}

//搜索按钮
void UserDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	Controller control;
	ifstream infile;
	infile.open("book.dat");
	BookQuery q;
	UpdateData(TRUE);
	q.bookId = m_bookId.GetBuffer(0);
	q.bookName = m_bookName.GetBuffer(0);
	q.author = m_author.GetBuffer(0);
	q.publisher = m_publisher.GetBuffer(0);
	q.lowPrice = m_lowPrice;
	q.highPrice = m_highPrice;


	control.selectBook(q);

	
	vector<Book>::iterator it;
	int i = 0;
	m_list.DeleteAllItems();

	if (q.books.size()) {
		for (it = q.books.begin(); it != q.books.end(); it++)
		{
			int j = 0;

			CString str1, str2, str3;
			m_list.InsertItem(i, it->bookId.c_str());
			m_list.SetItemText(i, ++j, it->bookName.c_str());
			m_list.SetItemText(i, ++j, it->author.c_str());
			m_list.SetItemText(i, ++j, it->publisher.c_str());
			str1.Format("%f", it->price);
			m_list.SetItemText(i, ++j, str1);
			str2.Format("%d", it->num);
			m_list.SetItemText(i, ++j, str2);
			str3.Format("%d", it->stock);
			m_list.SetItemText(i, ++j, str3);
			i++;
		}
	}
	else
		MessageBox("查无此书");

}





void UserDlg::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_check)
	{
		for (int i = 0; i < m_list.GetItemCount(); i++)
		{
			m_list.SetCheck(i, TRUE);
		}
	}
	else
	{
		for (int i = 0; i < m_list.GetItemCount(); i++)
		{
			m_list.SetCheck(i, FALSE);
		}
	}
}
