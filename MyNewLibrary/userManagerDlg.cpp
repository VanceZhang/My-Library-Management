// userManagerDlg.cpp: 实现文件
//

#include "pch.h"
#include "MyNewLibrary.h"
#include "userManagerDlg.h"
#include "afxdialogex.h"
#include"AddUserDlg.h"
#include <iostream>
#include"Controller.h"
using namespace std;



// userManagerDlg 对话框

IMPLEMENT_DYNAMIC(userManagerDlg, CDialogEx)

userManagerDlg::userManagerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADMINUSERDLG, pParent)
{

}

userManagerDlg::~userManagerDlg()
{
}

void userManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_PICTURE, m_picture);
}


BEGIN_MESSAGE_MAP(userManagerDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &userManagerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &userManagerDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &userManagerDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// userManagerDlg 消息处理程序
BOOL userManagerDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

	m_picture.ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
#define HBMP(filepath, width, height)(HBITMAP)LoadImage(AfxGetInstanceHandle(), filepath, IMAGE_BITMAP, width, height, LR_LOADFROMFILE|LR_CREATEDIBSECTION)
	CRect rect;
	m_picture.GetWindowRect(rect);
	m_picture.SetBitmap(HBMP(TEXT("./title1.bmp"), rect.Width(), rect.Height()));

	m_editFont.CreatePointFont(140, _T("微软雅黑"));
	m_list.SetFont(&m_editFont);
	SetFont(&m_editFont);


	CString strArr[] = { "用户名","密码","邮箱" };
	for (int i = 0; i < 3; i++) {
		m_list.InsertColumn(i, strArr[i], LVCFMT_LEFT, 130);//参数 索引 内容 对齐 列宽
	}

	Controller control;
	ifstream infile;
	infile.open("user.dat");
	vector<User> userInfo = control.readUserFile(infile);
	vector<User>::iterator it;
	int i = 0;
	for (it = userInfo.begin(); it != userInfo.end(); it++)
	{
		m_list.InsertItem(i, it->userId.c_str());
		m_list.SetItemText(i, 1, it->password.c_str());
		m_list.SetItemText(i, 2, it->Email.c_str());
		i++;

	}


	infile.close();
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES | LVS_EX_GRIDLINES);
	return  TRUE;
}

//添加用户
void userManagerDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	AddUserDlg addUser;
	addUser.DoModal();

}

//删除用户
void userManagerDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	
		bool state;
		Controller control;
		
		for (int i = 0; i < m_list.GetItemCount(); i++) {
			state = m_list.GetCheck(i);

			if (state == TRUE) {
				if (control.deleteUser(m_list.GetItemText(i, 0).GetBuffer(0)))
					MessageBox("删除成功");
				else
					MessageBox("删除失败");

			}
		}

	
	
}

//刷新
void userManagerDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_list.DeleteAllItems();
	Controller control;
	ifstream infile;
	infile.open("user.dat");
	vector<User> userInfo = control.readUserFile(infile);
	vector<User>::iterator it;
	int i = 0;
	for (it = userInfo.begin(); it != userInfo.end(); it++)
	{
		m_list.InsertItem(i, it->userId.c_str());
		m_list.SetItemText(i, 1, it->password.c_str());
		m_list.SetItemText(i, 2, it->Email.c_str());
		i++;

	}
	infile.close();
	UpdateData(TRUE);
}
