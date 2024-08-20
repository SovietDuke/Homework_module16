#pragma once
#include <exception>

class ExcLimitEmail : public std::exception
{
public:
	virtual const char* what() const noexcept override
	{
		return "Превышен максимальный размер для пользовательского имени.";
	}
};
