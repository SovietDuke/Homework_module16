#pragma once
#include <exception>

class ExcLimitPassword : public std::exception
{
public:
	virtual const char* what() const noexcept override
	{
		return "Превышена максимальная длина пароля!";
	}
};
