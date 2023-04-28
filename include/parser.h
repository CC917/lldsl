#ifndef PARSER_H
#define PARSER_G

#include "lex.h"

class parser
{
public:
	parser(lex& lex) : _lex(lex)
	{
		//std::cout << lex.get_token_list().size() << "???" << std::endl;
	}

	void do_parser();
private:
	lex& _lex;
};

#endif
