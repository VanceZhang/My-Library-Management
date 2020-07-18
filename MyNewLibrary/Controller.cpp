#include "pch.h"
#include "Controller.h"
#include"User.h"
#include "Book.h"
#include <algorithm>
#include<string>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <ctime>
using namespace std;

//读取文件，存入vector数组
vector<User> Controller::readUserFile(ifstream& infile)
{
	User user;
	vector<User> userVec;

	while (infile >> user.userId >> user.password>>user.Email) {

		userVec.push_back(user);
	}
	return userVec;

}

vector<Manager> Controller::readManagerFile(ifstream& infile)
{
	Manager manager;
	vector<Manager> managerVec;

	while (infile >> manager.userId >> manager.password>>manager.Email) {

		managerVec.push_back(manager);
	}
	return managerVec;

}

vector<Book> Controller::readBookFile(ifstream& infile)
{
	Book book;
	vector<Book> bookVec;

	while (infile >> book.bookId >> book.bookName >> book.author >> book.publisher >> book.price >> book.num >> book.stock) {

		bookVec.push_back(book);
	}
	return bookVec;
}

vector<Borrow> Controller::readBorrowFile(ifstream& infile)
{
	Borrow borrow;
	vector<Borrow> borrowVec;

	while (infile >> borrow.userId >> borrow.bookId>>borrow.bookName>>borrow.borrowDate) {

		borrowVec.push_back(borrow);
	}
	return borrowVec;
}


//添加（注册）
bool Controller::addUser(User& user) 
{
	//先判断用户是否存在，若存在，i=0
	ifstream infile;
	infile.open("user.dat");
	vector<User> userInfo = readUserFile(infile);
	infile.close();
	vector<User>::iterator it;
	int i = 1;
	for (it = userInfo.begin(); it != userInfo.end(); it++)
	{
		if ((user.userId != (it->userId)) && user.Email != (it->Email))
			i = 1;
		else
			return 0;
	}

	ofstream outfile;
	outfile.open("user.dat", ios::app);
	if ((outfile << '\n' << user.userId << '\t' << user.password << '\t'<<user.Email<<endl) && (i == 1))
	{
		outfile.close();
		return 1;
	}

	else 
		return 0;
}
//添加书籍
bool Controller::addBook(Book& book) // 使用时切记file.open("", ios::app)和file.close();
{
	ofstream outfile;
	outfile.open("book.dat", ios::app);
	if (outfile << '\n' << book.bookId << '\t' << book.bookName << '\t' << book.author << '\t' << book.publisher << '\t' << book.price << '\t' << book.num << '\t' << book.stock << endl)
	{
		outfile.close();
		return 1;
	}
	else
		return 0;
}
//搜索用户（登录）
bool Controller::selectUser(User& user) {
	ifstream infile;
	infile.open("user.dat", ios::in);
	vector<User>_user = readUserFile(infile);
	infile.close();
	vector<User>::iterator it;
	for (it = _user.begin(); it != _user.end(); it++) 
	{
		if ((it->userId == user.userId)&&(it->password==user.password))
			return 1;

		else
			return 0;
	}
	
}
//搜索管理员（登录）
bool Controller::selectManager(Manager& manager) {
	ifstream infile;
	infile.open("manager.dat", ios::in);
	vector<Manager>_manager = readManagerFile(infile);
	infile.close();
	vector<Manager>::iterator  it;
	for (it = _manager.begin(); it != _manager.end(); it++)
	{
		if ((it->userId == manager.userId) && (it->password == manager.password))
			return 1;

		else
			return 0;
	}
}
//搜索书籍，并将结果存入bookquery的books数组中
void Controller::selectBook(BookQuery& q)
{
	ifstream infile;
	infile.open("book.dat");
	vector<Book>_book = readBookFile(infile);
	infile.close();
	vector<Book>::iterator it;
	q.books.clear();

	for (it = _book.begin(); it != _book.end(); it++)
	{
		if (!q.bookId.empty())
		{
			if (it->bookId == q.bookId)
				q.books.push_back(*it);
		}
		if (!q.bookName.empty())
		{
			if (it->bookName == q.bookName)
				q.books.push_back(*it);
		}
		if (!q.author.empty())
		{
			if (it->author == q.author)
				q.books.push_back(*it);
		}
		if (!q.publisher.empty())
		{
			if (it->publisher == q.publisher)
				q.books.push_back(*it);
		}
		if (q.highPrice > 0 && q.highPrice >= q.lowPrice)
		{
			if (((it->price) < q.highPrice) && ((it->price) > q.lowPrice))
				q.books.push_back(*it);
		}
		if (q.publisher.empty() && q.author.empty() && q.bookName.empty() && q.bookId.empty() && (q.highPrice == 0))
			q.books.push_back(*it);

	}
	infile.close();


}
//借书
bool Controller::borrowBook(string userId, string bookId,string bookName)
{
	
	auto t = chrono::system_clock::to_time_t(chrono::system_clock::now());
	stringstream ss;
	ss << put_time(localtime(&t), "%Y年%m月%d日%H时%M分%S秒");
	string str_time = ss.str();
	


	ofstream outfile;
	outfile.open("borrow.dat", ios::app);
	if (outfile << '\n' << userId << '\t' << bookId << '\t' << bookName << '\t' << str_time << endl)
	{
		outfile.close();
		return 1;
	}

	else
		return 0;
}
//还书
bool Controller::returnBook(string user_id, string book_id)
{
	

	ifstream infile;
	infile.open("borrow.dat");
	vector<Borrow> borrow = readBorrowFile(infile);
	vector<Borrow>::iterator it;
	infile.close();

	ofstream outfile;
	outfile.open("borrow.dat", ios::trunc);
	int i = 0;
	for (it = borrow.begin(); it != borrow.end(); it++)
	{
		if ((it->userId == user_id) && (it->bookId == book_id))
			continue;
		else 
		{
			if (outfile << '\n' << it->userId << '\t' << it->bookId <<'\t'<<it->bookName<<'\t'<<it->borrowDate<< endl)
				i=1;
		}
	}
	return i;

}
//删除用户
bool Controller::deleteUser(string userId)
{
	ifstream infile;
	infile.open("user.dat");
	vector<User> users = readUserFile(infile);
	infile.close();

	vector<User>::iterator it;

	ofstream outfile;
	outfile.open("user.dat", ios::trunc);
	outfile << "";
	outfile.close();

	int i=0 ;
	for (it = users.begin(); it != users.end(); it++)
	{
		if (userId != it->userId)
		{
			if (addUser(*it))
				i = 1;
			else
				i = 0;

		}
		else
			continue;
	}
	return i;
	
	
}
//删除书籍
bool Controller::deleteBook(string bookId)
{
	ifstream infile;
	infile.open("book.dat");
	vector<Book> books = readBookFile(infile);
	infile.close();

	vector<Book>::iterator it;

	ofstream outfile;
	outfile.open("book.dat", ios::trunc);
	outfile << "";
	outfile.close();
	
	int i = 0;
	for (it = books.begin(); it != books.end(); it++)
	{
		if (bookId != it->bookId)
		{
			if (addBook(*it))
				i = 1;
			else
				i = 0;

		}
		else
			continue;
	}
	return i;
}

