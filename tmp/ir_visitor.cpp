#include "ir_visitor.hpp"

namespace Voltt {
namespace IRVisitor {

std::unique_ptr<llvm::LLVMContext> CTX = std::make_unique<llvm::LLVMContext>();
std::unique_ptr<llvm::Module> MOD = std::make_unique<llvm::Module>("TMP", *CTX);
std::unique_ptr<llvm::IRBuilder<>> BUILD = std::make_unique<llvm::IRBuilder<>>(*CTX);
std::map<ASTNode::Node*, llvm::Value*> GlobalValues;

auto ir_gen(ASTNode::Node* _node) -> llvm::Value*
{
    switch (_node->type) {
        default: Logger::unhandled_case_err("CODEGEN: Invalid node to codegen");

        case ASTNode::TypeExprBinary:
            return ir_binary_expr_gen(&_node->data.expr_binary_data);

        case ASTNode::TypeLiteralDeciamal:
            return ir_literal_decimal_gen(&_node->data.literal_decimal_data);

        case ASTNode::TypeLiteralNumeric:
            return ir_literal_numeric_gen(&_node->data.literal_numeric_data);
    }
}

auto ir_binary_expr_gen(ASTNode::NodeExprBinary *_node) -> llvm::Value*
{
    llvm::Value* Left = ir_gen(_node->left);
    llvm::Value* Right = ir_gen(_node->right);
    if (!Left || !Right) return nullptr;

    switch (_node->op) {
        default: Logger::unhandled_case_err("CODEGEN: Expected a binary expression");

        case Tok::TokenBinOpAdd:
            return BUILD->CreateFAdd(Left, Right, "addtmp");
        
        case Tok::TokenBinOpSub:
            return BUILD->CreateFSub(Left, Right, "subtmp");

        case Tok::TokenBinOpMul:
            return BUILD->CreateFMul(Left, Right, "multmp");

        case Tok::TokenBinOpDiv:
            return BUILD->CreateFDiv(Left, Right, "divtmp");
    }
}

auto ir_literal_numeric_gen(ASTNode::NodeLiteralNumeric* _node) -> llvm::Value*
{
    return llvm::ConstantInt::get(
        *CTX,
        llvm::APInt(32, _node->value, false)
    );
}

auto ir_literal_decimal_gen(ASTNode::NodeLiteralDecimal* _node) -> llvm::Value*
{
    return llvm::ConstantFP::get(
        *CTX,
        llvm::APFloat(_node->value)
    );
}

} // namespace IRVisitor
} // namespace Voltt