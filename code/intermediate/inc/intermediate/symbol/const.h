/*
 * Copyright (c) 2019 Zachary Stiers
 * License: https://github.com/zstiers/relyst/blob/master/LICENSE
 */

#pragma once

namespace relyst::intermediate::symbol {

enum class TypeKind {
    kInvalid,

    kComponent,
    kFloat,
    kIntegerSigned,
    kIntegerUnsigned,
    kStruct,
    kSurrogate,

    kCount
};

} // namespace relyst::intermediate::symbol