#pragma once
#include <string>
#include <iostream>

template <typename T> class Array
{
public:
	Array() = default;

	Array(int length) : m_length(length)
	{
		if (length <= 0)
		{
			throw IncorrectLength();
		}
		else
		{
			m_data = new T[length]{};
		}
	}

	int m_length{};

	template <typename T> Array(const Array& Array)
	{
		reallocate(Array.getLength());

		for (int i = 0; i < m_length; ++i)
			m_data[i] = Array.m_data[i];
	}

	~Array()
	{
		delete[] m_data;
	}

	void erase()
	{
		delete[] m_data;
		m_data = nullptr;
		m_length = 0;
	}

	template <typename T> void reallocate(int newLength)
	{
		erase();

		if (newLength <= 0)
			return;

		m_data = new T[newLength];
		m_length = newLength;
	}

	template <typename T> void resize(int newLength)
	{
		if (newLength == m_length)
			return;

		if (newLength <= 0)
		{
			erase();
			return;
		}

		T* data{ new T[newLength] };

		if (m_length > 0)
		{
			int elementsToCopy{ (newLength > m_length) ? m_length : newLength };

			for (int i = 0; i < elementsToCopy; ++i)
				data[i] = m_data[i];
		}

		delete[] m_data;

		m_data = data;
		m_length = newLength;
	}

	template <typename T> T& operator [](int i)
	{
		if (i >= 0 and i <= m_length)
			return m_data[i];
		else
			throw NoPosition();
	};

	template <typename T> int getLength() const
	{
		return m_length;
	}

	template <typename T> Array<T>& operator=(const Array& Array)
	{
		if (&Array == this)
			return *this;

		reallocate(Array.getLength());

		for (int i = 0; i < m_length; ++i)
			m_data[i] = Array.m_data[i];

		return *this;
	}

	template <typename T> void insertBefore(T value, int i)
	{
		if (i >= 0 && i <= m_length)
			T* data{ new T[m_length + 1] };
		else
			throw OutOfRange();

		T* data{ new T[m_length + 1] };

		for (int _i = 0; _i < i; ++_i)
			data[_i] = m_data[_i];

		data[i] = value;

		for (int _i = i; _i < m_length; ++_i)
			data[_i + 1] = m_data[_i];

		delete[] m_data;
		m_data = data;
		++m_length;
	}

	template <typename T> void remove(int i)
	{
		if (i >= 0 && i <= m_length)
		{
			if (m_length == 1)
			{
				erase();
				return;
			}
			T* data{ new T[m_length + 1] };
		}
		else
			throw OutOfRange();

		T* data{ new T[m_length - 1] };

		for (int _i = 0; _i < i; ++_i)
			data[_i] = m_data[_i];

		for (int _i = i + 1; _i < m_length; ++_i)
			data[_i - 1] = m_data[_i];

		delete[] m_data;
		m_data = data;
		--m_length;
	}

	template <typename T> void insertAtBeginning(T value)
	{
		insertBefore(value, 0);
	}

	template <typename T> void insertAtEnd(T value)
	{
		insertBefore(value, m_length);
	}

protected:
	T* m_data{};
};
