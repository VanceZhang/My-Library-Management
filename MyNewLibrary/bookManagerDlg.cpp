// bookManagerDlg.cpp: 实现文件
//

#include "pch.h"
#include "MyNewLibrary.h"
#include "bookManagerDlg.h"
#include "afxdialogex.h"
#include"addBookDlg.h"
#include"Controller.h"
#include <iostream>
using namespace std;


// bookManagerDlg 对话框

IMPLEMENT_DYNAMIC(bookManagerDlg, CDialogEx)

bookManagerDlg::bookManagerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADMINBOOKSDLG, pParent)
{

}

bookManagerDlg::~bookManagerDlg()
{
}

void bookManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_PICTURE, m_picture);
}


BEGIN_MESSAGE_MAP(bookManagerDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &bookManagerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &bookManagerDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &bookManagerDlg::OnBnClickedButton4)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &bookManagerDlg::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// bookManagerDlg 消息处理程序

BOOL bookManagerDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

	m_picture.ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
#define HBMP(filepath, width, height)(HBITMAP)LoadImage(AfxGetInstanceHandle(), filepath, IMAGE_BITMAP, width, height, LR_LOADFROMFILE|LR_CREATEDIBSECTION)
	CRect rect;
	m_picture.GetWindowRect(rect);
	m_picture.SetBitmap(HBMP(TEXT("./title1.bmp"), rect.Width(), rect.Height()));

	m_editFont.CreatePointFont(140, _T("微软雅黑"));
	m_list.SetFont(&m_editFont);
	

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

//添加
void bookManagerDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	addBookDlg addbook;
	addbook.DoModal();
}

//删除
void bookManagerDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	bool state;
	Controller control;

	for (int i = 0; i < m_list.GetItemCount(); i++) {
		state = m_list.GetCheck(i);

		if (state == TRUE) {
			if (control.deleteBook(m_list.GetItemText(i, 0).GetBuffer(0)))
				MessageBox("删除成功");
			else
				MessageBox("删除失败");

		}
	}


}

//刷新
void bookManagerDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_list.DeleteAllItems();
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
	UpdateData(FALSE);

}


void bookManagerDlg::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
