#include "tensor/dtype.h"
#include <cstddef>

size_t dtypeSize(DType dtype) {
  switch (dtype) {
  case DType::Float32:
    return 4;
  case DType::Float64:
    return 8;
  case DType::Int32:
    return 4;
  case DType::Int64:
    return 8;
  case DType::Bool:
    return 1;
  default:
    return 0;
  }
}

const char *toString(DType dtype) {
  switch (dtype) {
  case DType::Float32:
    return "float32";
  case DType::Float64:
    return "float64";
  case DType::Int32:
    return "int32";
  case DType::Int64:
    return "int64";
  case DType::Bool:
    return "bool";
  default:
    return "unknown";
  }
}
