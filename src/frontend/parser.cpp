#include "parser.hpp"
#include "astnode.hpp"

namespace Voltt {
namespace Parser {

auto parse_literal_numeric(CTX* _ctx) -> const bool 
{
    _ctx->node_pool.emplace_back(std::move((ASTNode::Node*)std::malloc(ASTNode::NODE_SIZE)));

    return false;
}

} // namespace Parser
} // namespace Voltt