#pragma once
#include <string>
#include<vector>
#include <fstream>
#include"User.h"
#include "Book.h"
#include <algorithm>
using namespace std;
class Controller
{
private:
	bool isValidChar(char ch);

public:
	//从存储文件中读取数据
	vector<User> readUserFile(ifstream& infile);
	vector<Manager> readManagerFile(ifstream& infile);
	vector<Book> readBookFile(ifstream& infile);
	vector<Borrow> readBorrowFile(ifstream& infile);

	bool addUser(User &user);//用于管理员增加用户，或用户注册
	bool addBook(Book &book);
	bool selectUser(User& user);//用户登录;用于管理员搜索用户,未启用
	bool selectManager(Manager&manager);//管理员登录
	void selectBook(BookQuery &q);//对需求的q进行查询，并将结果写入Book数组，数组size为0则没搜索到。
	
	bool borrowBook(string userId, string bookId, string bookName);//借书
	bool returnBook(string user_id, string book_id);//还书
	
	bool deleteUser(string userId);
	bool deleteBook(string bookId);

	bool isValidEmail(string strEmailmail);

	bool modifyPassword(string Email, string password);

};



