#include "astnode.hpp"
#include "tok.hpp"

namespace Voltt {
namespace ASTNode {
 
auto ast_dump_node_ident(std::ostream& _os, size_t _level) -> const void
{
    _level *= 2;
    while (_level--) _os.write(" ", 1);
}

auto ast_dump_node(std::ostream& _os, List<Node>& _pool, const NodePrecision _ptr, const size_t _level) -> const void
{
    Node curr_node = _pool[_ptr];
    switch (curr_node.type) {
        default: Logger::unhandled_case_err("Invalid Node to traverse.");

        case TypeExprBinary:
            ast_dump_node_ident(_os, _level);
            _os << " └─| Binary Expression\n";

            ast_dump_node_ident(_os, _level+1);
            _os << "   > op: " << std::to_string(curr_node.data.expr_binary_data.op) << '\n';

            ast_dump_node(_os, _pool, curr_node.data.expr_binary_data.left, _level+1);
            ast_dump_node(_os, _pool, curr_node.data.expr_binary_data.right, _level+1);

            return;
    
        case TypeLiteralNumeric:
            ast_dump_node_ident(_os, _level);
            _os << "   | Literal Numeric\n";

            ast_dump_node_ident(_os, _level+1);
            _os << "   > value: " << curr_node.data.literal_numeric_data.value << '\n';
    
            return;

        case TypeLiteralDeciamal:
            ast_dump_node_ident(_os, _level);
            _os << "   | Literal Decimal\n";

            ast_dump_node_ident(_os, _level+1);
            _os << "   > value: " << curr_node.data.literal_decimal_data.value << '\n';

            return;

        case TypeIdent:
            ast_dump_node_ident(_os, _level);
            _os << "   | Ident\n";

            ast_dump_node_ident(_os, _level+1);
            _os << "   > raw: " << curr_node.data.ident_data.raw << '\n';

            return;

        case TypeTy: // TODO

            ast_dump_node(_os, _pool, curr_node.data.ty_data.ty, _level+1);

            return;
    
        case TypeVariableDecl:
            ast_dump_node_ident(_os, _level);
            _os << "   | Variable\n";

            ast_dump_node_ident(_os, _level+1);
            _os << "   | Const\n";
            ast_dump_node_ident(_os, _level+2);
            _os << "   > bool: " << curr_node.data.variable_decl_data.is_const << '\n';

            ast_dump_node(_os, _pool, curr_node.data.variable_decl_data.ident, _level+1);

            ast_dump_node_ident(_os, _level+1);
            _os << "   | Type\n";

            ast_dump_node(_os, _pool, curr_node.data.variable_decl_data.type, _level+1);
            ast_dump_node(_os, _pool, curr_node.data.variable_decl_data.expr, _level+1);

            return;
    }

    Logger::unreachable_err();
}

}
}