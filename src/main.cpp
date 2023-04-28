#include "file_if.h"
#include "lex.h"
#include "app.h"
#include "parser.h"
#include "emit.h"

#include <iostream>

using namespace std;

class compilerImpl : public compiler
{
private:
	lex& scan_stage(std::string source_path) override
	{
		file_if interface(source_path.c_str());

		auto& reader = interface.get_compoment<file_reader>();

		static lex lx(reader);

		lx.do_lex();
		//std::cout << lx.get_token_list().size() << std::endl;
		lx.dump_token();

		return lx;
	}

	int parser_stage(lex& lex) override
	{
		parser psr(lex);
		psr.do_parser();
		return 0;
	}

	void emit_stage()
	{
		emit_code();
	}

public:
	int run() override
	{
		auto& ll = scan_stage("test.pl");
		//std::cout << ll.get_token_list().size() << "??" << std::endl;
		parser_stage(ll);

		emit_stage();

		return 0;
	}
};

int main()
{
	compiler *c = new compilerImpl();
	return c->run();
}
