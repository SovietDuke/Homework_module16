#pragma once
#include <exception>

class OutOfRange : public std::exception
{
public:
	virtual const char* what() const noexcept override
	{
		return "Вне диапозона контейнера!";
	}
};
