// Copyright 2019 Amazon Inc. or its affiliates. All Rights Reserved.
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
#include "error_feedback.h"

namespace byteps {
namespace common {
namespace compressor {

void ErrorFeedback::Compress(tensor_t grad, tensor_t& compressed) {
  // before: grad += error
  UpdateGradient(grad);

  // TODO: look strange
  compressed.data = _error.get();
  // compress
  _cptr->Compress(grad, compressed);

  UpdateError(grad, compressed);
}

void ErrorFeedback::Decompress(tensor_t compressed, tensor_t& decompressed) {
  _cptr->Decompress(compressed, decompressed);
}

void ErrorFeedback::UpdateError(tensor_t corrected, tensor_t compressed) {
  tensor_t error{_error.get(), _size, corrected.dtype};
  _cptr->FastUpdateError(error, corrected, compressed);
}

}  // namespace compressor
}  // namespace common
}  // namespace byteps