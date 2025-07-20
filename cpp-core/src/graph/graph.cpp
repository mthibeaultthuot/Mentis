

#include "graph/graph.h"
#include "graph_generated.h"
#include <iostream>

LazyNode::LazyNode(int id, OPS ops, DType dtype, std::vector<int> shape,
                   std::vector<std::string> inputs,
                   std::vector<std::string> outputs)
    : id_(id), ops_(ops), dtype_(dtype), shape_(shape), inputs_(inputs),
      outputs_(outputs) {}

std::string LazyNode::addInput(std::string input) {
  inputs_.push_back(input);
  return input;
}

LazyNode::~LazyNode() = default;

std::string LazyNode::addOutput(std::string output) {
  outputs_.push_back(output);
  return output;
}

LazyGraph::LazyGraph(int id) : id_(id) {}

LazyGraph::~LazyGraph() = default;

std::ostream &operator<<(std::ostream &os, const LazyNode &node) {
  os << "LazyNode(id=" << node.id_ << ", ops=" << ops_to_string(node.ops_)
     << ", dtype=" << static_cast<int>(node.dtype_) << ", shape=[";
  for (const auto &dim : node.shape_)
    os << dim << ",";
  os << "], inputs=[";
  for (const auto &in : node.inputs_)
    os << in << ",";
  os << "], outputs=[";
  for (const auto &out : node.outputs_)
    os << out << ",";
  os << "])";
  return os;
}

LazyNode LazyGraph::addNode(LazyNode node) {
  nodes_.push_back(node);
  return node;
}

std::ostream &operator<<(std::ostream &os, const LazyGraph &graph) {
  os << "LazyGraph(id=" << graph.id_ << ", nodes=[\n";
  for (const auto &node : graph.nodes_) {
    os << "  " << node << "\n";
  }
  os << "])";
  return os;
}
