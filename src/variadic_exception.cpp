#include "variadic_exception.h"

const char* Variadic_exception::what() const noexcept {
	return message_.c_str();
}