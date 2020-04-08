#pragma once

template<typename T>
class Singleton
{
public:
	static T& GetInstance()
	{
		static T instance;
		return instance;
	}

public:
	Singleton<T>() {}
	~Singleton<T>() {}
	Singleton<T>(const Singleton<T>&) = delete;
	Singleton<T>& operator=(const Singleton<T>&) = delete;

};