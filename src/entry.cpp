#include "frontend/astnode.hpp"
#include "frontend/parser.hpp"
#include "frontend/tok.hpp"
#include "logger.hpp"

#include <iostream>
#include <cstdint>

auto main() -> int32_t
{
	using namespace Voltt;

	Tokenizer::CTX tokctx("test.vlt");
	Tokenizer::tokenize(&tokctx);

	List<int> numbers{};
	numbers.push(10);

	for ( const auto& num : numbers ) std::cout << num << std::endl;

	//Parser::CTX parctx(&tokctx);
	//Parser::parse(&parctx);

	//ASTNode::ast_dump_node(std::cout, parctx.node_pool, 0, 0);

	return 0;
}
