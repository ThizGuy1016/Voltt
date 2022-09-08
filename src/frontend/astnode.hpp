#pragma once

#include "../list.hpp"
#include "tok.hpp"

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
	NodePrecision ty;
	NodePrecision next;
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

auto ast_dump_node_ident(std::ostream&, size_t) -> const void;
auto ast_dump_node(std::ostream&, List<Node>&, const NodePrecision _ptr, const size_t) -> const void;


} // namespace ASTNode
} // namespace Voltt
