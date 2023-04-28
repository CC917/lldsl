#include "parser.h"
#include "AST.h"

#include <cstdio>

#define error(...) fprintf(stderr,__VA_ARGS__)

#define ERR error("parser error\n");

namespace
{
	lex* t;

	node* parser_mov()
	{
		return new node(node::node_type::op_mov, nullptr, nullptr);
	}

	node* parser_cp()
	{
		return new node(node::node_type::op_cp, nullptr, nullptr);
	}

	void parser_()
	{
		Token tk = t->getNextToken();
		if (tk.type == Token::token_type::var) {
			node* n = new node(node::node_type::src, nullptr, nullptr);
			n->var_name = tk.name;
			tk = t->getNextToken();
			node* p = nullptr;
			node* q = nullptr;
			if (tk.type == Token::token_type::operator_cp) {
				p = parser_cp();
			}
			else if (tk.type == Token::token_type::operator_mov) {
				p = parser_mov();
			}
			else {
				ERR
			}
			tk = t->getNextToken();
			if (tk.type == Token::token_type::var) {
				q = new node(node::node_type::dst, nullptr, nullptr);
				q->var_name = tk.name;
			}
			else
				ERR;
			p->kid1 = n;
			p->kid2 = q;

			std::cout << "found a cp tree or mov tree\n";

			tree_list::_node[tree_list::index++] = p;
		}
		else {
			ERR;;
		}
	}
}

void parser::do_parser()
{
	std::cout << "\nstart parser\n";
	t = &_lex;
	while (t->get_token_count() != 0)
		parser_();
	std::cout << "\nend parser\n";
}
