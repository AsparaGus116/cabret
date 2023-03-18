#pragma once
#include <string>
#include <regex>

class Preprocessor
{
private:
	std::regex_constants::syntax_option_type icase{ std::regex_constants::syntax_option_type::icase };

	const std::string def_delim{ "|" };
	const std::string undef_delim{ "%" };
public:
	Preprocessor();

	void preprocess(std::string& buffer);
};

