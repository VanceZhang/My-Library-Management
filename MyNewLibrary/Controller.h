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
	//�Ӵ洢�ļ��ж�ȡ����
	vector<User> readUserFile(ifstream& infile);
	vector<Manager> readManagerFile(ifstream& infile);
	vector<Book> readBookFile(ifstream& infile);
	vector<Borrow> readBorrowFile(ifstream& infile);

	bool addUser(User &user);//���ڹ���Ա�����û������û�ע��
	bool addBook(Book &book);
	bool selectUser(User& user);//�û���¼;���ڹ���Ա�����û�,δ����
	bool selectManager(Manager&manager);//����Ա��¼
	void selectBook(BookQuery &q);//�������q���в�ѯ���������д��Book���飬����sizeΪ0��û��������
	
	bool borrowBook(string userId, string bookId, string bookName);//����
	bool returnBook(string user_id, string book_id);//����
	
	bool deleteUser(string userId);
	bool deleteBook(string bookId);

	bool isValidEmail(string strEmailmail);

	bool modifyPassword(string Email, string password);

};



