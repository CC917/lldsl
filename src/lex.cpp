#include "lex.h"

Token lex::getNextToken()
{
	//std::cout << token_list.size();
	Token c = token_list.front();
	token_list.pop_front();
	return c;
}

