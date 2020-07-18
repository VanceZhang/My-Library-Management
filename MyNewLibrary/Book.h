#pragma once
#include <string>
#include<vector>
#include <afxstr.h>
using namespace std;
class Book
{
public:
	string bookId;
	string bookName;
	string author;
	string publisher;
	double price;
	unsigned int num;
	unsigned int stock;

	string publishDate;//�������ڣ�Ԥ��������δʹ��
	string bookType;//ͼ�����ࣻԤ��������δʹ��

	bool operator == (const Book& T)
	{
		if ((bookId == T.bookId) && (bookName == T.bookName)&&(author==T.author)&&(publisher==T.publisher)&&(price==T.price))
		{
			return true;
		}
		return false;
	}

};

class BookQuery//�����鼮����
{
public:
	string bookId;
	string bookName;
	string author;
	string publisher;
	double lowPrice;
	double highPrice;
	bool hasStock;
	vector<Book> books;

	bool operator == (const BookQuery& T)
	{
		if ((bookId == T.bookId) && (bookName == T.bookName) && (author == T.author) && (publisher == T.publisher))
		{
			return true;
		}
		return false;
	}
};

class Borrow //��������
{
public:
	string bookId;
	string userId;
	string bookName;
	string borrowDate;
	string returnDate;//Ԥ������
	
};


