#pragma once
#include <exception>

class NoPosition : public std::exception
{
public:
	virtual const char* what() const noexcept override
	{
		return "В контейнере нет такой позиции!";
	}
};
