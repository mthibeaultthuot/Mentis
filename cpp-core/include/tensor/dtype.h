#pragma once
#include <cstddef>
#include <iostream>

enum class DType { Float32, Float64, Int32, Int64, Bool };

size_t dtypeSize(DType dtype);
const char *toString(DType dtype);

inline DType dtype_from_string(const std::string &s) {
  if (s == "float32")
    return DType::Float32;
  else if (s == "float64")
    return DType::Float64;
  else if (s == "int32")
    return DType::Int32;
  else if (s == "int64")
    return DType::Float64;
  else if (s == "bool")
    return DType::Bool;
  else
    throw std::invalid_argument("unknown dtype" + s);
}

inline std::string dtype_to_string(DType dtype) {
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
    break;
  }
}
