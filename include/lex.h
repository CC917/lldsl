#ifndef LEX_H
#define LEX_H

#include "file_if.h"
#include <vector>
#include <list>
#include <iostream>

struct Token;

using TokenList = std::list<Token>;

struct Token
{
	enum class token_type {
		operator_mov = 1,
		operator_cp = 2,
		var = 3
	};
	token_type type;

	std::string name;
	
	Token(token_type ty) : type(ty) {}
	Token(token_type ty,std::string ne) : type(ty),name(ne) {}
};

struct token_tool
{
	static bool check_dig_alpha(char c)
	{
		return isdigit(c) || isalpha(c);
	}
};

class lex
{
public:
	lex(file_reader& rd) :_rd(rd) {}

	Token getNextToken();

	TokenList& get_token_list()
	{
		return token_list;
	}

	~lex()
	{
		std::cout << "lex haved destoryed" << std::endl;
	}

	void do_lex()
	{
		char c;
		while ((c = _rd.read()) != file_reader::end_of_file) {
			if (c == '#') {
				//igore comments
				while (c = _rd.read() != '\n')
					continue;
			}
			if (c == '-') {
				c = _rd.read();
				if (c == '>')
				{
					token_list.emplace_back(Token::token_type::operator_cp);
				}
				else
				{
					_rd.reback();
				}
			}
			else if (c == '=') {
				c = _rd.read();
				if (c == '>')
				{
					token_list.emplace_back(Token::token_type::operator_mov);
				}
				else
				{
					_rd.reback();
				}
			}
			else if (token_tool::check_dig_alpha(c)) {
				std::string name;
				name.push_back(c);
				c = _rd.read();
				while (token_tool::check_dig_alpha(c)) {
					name.push_back(c);
					c = _rd.read();
				}
				_rd.reback();
				token_list.emplace_back(Token::token_type::var, name);
			}
			else
				;
		}
	}

	std::size_t get_token_count() const
	{
		return token_list.size();
	}

	void dump_token()
	{
		int i = 0;
		for (auto c = token_list.begin(); c != token_list.end(); c++) {
			std::cout << "TOKEN_" << i++ << ":" << static_cast<int>(c->type)
				<< " " << c->name << std::endl;
		}
	}

private:
	file_reader& _rd;
	TokenList token_list;
};


#endif