//判断字符
bool Controller::isValidChar(char ch)
{
	if ((ch >= 97) && (ch <= 122)) //26个小写字母
		return true;
	if ((ch >= 65) && (ch <= 90)) //26个大写字母
		return true;
	if ((ch >= 48) && (ch <= 57)) //0~9
		return true;
	if (ch == 95 || ch == 45 || ch == 46 || ch == 64) //_-.@
		return true;
	return false;
}
//判断邮箱格式是否正确
bool Controller::isValidEmail(string strEmail)
{
	if (strEmail.length() < 5) //26个小写字母
		return false;

	char ch = strEmail[0];
	if (((ch >= 97) && (ch <= 122)) || ((ch >= 65) && (ch <= 90))||((ch >= 48) && (ch <= 57)))
	{
		int atCount = 0;
		int atPos = 0;
		int dotCount = 0;
		for (int i = 1; i < strEmail.length(); i++) //0已经判断过了，从1开始
		{
			ch = strEmail[i];
			if (isValidChar(ch))
			{
				if (ch == 64) //"@"
				{
					atCount++;
					atPos = i;
				}
				else if ((atCount > 0) && (ch == 46))//@符号后的"."号
					dotCount++;
			}
			else
				return false;
		}
		//6. 结尾不得是字符“@”或者“.”
		if (ch == 46)
			return false;
		//2. 必须包含一个并且只有一个符号“@”
		//3. @后必须包含至少一个至多三个符号“.”
		if ((atCount != 1) || (dotCount < 1) || (dotCount > 3))
			return false;
		//5. 不允许出现“@.”或者.@
		int x, y;
		x = strEmail.find("@.");
		y = strEmail.find(".@");
		if (x > 0 || y > 0)
		{
			return false;
		}
		return true;
	}
	return false;
}
//修改密码
bool Controller::modifyPassword(string Email,string password)
{
	ifstream infile;
	infile.open("user.dat");
	vector<User> userInfo = readUserFile(infile);
	infile.close();
	vector<User>::iterator it;

	//清空文件
	ofstream outfile;
	outfile.open("user.dat", ios::trunc);
	outfile << "";
	outfile.close();

	
	int j = 0;
	for (it = userInfo.begin(); it != userInfo.end(); it++)
	{
		if (Email == (it->Email))
		{
			it->password = password;
			j=1;
		}
		else
			j ++;
		addUser(*it);
	

	}
	if (j != userInfo.size())
		return 1;
	else
		return 0;

}

