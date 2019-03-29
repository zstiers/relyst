/*
 * Copyright (c) 2019 Zachary Stiers
 * License: https://github.com/zstiers/relyst/blob/master/LICENSE
 */

#pragma once

#ifndef RELYST_AST_FORCE_NODE_POLYMORPHISM
#define RELYST_AST_FORCE_NODE_POLYMORPHISM RELYST_DEBUG
#endif

namespace relyst::intermediate::ast {

#define RELYST_NODE_KIND_SECTION_BEGIN(name) k##name##First, k##name##Before = k##name##First - 1,
#define RELYST_NODE_KIND_SECTION_END(name)   k##name##After, k##name##Last   = k##name##After - 1,

enum class NodeKind {
    kInvalid,

    RELYST_NODE_KIND_SECTION_BEGIN(Binary)
    kAssign,

    kAdd,
    kSubtract,
    kDivide,
    kMultiply,
    kModulus,

    kAddAssign,
    kSubtractAssign,
    kDivideAssign,
    kMultiplyAssign,
    kModulusAssign,

    kLogicalEqual,
    kLogicalNotEqual,
    kLogicalLess,
    kLogicalLessEqual,
    kLogicalGreater,
    kLogicalGreaterEqual,

    kLogicalAnd,
    kLogicalOr,

    kLogicalAndAssign,
    kLogicalOrAssign,

    kBitwiseAnd,
    kBitwiseOr,
    kBitwiseXor,
    kBitwiseLeftShift,
    kBitwiseRightShift,

    kBitwiseAndAssign,
    kBitwiseOrAssign,
    kBitwiseXorAssign,
    kBitwiseLeftShiftAssign,
    kBitwiseRightShiftAssign,
    RELYST_NODE_KIND_SECTION_END(Binary)

    RELYST_NODE_KIND_SECTION_BEGIN(Function)
    kEntry,
    kFork,
    kFunctionBasic,
    RELYST_NODE_KIND_SECTION_END(Function)

    RELYST_NODE_KIND_SECTION_BEGIN(Scope)
    kNamespace,
    kRoot,
    RELYST_NODE_KIND_SECTION_END(Scope)

    RELYST_NODE_KIND_SECTION_BEGIN(Type)
    kComponent,
    kStruct,
    RELYST_NODE_KIND_SECTION_END(Type)

    RELYST_NODE_KIND_SECTION_BEGIN(Unary)
    kDecrementPre,
    kDecrementPost,
    kIncrementPre,
    kIncrementPost,

    kLogicalNot,
    kBitwiseNot,

    kAddress,
    kPlus,
    kNegate,

    kMemberAccess,
    RELYST_NODE_KIND_SECTION_END(Unary)

    RELYST_NODE_KIND_SECTION_BEGIN(Variable)
    kConst,
    kDupe,
    kRef,
    RELYST_NODE_KIND_SECTION_END(Variable)

    kCount
};

#undef RELYST_NODE_KIND_SECTION_BEGIN
#undef RELYST_NODE_KIND_SECTION_END

} // namespace relyst::intermediate::ast