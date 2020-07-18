// RegDlg.cpp: 实现文件
//

#include "pch.h"
#include "MyNewLibrary.h"
#include "RegDlg.h"
#include "afxdialogex.h"
#include "User.h"
#include "Controller.h"


// RegDlg 对话框

IMPLEMENT_DYNAMIC(RegDlg, CDialogEx)

RegDlg::RegDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REGDLG, pParent)
	, m_userName(_T(""))
	, m_password(_T(""))
	, m_passwordAgain(_T(""))
	, m_email(_T(""))
{

}

RegDlg::~RegDlg()
{
}

void RegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_userName);
	DDX_Text(pDX, IDC_EDIT2, m_password);
	DDX_Text(pDX, IDC_EDIT3, m_passwordAgain);
	DDX_Text(pDX, IDC_EDIT7, m_email);
}


BEGIN_MESSAGE_MAP(RegDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &RegDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &RegDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// RegDlg 消息处理程序


void RegDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void RegDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Controller control;
	string str_email = (CStringA)m_email;
	if ((m_password == m_passwordAgain)&& control.isValidEmail(str_email))
	{
		User user;
		user.password = (CStringA)m_password;
		user.userId = (CStringA)m_userName;
		user.Email = (CStringA)m_email;
		
		control.addUser(user);
		MessageBox(_T("注册成功，请登录"));
		CDialogEx::OnOK();
	}
	else if(!control.isValidEmail(str_email))
		MessageBox(_T("请输入正确的邮箱"));
	else
		MessageBox(_T("两次密码不一致"));
	
}
