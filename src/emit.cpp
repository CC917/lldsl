#include "emit.h"

#include "AST.h"

#define ERR fprintf(stderr,"emit error\n")

#define MAX_LINE 96

static char buffer[MAX_LINE];

void emit_code()
{
	FILE* fp = fopen("output.sh", "w");
	if (fp == NULL) {
		std::cout << "open file error\n";
	}

	fputs("#!/bin/bash\n\n", fp);
	fputs("function __copy_fun()\n{\n", fp);

	for (int i = 0; i < tree_list::index; i++) {
		std::cout << "start emit code\n";
		
		node* p = tree_list::_node[i];

		std::cout << static_cast<int>(p->type);

		if (p->type == node::node_type::op_cp) {
			sprintf(buffer, "\tcp ${%s}", p->kid1->var_name.c_str());
			fputs(buffer, fp);
			sprintf(buffer, " ,${%s}\n", p->kid2->var_name.c_str());
			fputs(buffer, fp);
		}
		else if (p->type == node::node_type::op_mov) {
			sprintf(buffer, "\tmv ${%s}", p->kid1->var_name.c_str());
			fputs(buffer, fp);
			sprintf(buffer, " ,${%s}\n", p->kid2->var_name.c_str());
			fputs(buffer, fp);
		}
		else
			ERR;
	}

	fputs("}\n", fp);
	fclose(fp);
}
