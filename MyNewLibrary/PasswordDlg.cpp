// PasswordDlg.cpp: 实现文件
//

#include "pch.h"
#include "MyNewLibrary.h"
#include "PasswordDlg.h"
#include "afxdialogex.h"
#include"Controller.h"


// PasswordDlg 对话框

IMPLEMENT_DYNAMIC(PasswordDlg, CDialogEx)

PasswordDlg::PasswordDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PasswordDlg, pParent)
	, m_email(_T(""))
	, m_password(_T(""))
	, m_passwordAgain(_T(""))
{

}

PasswordDlg::~PasswordDlg()
{
}

void PasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT7, m_email);
	//  DDX_Control(pDX, IDC_EDIT2, m_password);
	DDX_Text(pDX, IDC_EDIT2, m_password);
	DDX_Text(pDX, IDC_EDIT3, m_passwordAgain);
}


BEGIN_MESSAGE_MAP(PasswordDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &PasswordDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// PasswordDlg 消息处理程序


void PasswordDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Controller control;
	string str_email = (CStringA)m_email;
	control.modifyPassword(m_email.GetBuffer(0), m_password.GetBuffer(0));
	if ((m_password == m_passwordAgain) && control.isValidEmail(str_email) && control.modifyPassword(m_email.GetBuffer(0), m_password.GetBuffer(0)))
	{

		MessageBox(_T("修改成功，请登录"));
		CDialogEx::OnOK();
	}
	else if (!control.isValidEmail(str_email))
		MessageBox(_T("请输入正确的邮箱"));
	else if (m_password != m_passwordAgain)
		MessageBox(_T("两次密码不一致"));
	else
		MessageBox("未知错误");

}
