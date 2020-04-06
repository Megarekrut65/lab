#pragma once
#include "my_correct_read.h"
#include <string>

namespace correct
{
	double read_double(const std::string&);
	std::size_t read_size_t(const std::string&);
	unsigned read_unsigned(const std::string&);
	long read_long(const std::string&);
	int read_int(const std::string&);
}