#include "frontend/astnode.hpp"
#include "frontend/parser.hpp"
#include "frontend/tok.hpp"

#include <iostream>
#include <cstdint>

auto main() -> int32_t
{
	using namespace Voltt;

	Tokenizer::CTX tokctx("test.vlt");
	Tokenizer::tokenize(&tokctx);

	Parser::CTX parctx(&tokctx);
	Parser::parse_literal_numeric(&parctx);

	return 0;
}
