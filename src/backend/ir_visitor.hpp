#pragma once

#include "../frontend/astnode.hpp"

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"
#include "llvm/Transforms/Utils.h"

#include <memory>
#include <string>
#include <map>

namespace Voltt {
namespace IRVisitor {

auto ir_gen(ASTNode::Node* _node) -> llvm::Value*;
auto ir_binary_expr_gen(ASTNode::NodeExprBinary* _node) -> llvm::Value*;
auto ir_literal_numeric_gen(ASTNode::NodeLiteralNumeric* _node) -> llvm::Value*;
auto ir_literal_decimal_gen(ASTNode::NodeLiteralDecimal* _node) -> llvm::Value*;

} // namespace IRVisitor
} // namespace Voltt
