#pragma once
#include <iostream>
#include <ops/ops.h>
#include <pybind11/pybind11.h>
#include <string>
#include <tensor/dtype.h>
#include <vector>

class LazyNode {
public:
  LazyNode(int id, OPS ops, DType dtype, std::vector<int> shape,
           std::vector<std::string> inputs, std::vector<std::string> outputs);
  ~LazyNode();
  std::string addInput(std::string input);
  std::string addOutput(std::string output);

  friend std::ostream &operator<<(std::ostream &os, const LazyNode &node);

private:
  int id_;
  OPS ops_;
  DType dtype_;
  std::vector<int> shape_;
  std::vector<std::string> inputs_;
  std::vector<std::string> outputs_;
};

class LazyGraph {
public:
  LazyGraph(int id);
  ~LazyGraph();
  LazyNode addNode(LazyNode node);

  friend std::ostream &operator<<(std::ostream &os, const LazyGraph &graph);

private:
  int id_;
  std::vector<LazyNode> nodes_;
};
