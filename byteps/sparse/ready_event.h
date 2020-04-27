// Copyright 2020 Bytedance Inc. All Rights Reserved.
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
// =============================================================================

#ifndef BYTEPS_SPARSE_READY_EVENT_H
#define BYTEPS_SPARSE_READY_EVENT_H

#if HAVE_CUDA
#include "cuda_runtime.h"
#endif

#include <memory>

#include "../common/common.h"
#include "../common/logging.h"

namespace byteps {
namespace sparse {

using namespace byteps::common;

#if HAVE_CUDA
class GeneralReadyEvent : public ReadyEvent {
 public:
  GeneralReadyEvent(int device, cudaStream_t stream);
  ~GeneralReadyEvent();
  virtual bool Ready() const override;

 private:
  int device_ = CPU_DEVICE_ID;
  cudaEvent_t cuda_event_ = nullptr;
  cudaStream_t stream_;
};
#endif

std::shared_ptr<ReadyEvent> RecordReadyEvent(int device, cudaStream_t stream);

}  // namespace sparse
}  // namespace byteps

#endif  // BYTEPS_SPARSE_READY_EVENT_H
