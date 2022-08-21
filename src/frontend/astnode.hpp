#pragma once

#include "tok.hpp"

#include <vector>

namespace Voltt {
namespace ASTNode {

using NodePrecision = uint16_t;

enum NodeType : uint8_t {
	TypeVariableDecl,
	TypeExprBinary,
	TypeTy,
	TypeLiteralNumeric,
	TypeLiteralDeciamal,
	TypeIdent,
};

struct Node;

struct NodeVariableDecl {
	bool is_const;

	NodePrecision ident;
	NodePrecision type;
	NodePrecision expr;
};

struct NodeExprBinary {
	Tok::TokID op;
	NodePrecision left;
	NodePrecision right;
};

struct NodeTy {
	std::vector<NodePrecision> ty;
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
	} data;
};

constexpr size_t NODE_SIZE = sizeof(ASTNode::Node);

} // namespace ASTNode
} // namespace Voltt
