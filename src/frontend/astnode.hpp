#pragma once

#include "tok.hpp"

#include <vector>

namespace Voltt {
namespace ASTNode {

enum NodeType : uint8_t {
	TypeStatement,
	TypeVariableDecl,
	TypeFunctionDecl,
	TypePrototype,
	TypePrototypeArg,
	TypeExprBinary,
	TypeTy,
	TypeLiteralNumeric,
	TypeLiteralDeciamal,
	TypeIdent,
};

struct Node;

struct NodeStatement {
	Node* expr;
};

struct NodeVariableDecl {
	bool is_const;

	Node* ident;
	Node* type;
	Node* expr;
};

struct NodePrototypeArg {
	char const* raw;
	Node* type;
};

struct NodeProtype {
	std::vector<Node*> args;
};

struct NodeFunctionDecl {
	Node* name;
	Node* proto;
	Node* ret;
	Node* body;
};

struct NodeExprBinary {
	Tok::TokID op;
	Node* left;
	Node* right;
};

struct NodeTy {
	std::vector<Node*> ty;
};

struct NodeLiteralNumeric {
	int32_t value;
};

struct NodeLiteralDecimal {
	double value;
};

struct NodeIdent {
	char const* raw;
};

struct Node {
	NodeType type;
	Tok::Token tok;

	union {
		NodeLiteralNumeric literal_numeric_data;
		NodeLiteralDecimal literal_decimal_data;
		NodeExprBinary expr_binary_data;
		NodeTy ty_data;
		NodeIdent ident_data;
		NodeVariableDecl variable_decl_data;
		NodePrototypeArg prototype_arg_data;
		NodeProtype prototype_data;
		NodeFunctionDecl function_decl_data;
	} data;
};

} // namespace ASTNode
} // namespace Voltt
