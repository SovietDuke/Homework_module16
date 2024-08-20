#pragma once
#include <string>
#include <iostream>

#define MAX_USERNAME 30 //фиксируем максимальную длину пользователеьского имени
#define MAX_EMAIL 30 //фиксируем мкксимальную длину email
#define MAX_PASSWORD 20 //фиксируем максимальное количество знаков в пароле

class User
{
public:
	//конструкторы
	User(); 
	User(std::string username); 
	User(std::string username, std::string email);
	User(std::string username, std::string email, std::string password);

	~User(); //деструктор
	std::string _username; // имя пользователя
	std::string _password; // пароль
	unsigned long _id = 0; // уникальный идентификатор пользоателя
	void setID(unsigned long newID); //сеттер идентификатора пользоателя
	void setUserName(std::string newName); //сеттер имени пользователя
	void setEmail(std::string newEmail); // сеттер электронной почты
	void setPassword(std::string newPassword); //сеттер пароля
	void printUser(); //отображает в консоли всю информацию пользователя
	void showMessage(std::string message); // выводит полученное сообщение в консоль
	unsigned long getID() const; // геттер пользовательского id
	std::string getUserName() const; // геттер имени пользователя
	std::string getEmail() const; // геттер электронной почты
	std::string getPassword() const; // геттер пароля
private:
	std::string _email; // адрес электронной почты
};
