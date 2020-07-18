#pragma once
#include <string>
#include<vector>
using namespace std;
class User
{
public:
	string userId;
	string password;
	string Email;

	bool operator == (const User& T)
	{
		if ((userId == T.userId)&&(password==T.password))
		{
			return true;
		}
		return false;
	}
};

class UserQuery //用于用户查询,预留类，未使用
{
public:
	string userId;
	string password;
	vector<User> users;

};

class Manager{
public:
	string userId;
	string password;
	string Email;

	bool operator == (const Manager& T)
	{
		if ((userId == T.userId) && (password == T.password))
		{
			return true;
		}
		return false;
	}

};

