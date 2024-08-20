#include "Chat.h"
#include "ExcLimitUsername.h"
#include "ExcLimitPassword.h"
#include "ExcLimitEmail.h"

//конструктор
Chat::Chat(std::string chatName)
{
	if (chatName.size() <= MAX_CHATNAME_SIZE) _chatName = chatName;
}

//сеттер названия чата
void Chat::setChatName(std::string newName)
{
	if (newName.size() > MAX_CHATNAME_SIZE)
	{
		std::cout << "Название чата не должно превышать " << MAX_CHATNAME_SIZE << " знаков!" << std::endl;
		return;
	}
	_chatName = newName;
}

//основное меню чата
void Chat::menu()
{
	std::cout << "================== " << _chatName << " ==================" << std::endl << std::endl;
	std::cout << "Пожалуйста, авторизуйтесь для продолжения или наберите quit для завершения программы." << std::endl;
	short command = 0;
	User* currentUser = Chat::authorization(); //сначала авторизация
	if (currentUser)
	{
		std::string input;
		while (command != 3)
		{
			std::cout << "Опции:" << std::endl;
			std::cout << "1 - написать всем." << std::endl;
			std::cout << "2 - начать чат с другим пользователем." << std::endl;
			std::cout << "3 - посмотреть список активных пользователей." << std::endl;
			std::cout << "Для завершения програмы наберите выход." << std::endl;
			std::cin >> input;
			if (input == "1") command = 0;
			else if (input == "2") command = 1;
			else if (input == "3") command = 2;
			else if (input == "quit" or input == "Quit" or input == "QUIT") command = 3;
			else std::cout << std::endl << "Введите опцию из списка!" << std::endl;
			switch (command)
			{
			case 0:
			{
				Chat::sendMessage(currentUser);
				break;
			}
			case 1:
			{
				Chat::sendMessageToU(currentUser);
				break;
			}
			case 2:
				Chat::showUsers();
				break;
			}
		}
	}
	std::cout << "Выход из чата." << std::endl;
}

//функция авторизации пользователя
User* Chat::authorization()
{
	User* temp;
	std::string input;
	while (input != "quit" and input != "Quit" and input != "QUIT")
	{
		std::cout << "================== АВТОРИЗАЦИЯ ==================" << std::endl;
		std::cout << "Введите логин:" << std::endl;
		std::cin >> input;
		if (input == "quit" or input == "Quit" or input == "QUIT") return 0;
		if (input.size() > MAX_USERNAME) throw ExcLimitUsername();
		//проверяем наличие пользователя в массиве пользователей _userArray
		temp = _userArray.getUserByName(input);
		if (temp)
		{
			std::cout << "Введите пароль:" << std::endl;
			for (int i = 0; i < 3; i++)
			{
				std::cin >> input;
				if (input == "quit" or input == "Quit" or input == "QUIT") return 0;
				if (input.size() > MAX_PASSWORD) throw ExcLimitPassword();
				if (temp->_password == input)
				{
					std::cout << "Авторизация выполнена успешно!" << std::endl;
					return temp;
				}
				std::cout << "Пароль неверный! Осталось попыток: " << 2 - i << std::endl;
			}
			std::cout << "Неверный пароль. Повторите позже." << std::endl;
			return 0;
		}
		//если авторизация неуспешна, предлагаем пользователю зарегистрироваться
		std::cout << std::endl << "Такого пользователя не существует!" << std::endl;
		std::cout << std::endl << "Хотите зарегистрироваться?" << std::endl;
		std::cout << "Введите 1 для регистрации или любую другую клавишу для выхода." << std::endl;
		std::cin >> input;
		if (input == "1") Chat::registration();
		else return 0;
	}
	return 0;
}

//регистрация нового пользователя
void Chat::registration()
{
	std::cout << "================== РЕГИСТРАЦИЯ ПОЛЬЗОВАТЕЛЯ ==================" << std::endl;
	std::string name, email, password;
	while (name != "quit" and name != "Quit" and name != "QUIT")
	{
		std::cout << "Придумайте логин: " << std::endl;
		std::cin >> name;
		if (name == "quit" or name == "Quit" or name == "QUIT") return;
		if (name.size() > MAX_PASSWORD) throw ExcLimitPassword();
		if (_userArray.getUserByName(name)) //проверка уникальности логина
			std::cout << "Пользователь с таким логином уже существует!" << std::endl;
		else break;
	} 
	std::cout << "Укажите электронную почту: " << std::endl;
	std::cin >> email;
	if (email == "quit" or email == "Quit" or email == "QUIT") return;
	if (name.size() > MAX_EMAIL) throw ExcLimitEmail();
	std::cout << "Придумайте пароль: " << std::endl;
	std::cin >> password;
	if (password == "quit" or password == "Quit" or password == "QUIT") return;
	if (password.size() > MAX_PASSWORD) throw ExcLimitPassword();
	User* newUser = new User(name, email, password);
	_userArray.add(newUser);
}

//функция добавления нового пользователя в чат
void Chat::addUser(User* newUser)
{
	for (int i = 0; i < Chat::_userArray.getLength(); i++)
	{
		if (Chat::_userArray[i] == newUser) return;
	}
	_userArray.add(newUser);
}

//функция удаления пользователя из чата
void Chat::deleteUser(User* user)
{
	_userArray.remove(user);
}

//вывод списка зарегистрированных пользователей в чате
void Chat::showUsers()
{
	std::cout << "Текущие пользователи: " << std::endl;;
	for (int i = 0; i < _userArray.getLength(); i++)
	{
		std::cout << Chat::_userArray[i]->_username << std::endl;
	}
	std::cout << std::endl;
	return;
}

//отправка сообщения "всем"
void Chat::sendMessage(User* currentUser)
{
	std::cout << "Введите сообщение:" << std::endl;
	std::string message;
	std::cin >> message;	
	int size = _userArray.getLength();
	if (size <= MAX_MESSAGE_SIZE)
	{
		std::cout << std::endl;
		for (int i = 0; i < size; i++)
		{
			if (Chat::_userArray[i] != currentUser) Chat::_userArray[i]->showMessage(message);
		}
	}
	else
	{
		std::cout << "Длина сообщения не должна превышать " << MAX_MESSAGE_SIZE << " знаков!";
	}
	std::cout << std::endl;
	return;
}

//отправка сообщения конкретному пользователю
void Chat::sendMessageToU(User* currentUser)
{
	
	std::string secondUserName;
	while (secondUserName != "quit" and secondUserName != "Quit" and secondUserName != "QUIT")
	{
		std::cout << "Введите имя пользователя: " << std::endl;
		std::cin >> secondUserName;
		if (currentUser->_username != secondUserName)
		{
			User* secondUser = _userArray.getUserByName(secondUserName);
			if (secondUser)
			{
				std::cout << "Введите сообщение пользователю " << secondUserName << std::endl;
				std::string message;
				std::cin >> message;
				if (message.size() <= MAX_MESSAGE_SIZE)
				{
					secondUser->showMessage(message);
				}
				else
				{
					std::cout << "Длина сообщения не должна превышать " << MAX_MESSAGE_SIZE << " знаков!";
				}
			}
			else std::cout << "Такой пользователь отсутствует в чате." << std::endl;
			std::cout << std::endl;
			return;
		}
		else std::cout << "Нельзя написать самому себе!" << std::endl;
	}
}