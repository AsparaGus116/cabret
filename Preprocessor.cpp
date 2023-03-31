#include "Preprocessor.h"

Preprocessor::Preprocessor()
{
}

void Preprocessor::preprocess(std::string& buffer)
{
	std::regex define("#define\\s+(\\w+)\n?", icase);
	std::regex undef("#undef\\s+(\\w+)\n?", icase);
	std::regex whitespace("[\\s]+");
	std::regex newline_whitespace("\\n+[\\s]*");
	std::regex comments("(\\/\\/)(.)+\\n");
	std::regex multiline_comments("\\/\\*((.)|(\\n))*?(\\*\\/)");

	buffer = std::regex_replace(buffer, multiline_comments, "");
	buffer = std::regex_replace(buffer, comments, "\n");
	buffer = std::regex_replace(buffer, define, def_delim + "$1;");
	// TODO: Change define and undefine characters (extended char set?), maybe set up an enum
	// TODO: Create separate preprocessor class
	buffer = std::regex_replace(buffer, undef, undef_delim + "$1;");
	buffer = std::regex_replace(buffer, whitespace, " ");
	buffer = std::regex_replace(buffer, newline_whitespace, "\n");
}
