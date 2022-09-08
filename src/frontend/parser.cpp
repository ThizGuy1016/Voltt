#include "parser.hpp"

#include "astnode.hpp"
#include "tok.hpp"

namespace Voltt {
namespace Parser {

auto parse(CTX* _ctx) -> const void
{
    for (;;) {

        if (curr_t(_ctx).id == Tok::TokenEndOfFile) return;
        ASTNode::NodePrecision node_ptr = parse_toplevel_expr(_ctx);

        if (node_ptr == 0) return;
        switch (curr_t(_ctx).id) { 
            default: 
                Logger::unhandled_case_err("Expressions must end in a newline");

            case Tok::TokenParenClose:
                Logger::cmperr(
                    Tok::dump_errctx(curr_t(_ctx), _ctx->contents, _ctx->fname),
                    Logger::CompErrID::UNMATCHED_OPEN_PAREN
                );

            case Tok::TokenEndStatement: next_t(_ctx);
        }
    }
}

auto parse_toplevel_expr(CTX* _ctx) -> const ASTNode::NodePrecision
{
    switch (curr_t(_ctx).id) {
        case Tok::TokenEndStatement:
            next_t(_ctx); // consume end of statement
            return parse_toplevel_expr(_ctx);

        case Tok::TokenEndOfFile: return 0;
        
        case Tok::TokenIdent: return parse_var_decl(_ctx);

        default:
            Logger::cmperr(
                Tok::dump_errctx(curr_t(_ctx), _ctx->contents, _ctx->fname),
                Logger::CompErrID::INVALID_TOPLEVEL_EXPR
        );
    }

    Logger::unreachable_err();
    return 0;
}

auto parse_primary_expr(CTX* _ctx) -> const ASTNode::NodePrecision
{
    switch (curr_t(_ctx).id) {
        case Tok::TokenParenOpen:
            return parse_paren_expr(_ctx);

        case Tok::TokenIdent:
            return parse_ident(_ctx);
        
        case Tok::TokenLiteralNumeric:
            return parse_literal_numeric(_ctx, false);

        case Tok::TokenLiteralDecimal:
            return parse_literal_numeric(_ctx, true);

        default:
            Logger::cmperr(
                Tok::dump_errctx(curr_t(_ctx), _ctx->contents, _ctx->fname),
                Logger::CompErrID::EXPECTED_EXPRESSION
            );
            return 0;
    }
}

auto parse_expr(CTX* _ctx) -> const ASTNode::NodePrecision
{
    return parse_addative_expr(_ctx);
}

auto parse_paren_expr(CTX* _ctx) -> const ASTNode::NodePrecision
{
    next_t(_ctx); // consume '('
    switch (curr_t(_ctx).id) {
        case Tok::TokenParenClose: // empty paren case
            next_t(_ctx); // consume ')'
            return parse_expr(_ctx);
        
        default:
            ASTNode::NodePrecision expr = parse_expr(_ctx);
            switch (curr_t(_ctx).id) {
                default:
                    Logger::cmperr(
                        Tok::dump_errctx(curr_t(_ctx), _ctx->contents, _ctx->fname),
                        Logger::CompErrID::UNMATCHED_CLOSE_PAREN
                    );
                    return 0;

                case Tok::TokenParenClose: next_t(_ctx); // consume ')'
            }
            return expr;
    }
}

auto parse_var_decl(CTX* _ctx) -> const ASTNode::NodePrecision
{
    _ctx->node_pool.push(std::move(ASTNode::Node{}));
    for ( const auto& node : _ctx->node_pool ) std::cout << std::to_string(node.type) << std::endl;
    ASTNode::Node var = _ctx->node_pool.last();
    
    var.type = ASTNode::TypeVariableDecl;
    var.tok = curr_t(_ctx);
    var.data.variable_decl_data.ident = parse_ident(_ctx);

    switch (curr_t(_ctx).id) {
        default:
            Logger::cmperr(
                Tok::dump_errctx(curr_t(_ctx), _ctx->contents, _ctx->fname),
                Logger::CompErrID::EXPECTED_EXPRESSION
            );
            return 0;

        case Tok::TokenColonSymbol:
            next_t(_ctx);
            var.data.variable_decl_data.type = parse_type(_ctx);

            switch (curr_t(_ctx).id) {
                default:
                    Logger::cmperr(
                        Tok::dump_errctx(curr_t(_ctx), _ctx->contents, _ctx->fname),
                        Logger::CompErrID::EXPECTED_EQ
                    );
                    return 0;

                case Tok::TokenEqSymbol:
                    var.data.variable_decl_data.is_const = false;
                    break;

                case Tok::TokenColonSymbol:
                    var.data.variable_decl_data.is_const = true;
                    break;
            }

            next_t(_ctx);
            break;
    
        case Tok::TokenColonInferMut:
            var.data.variable_decl_data.is_const = true;
            var.data.variable_decl_data.type = 0;
            next_t(_ctx);
            break;

        case Tok::TokenColonInferConst:
            var.data.variable_decl_data.is_const = false;
            var.data.variable_decl_data.type = 0;
            next_t(_ctx);
            break;
    }

    var.data.variable_decl_data.expr = parse_expr(_ctx);

    return _ctx->node_pool.size;
}

auto parse_multiplicative_expr(CTX* _ctx) -> const ASTNode::NodePrecision 
{
    ASTNode::NodePrecision left = parse_primary_expr(_ctx);

    for (;;) {
        const Tok::Token op = curr_t(_ctx);
        switch (op.id) {
            default: 
                goto multiplicative_recurse_end;
            
            case Tok::TokenBinOpMul:
            case Tok::TokenBinOpDiv:
                next_t(_ctx); // consume operator

                ASTNode::NodePrecision right = parse_primary_expr(_ctx);
                _ctx->node_pool.push(std::move(ASTNode::Node{}));
                ASTNode::Node new_left = _ctx->node_pool.last();

                new_left.type = ASTNode::TypeExprBinary;
                new_left.tok = std::move(curr_t(_ctx));

                new_left.data.expr_binary_data.op = op.id;
                new_left.data.expr_binary_data.left = left;
                new_left.data.expr_binary_data.right = right; 
        
                left = _ctx->node_pool.size;
        }
    }

    multiplicative_recurse_end:

    return left; 
}

auto parse_addative_expr(CTX* _ctx) -> const ASTNode::NodePrecision 
{
    ASTNode::NodePrecision left = parse_multiplicative_expr(_ctx);

    for (;;) {
        const Tok::Token op = curr_t(_ctx);
        switch (op.id) {
            default: 
                next_t(_ctx);
                goto multiplicative_recurse_end;
            
            case Tok::TokenBinOpAdd:
            case Tok::TokenBinOpSub:
                next_t(_ctx); // consume operator

                ASTNode::NodePrecision right = parse_multiplicative_expr(_ctx);
                _ctx->node_pool.push(ASTNode::Node{});
                ASTNode::Node new_left = _ctx->node_pool.last();

                new_left.type = ASTNode::TypeExprBinary;
                new_left.tok = std::move(curr_t(_ctx));

                new_left.data.expr_binary_data.op = op.id;
                new_left.data.expr_binary_data.left = left;
                new_left.data.expr_binary_data.right = right; 
        
                left = _ctx->node_pool.size;
        }
    }

    multiplicative_recurse_end:
    
    return left; 
}

auto parse_literal_numeric(CTX* _ctx, const bool _dec = false) -> const ASTNode::NodePrecision
{
    char const* num_lit =  Tok::to_str(curr_t(_ctx), _ctx->contents);

    _ctx->node_pool.push(
        ASTNode::Node{
            .type = ASTNode::TypeLiteralNumeric,
            .tok = curr_t(_ctx),
        }
    );

    switch ((size_t)_dec) {
        case 0: 
            _ctx->node_pool.last().data.literal_numeric_data.value = std::stoi(num_lit);
            break;
        default:
            _ctx->node_pool.last().data.literal_numeric_data.value = std::stod(num_lit);
            _ctx->node_pool.last().type = ASTNode::TypeLiteralDeciamal;
    }

    std::free((char*)num_lit);

    return _ctx->node_pool.size;
}

auto parse_type(CTX* _ctx) -> const ASTNode::NodePrecision
{
    switch (curr_t(_ctx).id) {
        default:
            Logger::cmperr(
                Tok::dump_errctx(curr_t(_ctx), _ctx->contents, _ctx->fname),
                Logger::CompErrID::INVALID_TYPE_IDENTIFIER
            );
            return 0;

        case VTYPES_CASE:
        case Tok::TokenIdent:
            _ctx->node_pool.push(std::move(ASTNode::Node{}));
            ASTNode::Node type = _ctx->node_pool.last();
            
            type.type = ASTNode::TypeTy;
            type.tok = std::move(curr_t(_ctx));
            type.data.ty_data.ty = parse_ident(_ctx);

            // TODO 
            type.data.ty_data.next = 0;

            return _ctx->node_pool.size;
    }
    Logger::unreachable_err();
    return 0;
}

auto parse_ident(CTX* _ctx) -> const ASTNode::NodePrecision
{
    _ctx->node_pool.push(
        ASTNode::Node{
            .type = ASTNode::TypeIdent,
            .tok = curr_t(_ctx),
        }
    );

    _ctx->node_pool.last().data.ident_data.raw = Tok::to_str(curr_t(_ctx), _ctx->contents);

    next_t(_ctx);

    return _ctx->node_pool.size;
}

} // namespace Parser
} // namespace Voltt