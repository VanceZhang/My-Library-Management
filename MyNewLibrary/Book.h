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

	string publishDate;//发布日期；预留变量，未使用
	string bookType;//图书种类；预留变量，未使用

	bool operator == (const Book& T)
	{
		if ((bookId == T.bookId) && (bookName == T.bookName)&&(author==T.author)&&(publisher==T.publisher)&&(price==T.price))
		{
			return true;
		}
		return false;
	}

};

class BookQuery//用于书籍检索
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

class Borrow //借阅数据
{
public:
	string bookId;
	string userId;
	string bookName;
	string borrowDate;
	string returnDate;//预留数据
	
};


