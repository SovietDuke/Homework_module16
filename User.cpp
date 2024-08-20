#include "User.h"


// дфеолтный конструктор
User::User(){}

// конструктор по имени пользователя
User::User(std::string username)
{
	_username = username;
}

// конструктор по имени пользователя и адресу эл. почты
User::User(std::string username, std::string email)
{
	_username = username;
	_email = email;
}

// конструктор класса по имени пользователя, паролю и адресу эл. почты
User::User(std::string username, std::string email, std::string password)
{
	_username = username;
	_email = email;
	_password = password;
}

// деструктор
User::~User() {}

// сеттер идентификатора пользоателя
void User::setID(unsigned long newID)
{
	_id = newID;
}

// сеттер имени пользователя
void User::setUserName(std::string newName)
{
	_username = newName;
}

// сеттер электронной почты
void User::setEmail(std::string newEmail)
{
	_email = newEmail;
}

// сеттер пароля
void User::setPassword(std::string newPassword)
{
	_password = newPassword;
}

// функция для отображения в консоли всей информации пользователя
void User::printUser()
{
	std::cout << "User ID: " << _id << std::endl;
	std::cout << "User name: " << _username << std::endl;
	std::cout << "User email: " << _email << std::endl;
}

// выводит полученное сообщение в консоль
void User::showMessage(std::string message)
{
	std::cout << message << std::endl;
}

// геттер пользовательского id
unsigned long User::getID() const
{
	return _id;
}

// геттер имени пользователя
std::string User::getUserName() const
{
	return _username;
}

// геттер электронной почты
std::string User::getEmail() const
{
	return _email;
}

// геттер пароля
std::string User::getPassword() const
{
	return _password;
}