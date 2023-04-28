#ifndef AST_H
#define AST_H
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include "lex.h"

struct node
{
	enum class node_type {
		src = 1,
		op_mov = 2,
		op_cp = 3,
		dst = 4
	};

	node(node_type t, node* k1, node* k2) : type(t), kid1(k1), kid2(k2)
	{

	}

	node_type type;

	node* kid1;
	node* kid2;

	std::string var_name;
};

struct tree_list
{
	static node* _node[1024];
	static int index;
};

#endif