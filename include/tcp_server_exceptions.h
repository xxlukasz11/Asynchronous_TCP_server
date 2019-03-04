#ifndef _CUSTOM_EXCEPTIONS_H_
#define _CUSTOM_EXCEPTIONS_H_

#include "variadic_exception.h"

class Init_server_error : public Variadic_exception {
	using Variadic_exception::Variadic_exception;
};

class Sockopt_error : public Variadic_exception {
	using Variadic_exception::Variadic_exception;
};

class Timeout_error : public std::exception {
public:
	const char* what() const noexcept override;
};

class Client_disconnected_error : public std::exception {
public:
	const char* what() const noexcept override;
};

class Send_error : public std::exception {
public:
	const char* what() const noexcept override;
};

#endif
