// AdminDlg.cpp: 实现文件
//

#include "pch.h"
#include "MyNewLibrary.h"
#include "AdminDlg.h"
#include "afxdialogex.h"
#include"BorrowDlg.h"
#include"MyNewLibraryDlg.h"
#include "Controller.h"
#include <iostream>
#include "bookManagerDlg.h"
#include"userManagerDlg.h"



// AdminDlg 对话框

IMPLEMENT_DYNAMIC(AdminDlg, CDialogEx)

AdminDlg::AdminDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADIMINDLG, pParent)
	, m_publisher(_T(""))
	, m_author(_T(""))
	, m_bookName(_T(""))
	, m_bookId(_T(""))
	, m_highPrice(0)
	, m_lowPrice(0)
	//, m_check(FALSE)
{

}

AdminDlg::~AdminDlg()
{
}

void AdminDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE2, m_tree);
	DDX_Control(pDX, IDC_LIST2, m_list);
	DDX_Text(pDX, IDC_EDIT6, m_publisher);
	DDX_Text(pDX, IDC_EDIT5, m_author);
	DDX_Text(pDX, IDC_EDIT3, m_bookName);
	DDX_Text(pDX, IDC_EDIT1, m_bookId);
	//  DDX_Text(pDX, IDC_EDIT2, m_lowPrice);
	//  DDX_Text(pDX, IDC_EDIT4, m_highPrice);
	DDX_Text(pDX, IDC_EDIT4, m_highPrice);
	DDX_Text(pDX, IDC_EDIT2, m_lowPrice);
	DDX_Control(pDX, IDC_PICTURE, m_picture);
	//  DDX_Check(pDX, IDC_CHECK1, m_check);
}


BEGIN_MESSAGE_MAP(AdminDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &AdminDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &AdminDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDCANCEL3, &AdminDlg::OnBnClickedCancel3)
	ON_BN_CLICKED(IDCANCEL4, &AdminDlg::OnBnClickedCancel4)
	//ON_BN_CLICKED(IDC_CHECK1, &AdminDlg::OnBnClickedCheck1)
	ON_EN_CHANGE(IDC_EDIT2, &AdminDlg::OnEnChangeEdit2)
END_MESSAGE_MAP()


// AdminDlg 消息处理程序
//与用户界面大致相同，但没有复选框
BOOL AdminDlg::OnInitDialog() {
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
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT  | LVS_EX_GRIDLINES);
	return  TRUE;
}

//注销按钮
void AdminDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

//搜索按钮
void AdminDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	Controller control;
	
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



//书籍管理
void AdminDlg::OnBnClickedCancel3()
{
	// TODO: 在此添加控件通知处理程序代码
	bookManagerDlg bookManager;
	bookManager.DoModal();
}

//用户管理
void AdminDlg::OnBnClickedCancel4()
{
	// TODO: 在此添加控件通知处理程序代码
	userManagerDlg userManager;
	userManager.DoModal();
}





void AdminDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
