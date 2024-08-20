#pragma once
#include <string>
#include <iostream>

#define MAX_USERNAME 30 //��������� ������������ ����� ������������������ �����
#define MAX_EMAIL 30 //��������� ������������ ����� email
#define MAX_PASSWORD 20 //��������� ������������ ���������� ������ � ������

class User
{
public:
	//������������
	User(); 
	User(std::string username); 
	User(std::string username, std::string email);
	User(std::string username, std::string email, std::string password);

	~User(); //����������
	std::string _username; // ��� ������������
	std::string _password; // ������
	unsigned long _id = 0; // ���������� ������������� �����������
	void setID(unsigned long newID); //������ �������������� �����������
	void setUserName(std::string newName); //������ ����� ������������
	void setEmail(std::string newEmail); // ������ ����������� �����
	void setPassword(std::string newPassword); //������ ������
	void printUser(); //���������� � ������� ��� ���������� ������������
	void showMessage(std::string message); // ������� ���������� ��������� � �������
	unsigned long getID() const; // ������ ����������������� id
	std::string getUserName() const; // ������ ����� ������������
	std::string getEmail() const; // ������ ����������� �����
	std::string getPassword() const; // ������ ������
private:
	std::string _email; // ����� ����������� �����
};
