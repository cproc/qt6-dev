// Copyright 2022 The Tint Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "src/tint/ast/enable.h"

#include "src/tint/program_builder.h"

TINT_INSTANTIATE_TYPEINFO(tint::ast::Enable);

namespace tint::ast {

Enable::Enable(ProgramID pid, NodeID nid, const Source& src, builtin::Extension ext)
    : Base(pid, nid, src), extension(ext) {}

Enable::Enable(Enable&&) = default;

Enable::~Enable() = default;

const Enable* Enable::Clone(CloneContext* ctx) const {
    auto src = ctx->Clone(source);
    return ctx->dst->create<Enable>(src, extension);
}
}  // namespace tint::ast
