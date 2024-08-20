#pragma once
#include "UserArray.h"
#include <iostream>

#define MAX_CHATNAME_SIZE 20 //фиксируем максимальную длину чата
#define MAX_MESSAGE_SIZE 50 //фиксируем максимальную длину сообщений

class Chat
{
public:
	Chat(std::string chatName); //конструктор
	void setChatName(std::string newName); //сеттер названия чата
	void menu(); //основное меню чата
	User* authorization(); //функция авторизации 
	void registration(); //функция регистрации нового пользователя
	void addUser(User* newUser); //функция добавления нового пользователя в чат
	void deleteUser(User* user); //функция удаления пользователя из чата
	void showUsers(); //вывод списка пользователей
	void sendMessage(User* currentUser); //отправка сообщения "всем"
	void sendMessageToU(User* currentUser); //отправка сообщения конкретному пользователю
private:
	std::string _chatName; //название чата
	UserArray<User*> _userArray; //массив пользователей
};
