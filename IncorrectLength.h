#pragma once
#include <exception>

class IncorrectLength : public std::exception
{
public:
	virtual const char* what() const noexcept override
	{
		return "Объём контейнера меньше или равен 0!";
	}
};
