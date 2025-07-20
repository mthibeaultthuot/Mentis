#pragma once
#include <iostream>

enum class OPS { Input, MatMul, Add, Elu };

inline OPS ops_from_string(const std::string &s) {
  if (s == "input")
    return OPS::Input;
  else if (s == "matmul")
    return OPS::MatMul;
  else if (s == "add")
    return OPS::Add;
  else if (s == "elu")
    return OPS::Elu;
  else
    throw std::invalid_argument("unknown ops" + s);
}

inline std::string ops_to_string(OPS op) {
  switch (op) {
  case OPS::Input:
    return "input";
  case OPS::MatMul:
    return "matmul";
  case OPS::Add:
    return "add";
  case OPS::Elu:
    return "elu";
  default:
    return "unknown";
  }
}
