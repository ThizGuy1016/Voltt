#pragma once

#include "tokenizer.hpp"
#include "astnode.hpp"
//#include "astgen.hpp"

#include "../list.hpp"

namespace Voltt {
namespace Parser {

struct CTX;

auto alloc_node() -> ASTNode::Node*;

auto parse(CTX*) -> const void;

auto parse_toplevel_expr(CTX*) -> const ASTNode::NodePrecision;

/*
 * Expression
*/
auto parse_expr(CTX*) -> const ASTNode::NodePrecision;

/*
 * PrimaryExpression
 *	: Literal
 *	| Parenthasized Expression
 *	;
*/
auto parse_primary_expr(CTX*) -> const ASTNode::NodePrecision;

/*
 * Parenthasized Expression
 *	: '(' Expression ')'
 *	;
*/
auto parse_paren_expr(CTX*) -> const ASTNode::NodePrecision;

/*
 * Literal
 *	: Integer Literal
 *	| Decimal Literal
 *	;
*/
auto parse_literal(CTX*) -> ASTNode::Node*;

/*
 * Type
 *	: Ident -> ...
 *	;
*/
auto parse_type(CTX*) -> const ASTNode::NodePrecision;

/*
 * Literal Numeric
 *	: Integer Literal
 *	;
*/
//auto parse_literal_numeric(CTX*) -> ASTNode::Node*;
auto parse_literal_numeric(CTX*, const bool _dec) -> const ASTNode::NodePrecision; 

/*
 * Ident
 *	;
*/
auto parse_ident(CTX*) -> const ASTNode::NodePrecision;

/*
 * Multiplicative Expression
 *	: Multiplicative Expression Operator Multiplicative Expression -> ...
*/

auto parse_multiplicative_expression(CTX*) -> ASTNode::Node*;

/*
 * Addative Expression
 *  : Multiplicative Expression
 *	| Addative Expression Operator Multiplicative Expression <|> AddativeExpression -> ...
 *	;
*/
auto parse_addative_expr(CTX*) -> const ASTNode::NodePrecision;

/*
 * Variable Declaration
 *	: Variable -> Ident -> Type -> Expression
 *	;
*/ 
auto parse_var_decl(CTX*) -> const ASTNode::NodePrecision;

/*
 * Prototype Argument
 * Ident: Type
*/
auto parse_proto_arg(CTX*) -> ASTNode::Node*;

auto parse_proto(CTX*) -> ASTNode::Node*;

/*
 * Function Declaration
 * : Function '(' ProtoTypeArgument.. ')' -> return {}
*/
auto parse_fn_decl(CTX*) -> ASTNode::Node*;

struct CTX {
	size_t tok_pos;

	std::vector<Tok::Token> tok_buf;
	List<ASTNode::Node> node_pool;

	const char* fname;
	const char* contents;

	CTX(Tokenizer::CTX* _t)
	: tok_pos(0),
		tok_buf(std::move(_t->tok_buf)),
		fname(_t->fname),
		contents(std::move(_t->contents))
	{
		node_pool.resize(tok_buf.size());
	}

	~CTX()
	{
		fname = nullptr;

		std::free((void*)contents);
		contents = nullptr;
	}
};

auto inline curr_t(CTX* _ctx) -> Tok::Token&
{
	ASTNode::NodePrecision node_pos;
	return _ctx->tok_buf[_ctx->tok_pos];
}

auto inline next_t(CTX* _ctx) -> Tok::Token&
{
	return (_ctx->tok_pos+1 >= _ctx->tok_buf.size()) ? curr_t(_ctx) : _ctx->tok_buf[++_ctx->tok_pos]; 
}

} // namespace Parser
} // namespace Voltt
