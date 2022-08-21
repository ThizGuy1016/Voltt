#include "frontend/astnode.hpp"
#include "frontend/parser.hpp"
#include "frontend/astgen.hpp"
#include "backend/ir_visitor.hpp"
#include "frontend/tok.hpp"

#include <iostream>
#include <cstdint>

auto main() -> int32_t
{
	using namespace Voltt;

	Tokenizer::CTX tokctx("test.vlt");
	Tokenizer::tokenize(&tokctx);

	Parser::CTX parctx(&tokctx);
	auto node = Parser::parse_proto(&parctx);
	
	//for ( const ASTNode::Node* node : parctx.body ) ASTGen::ast_dump_node(std::cout, node);

	/*
	auto left = Parser::alloc_node();
	left->type = ASTNode::TypeLiteralDeciamal;
	left->data.literal_decimal_data.value = 34.0;

	auto right = Parser::alloc_node();
	right->type = ASTNode::TypeLiteralDeciamal;
	right->data.literal_decimal_data.value = 35.0;

	auto bin = Parser::alloc_node();
	bin->type = ASTNode::TypeExprBinary;
	bin->data.expr_binary_data.op = Tok::TokenBinOpAdd;
	bin->data.expr_binary_data.left = left;
	bin->data.expr_binary_data.right = right;

	IRVisitor::ir_gen(bin)->print(llvm::errs());
	*/

	return 0;
}
