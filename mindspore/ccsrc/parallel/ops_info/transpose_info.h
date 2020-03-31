/**
 * Copyright 2019 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MINDSPORE_CCSRC_PARALLEL_OPS_INFO_TRANSPOSE_INFO_H_
#define MINDSPORE_CCSRC_PARALLEL_OPS_INFO_TRANSPOSE_INFO_H_

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

#include "ir/value.h"
#include "parallel/ops_info/operator_info.h"
#include "parallel/strategy.h"

namespace mindspore {
namespace parallel {
/*
 * parallel class for Transpose Primitive
 */
class TransposeInfo : public OperatorInfo {
 public:
  TransposeInfo(const std::string& name, const Shapes& inputs_shape, const Shapes& outputs_shape,
                const PrimitiveAttrs& attrs)
      : OperatorInfo(name, inputs_shape, outputs_shape, attrs) {
    transpose_cost_ptr_ = std::make_shared<ActivationCost>();
  }
  ~TransposeInfo() override = default;
  Status Init(const StrategyPtr& strategy) override;
  Status InitForCostModel(const StrategyPtr& strategy) override;
  Status GenerateStrategies(int32_t stage_id) override;
  Status SetCostUnderStrategy(const StrategyPtr& strategy) override;
  OperatorCostPtr GetOperatorCost() const override { return transpose_cost_ptr_; }

 protected:
  Status CheckStrategy(const StrategyPtr& strategy) override;
  Status InferMirrorOps() override;
  Status InferForwardCommunication() override;
  Status InferTensorInfo() override;
  Status InferDevMatrixShape() override;
  Status InferTensorMap() override;
  Status InferTensorLayout(TensorLayouts* inputs_layout, TensorLayouts* outputs_layout);
  Status GetAttrs() override;
  Strategys GetOutputsStrategy();

 private:
  Status ComputeAxis();
  std::vector<int32_t> axis_v_;
  Dimensions input_strategy_;
  ActivationCostPtr transpose_cost_ptr_;
};
}  // namespace parallel
}  // namespace mindspore

#endif  // MINDSPORE_CCSRC_PARALLEL_OPS_INFO_TRANSPOSE_INFO_H_
