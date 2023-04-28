#ifndef APP_H
#define APP_H

#include "lex.h"

class app
{
public:
	virtual int run() = 0;
};


class compiler : public app
{
private:
	virtual lex& scan_stage(std::string source_path) = 0;
	virtual int parser_stage(lex& tokenlist) = 0;
};


#endif