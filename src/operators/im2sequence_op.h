/* Copyright (c) 2018 PaddlePaddle Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#pragma once

#include "framework/operator.h"
#include "operators/kernel/im2sequence_kernel.h"
#include <operators/op_param.h>

namespace paddle_mobile {
namespace operators {

using namespace framework;

template <typename DeviceType, typename T>
class Im2SequenceOp : public framework::OperatorWithKernel<DeviceType> {
 public:
  Im2SequenceOp(const std::string &type, const VariableNameMap &inputs,
                const VariableNameMap &outputs, const framework::AttributeMap &attrs,
                std::shared_ptr<framework::Scope> scope)
      : framework::OperatorWithKernel<DeviceType>(type, inputs, outputs, attrs,
                                                  scope),
        param_(inputs, outputs, attrs, *scope) {}

  using framework::OperatorWithKernel<DeviceType>::OperatorWithKernel;
  void InferShape() const override;

  void RunImpl() const {
    operators::Im2SequenceKernel<DeviceType, T> kernel;
    kernel.Compute(param_);
    this->ClearVariables({"Input"});
  }

 private:
  Im2SequenceParam param_;
};

}  // namespace operators
}  // namespace paddle_mobile
