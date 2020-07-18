// AddUserDlg.cpp: 实现文件
//

#include "pch.h"
#include "MyNewLibrary.h"
#include "AddUserDlg.h"
#include "afxdialogex.h"
#include "Controller.h"



// AddUserDlg 对话框

IMPLEMENT_DYNAMIC(AddUserDlg, CDialogEx)

AddUserDlg::AddUserDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADDUSER, pParent)
	, m_userId(_T(""))
	, m_password(_T(""))
	, m_passwordAgain(_T(""))
	, m_email(_T(""))
{

}

AddUserDlg::~AddUserDlg()
{
}

void AddUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT7, m_userId);
	DDX_Text(pDX, IDC_EDIT12, m_password);
	DDX_Text(pDX, IDC_EDIT8, m_passwordAgain);
	DDX_Text(pDX, IDC_EDIT9, m_email);
}


BEGIN_MESSAGE_MAP(AddUserDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &AddUserDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDCANCEL2, &AddUserDlg::OnBnClickedCancel2)
	ON_BN_CLICKED(IDOK, &AddUserDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// AddUserDlg 消息处理程序

//清空
void AddUserDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_userId = "";
	m_password = "";
	m_passwordAgain = "";
	m_email = "";
	
	UpdateData(FALSE);
}

//退出
void AddUserDlg::OnBnClickedCancel2()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

//注册
void AddUserDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	
	Controller control;
	string str_email = (CStringA)m_email;
	if ((m_password == m_passwordAgain) && control.isValidEmail(str_email))
	{
		User user;
		user.password = (CStringA)m_password;
		user.userId = (CStringA)m_userId;
		user.Email = (CStringA)m_email;

		control.addUser(user);
		MessageBox(_T("注册成功，请登录"));
		CDialogEx::OnOK();
	}
	else if (!control.isValidEmail(str_email))
		MessageBox(_T("请输入正确的邮箱"));
	else
		MessageBox(_T("两次密码不一致"));
	

}
