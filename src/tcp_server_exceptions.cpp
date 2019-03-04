#include "tcp_server_exceptions.h"

const char* Timeout_error::what() const noexcept {
	return "Connection timed out";
}

const char* Client_disconnected_error::what() const noexcept {
	return "Client disconnected";
}

const char* Send_error::what() const noexcept {
	return "Error while sending data to client";
}

