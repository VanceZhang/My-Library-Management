// BorrowDlg.cpp: 实现文件
//

#include "pch.h"
#include "MyNewLibrary.h"
#include "BorrowDlg.h"
#include "afxdialogex.h"
#include "UserDlg.h"
#include "afxdialogex.h"
#include"BorrowDlg.h"
#include"MyNewLibraryDlg.h"
#include "Controller.h"
#include <iostream>


// BorrowDlg 对话框

IMPLEMENT_DYNAMIC(BorrowDlg, CDialogEx)

BorrowDlg::BorrowDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BORROWDLG, pParent)
	, m_userId(_T(""))
{

}

BorrowDlg::~BorrowDlg()
{
}

BOOL BorrowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_picture.ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
#define HBMP(filepath, width, height)(HBITMAP)LoadImage(AfxGetInstanceHandle(), filepath, IMAGE_BITMAP, width, height, LR_LOADFROMFILE|LR_CREATEDIBSECTION)
	CRect rect;
	m_picture.GetWindowRect(rect);
	m_picture.SetBitmap(HBMP(TEXT("./title1.bmp"), rect.Width(), rect.Height()));

	m_editFont.CreatePointFont(140, _T("微软雅黑"));
	m_list.SetFont(&m_editFont);
	

	CString strArr[] = { "编号" ,"书名","借阅时间"};
	for (int i = 0; i < 3; i++) {
		m_list.InsertColumn(i, strArr[i], LVCFMT_LEFT, 110);//参数 索引 内容 对齐 列宽
	}
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES | LVS_EX_GRIDLINES);
	return TRUE;
}

void BorrowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT1, m_userId);
	DDX_Control(pDX, IDC_PICTURE, m_picture);
}


BEGIN_MESSAGE_MAP(BorrowDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &BorrowDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &BorrowDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, &BorrowDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &BorrowDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// BorrowDlg 消息处理程序

//归还书籍
void BorrowDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Controller control;
	bool state;
	for (int i = 0; i < m_list.GetItemCount(); i++)
	{
		state = m_list.GetCheck(i);

		if (state == TRUE)
		{
			string bookId = m_list.GetItemText(i, 0).GetBuffer(0);
			string userId = m_userId.GetBuffer(0);
			if (control.returnBook(userId, bookId))
				MessageBox("归还成功");
			else
				MessageBox("归还失败");

		}
	}
}


void BorrowDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	string tem = m_userId.GetBuffer(0);
	if (!tem.empty())
	{
		Controller control;
		ifstream infile;
		infile.open("borrow.dat");
		vector<Borrow> borrowInfo = control.readBorrowFile(infile);
		vector<Borrow>::iterator it;
		int i = 0;
		m_list.DeleteAllItems();
		for (it = borrowInfo.begin(); it != borrowInfo.end(); it++)
		{
			if (tem == (it->userId))
			{
				m_list.InsertItem(i, it->bookId.c_str());
				m_list.SetItemText(i, 1, it->bookName.c_str());
				m_list.SetItemText(i, 2, it->borrowDate.c_str());
				i++;
			}

		}
		infile.close();
	}
	else
		MessageBox("请输入用户名！");

	UpdateData(FALSE);
}

//全选
void BorrowDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < m_list.GetItemCount(); i++)
	{
		m_list.SetCheck(i, TRUE);
	}
}

//无
void BorrowDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
