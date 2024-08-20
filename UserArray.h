#pragma once
#include <vector>
#include <algorithm>
#include "User.h"
#include "IncorrectLength.h"
#include "Noposition.h"

template <typename T>
class UserArray
{
public:
    // Дефолтный конструктор
    UserArray() = default;

    // Конструктор с заданным количеством пользователей
    explicit UserArray(int length)
    {
        if (length <= 0)
        {
            throw IncorrectLength();
        }
        _users.resize(length);
    }

    // Оператор доступа к элементу
    T& operator[](int i)
    {
        if (i >= 0 && i < static_cast<int>(_users.size()))
        {
            return _users[i];
        }
        else
        {
            throw NoPosition();
        }
    }

    // Функция вывода информации о всех пользователях
    void print() const
    {
        for (const auto& user : _users)
        {
            user.printUser();
        }
    }

    // Функция добавления пользователя
    void add(const T& user)
    {
        _users.push_back(user);
    }

    // Функция удаления пользователя
    void remove(const T& user)
    {
        auto it = std::remove(_users.begin(), _users.end(), user);
        if (it != _users.end())
        {
            _users.erase(it, _users.end());
        }
    }

    // Функция получения пользователя по ID
    User* getUserByID(unsigned long ID)
    {
        auto it = std::find_if(_users.begin(), _users.end(), [ID](const T& user) {
            return user->_id == ID;
            });
        return it != _users.end() ? *it : nullptr;
    }

    // Функция получения пользователя по имени
    User* getUserByName(const std::string& Name)
    {
        auto it = std::find_if(_users.begin(), _users.end(), [&Name](const T& user) {
            return user->_username == Name;
            });
        return it != _users.end() ? *it : nullptr;
    }

    // Геттер количества пользователей
    int getLength() const
    {
        return static_cast<int>(_users.size());
    }

private:
    std::vector<T> _users; // Вектор пользователей
};
