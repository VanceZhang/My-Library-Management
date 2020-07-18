// addBookDlg.cpp: 实现文件
//

#include "pch.h"
#include "MyNewLibrary.h"
#include "addBookDlg.h"
#include "afxdialogex.h"
#include "Book.h"
#include <iostream>
#include "Controller.h"
using namespace std;


// addBookDlg 对话框

IMPLEMENT_DYNAMIC(addBookDlg, CDialogEx)

addBookDlg::addBookDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADDBOOKS, pParent)
	, m_bookId(_T(""))
	, m_bookName(_T(""))
	, author(_T(""))
	, m_publisher(_T(""))
	, m_price(0)
	, m_num(0)
{

}

addBookDlg::~addBookDlg()
{
}

void addBookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT7, m_bookId);
	DDX_Text(pDX, IDC_EDIT9, m_bookName);
	//  DDX_Text(pDX, IDC_EDIT8, m_price);
	//  DDX_Text(pDX, IDC_EDIT10, m_num);
	DDX_Text(pDX, IDC_EDIT13, author);
	DDX_Text(pDX, IDC_EDIT14, m_publisher);
	DDX_Text(pDX, IDC_EDIT8, m_price);
	DDX_Text(pDX, IDC_EDIT10, m_num);
}


BEGIN_MESSAGE_MAP(addBookDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &addBookDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &addBookDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL2, &addBookDlg::OnBnClickedCancel2)
END_MESSAGE_MAP()


// addBookDlg 消息处理程序

//清空
void addBookDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_bookId = "";
	m_bookName = "";
	author = "";
	m_publisher = "";
	m_price = 0;
	m_num = 0;
	UpdateData(FALSE);
}

//确定添加
void addBookDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Book book;
	book.bookId=m_bookId.GetBuffer(0);
	book.bookName=m_bookName.GetBuffer(0);
	book.author=author.GetBuffer(0);
	book.publisher=m_publisher.GetBuffer(0);
	book.price=m_price;
	book. num=m_num;
	book.stock=m_num;

	Controller control;
	
	
	control.addBook(book);
	
	MessageBox("添加成功");

	UpdateData(FALSE);


}

//退出
void addBookDlg::OnBnClickedCancel2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
