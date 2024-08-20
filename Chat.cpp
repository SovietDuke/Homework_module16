#include "Chat.h"
#include "ExcLimitUsername.h"
#include "ExcLimitPassword.h"
#include "ExcLimitEmail.h"

//�����������
Chat::Chat(std::string chatName)
{
	if (chatName.size() <= MAX_CHATNAME_SIZE) _chatName = chatName;
}

//������ �������� ����
void Chat::setChatName(std::string newName)
{
	if (newName.size() > MAX_CHATNAME_SIZE)
	{
		std::cout << "�������� ���� �� ������ ��������� " << MAX_CHATNAME_SIZE << " ������!" << std::endl;
		return;
	}
	_chatName = newName;
}

//�������� ���� ����
void Chat::menu()
{
	std::cout << "================== " << _chatName << " ==================" << std::endl << std::endl;
	std::cout << "����������, ������������� ��� ����������� ��� �������� quit ��� ���������� ���������." << std::endl;
	short command = 0;
	User* currentUser = Chat::authorization(); //������� �����������
	if (currentUser)
	{
		std::string input;
		while (command != 3)
		{
			std::cout << "�����:" << std::endl;
			std::cout << "1 - �������� ����." << std::endl;
			std::cout << "2 - ������ ��� � ������ �������������." << std::endl;
			std::cout << "3 - ���������� ������ �������� �������������." << std::endl;
			std::cout << "��� ���������� �������� �������� �����." << std::endl;
			std::cin >> input;
			if (input == "1") command = 0;
			else if (input == "2") command = 1;
			else if (input == "3") command = 2;
			else if (input == "quit" or input == "Quit" or input == "QUIT") command = 3;
			else std::cout << std::endl << "������� ����� �� ������!" << std::endl;
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
	std::cout << "����� �� ����." << std::endl;
}

//������� ����������� ������������
User* Chat::authorization()
{
	User* temp;
	std::string input;
	while (input != "quit" and input != "Quit" and input != "QUIT")
	{
		std::cout << "================== ����������� ==================" << std::endl;
		std::cout << "������� �����:" << std::endl;
		std::cin >> input;
		if (input == "quit" or input == "Quit" or input == "QUIT") return 0;
		if (input.size() > MAX_USERNAME) throw ExcLimitUsername();
		//��������� ������� ������������ � ������� ������������� _userArray
		temp = _userArray.getUserByName(input);
		if (temp)
		{
			std::cout << "������� ������:" << std::endl;
			for (int i = 0; i < 3; i++)
			{
				std::cin >> input;
				if (input == "quit" or input == "Quit" or input == "QUIT") return 0;
				if (input.size() > MAX_PASSWORD) throw ExcLimitPassword();
				if (temp->_password == input)
				{
					std::cout << "����������� ��������� �������!" << std::endl;
					return temp;
				}
				std::cout << "������ ��������! �������� �������: " << 2 - i << std::endl;
			}
			std::cout << "�������� ������. ��������� �����." << std::endl;
			return 0;
		}
		//���� ����������� ���������, ���������� ������������ ������������������
		std::cout << std::endl << "������ ������������ �� ����������!" << std::endl;
		std::cout << std::endl << "������ ������������������?" << std::endl;
		std::cout << "������� 1 ��� ����������� ��� ����� ������ ������� ��� ������." << std::endl;
		std::cin >> input;
		if (input == "1") Chat::registration();
		else return 0;
	}
	return 0;
}

//����������� ������ ������������
void Chat::registration()
{
	std::cout << "================== ����������� ������������ ==================" << std::endl;
	std::string name, email, password;
	while (name != "quit" and name != "Quit" and name != "QUIT")
	{
		std::cout << "���������� �����: " << std::endl;
		std::cin >> name;
		if (name == "quit" or name == "Quit" or name == "QUIT") return;
		if (name.size() > MAX_PASSWORD) throw ExcLimitPassword();
		if (_userArray.getUserByName(name)) //�������� ������������ ������
			std::cout << "������������ � ����� ������� ��� ����������!" << std::endl;
		else break;
	} 
	std::cout << "������� ����������� �����: " << std::endl;
	std::cin >> email;
	if (email == "quit" or email == "Quit" or email == "QUIT") return;
	if (name.size() > MAX_EMAIL) throw ExcLimitEmail();
	std::cout << "���������� ������: " << std::endl;
	std::cin >> password;
	if (password == "quit" or password == "Quit" or password == "QUIT") return;
	if (password.size() > MAX_PASSWORD) throw ExcLimitPassword();
	User* newUser = new User(name, email, password);
	_userArray.add(newUser);
}

//������� ���������� ������ ������������ � ���
void Chat::addUser(User* newUser)
{
	for (int i = 0; i < Chat::_userArray.getLength(); i++)
	{
		if (Chat::_userArray[i] == newUser) return;
	}
	_userArray.add(newUser);
}

//������� �������� ������������ �� ����
void Chat::deleteUser(User* user)
{
	_userArray.remove(user);
}

//����� ������ ������������������ ������������� � ����
void Chat::showUsers()
{
	std::cout << "������� ������������: " << std::endl;;
	for (int i = 0; i < _userArray.getLength(); i++)
	{
		std::cout << Chat::_userArray[i]->_username << std::endl;
	}
	std::cout << std::endl;
	return;
}

//�������� ��������� "����"
void Chat::sendMessage(User* currentUser)
{
	std::cout << "������� ���������:" << std::endl;
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
		std::cout << "����� ��������� �� ������ ��������� " << MAX_MESSAGE_SIZE << " ������!";
	}
	std::cout << std::endl;
	return;
}

//�������� ��������� ����������� ������������
void Chat::sendMessageToU(User* currentUser)
{
	
	std::string secondUserName;
	while (secondUserName != "quit" and secondUserName != "Quit" and secondUserName != "QUIT")
	{
		std::cout << "������� ��� ������������: " << std::endl;
		std::cin >> secondUserName;
		if (currentUser->_username != secondUserName)
		{
			User* secondUser = _userArray.getUserByName(secondUserName);
			if (secondUser)
			{
				std::cout << "������� ��������� ������������ " << secondUserName << std::endl;
				std::string message;
				std::cin >> message;
				if (message.size() <= MAX_MESSAGE_SIZE)
				{
					secondUser->showMessage(message);
				}
				else
				{
					std::cout << "����� ��������� �� ������ ��������� " << MAX_MESSAGE_SIZE << " ������!";
				}
			}
			else std::cout << "����� ������������ ����������� � ����." << std::endl;
			std::cout << std::endl;
			return;
		}
		else std::cout << "������ �������� ������ ����!" << std::endl;
	}
}