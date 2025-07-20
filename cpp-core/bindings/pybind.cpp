#include "engine/engine.h"
#include "graph/graph.h"
#include "graph_generated.h"
#include "ops/ops.h"
#include "tensor/dtype.h"
#include <iostream>
#include <pybind11/pybind11.h>

namespace py = pybind11;

int add(int x, int y) { return x + y; }

LazyGraph DeserializeGraph(pybind11::bytes b) {
  std::string buf = b;
  const Mentis::Graph *graph = Mentis::GetGraph(buf.data());
  LazyGraph lazyGraph(1);

  for (const auto *node : *graph->nodes()) {
    std::string op = node->op()->str();
    Mentis::DType proto_dtype = node->dtype();
    DType dtype = DType::Float32;

    switch (proto_dtype) {
    case Mentis::DType_FLOAT32:
      dtype = DType::Float32;
      break;
    case Mentis::DType_FLOAT64:
      dtype = DType::Float64;
      break;

    case Mentis::DType_INT32:
      dtype = DType::Int32;
      break;
    case Mentis::DType_INT64:
      dtype = DType::Int64;
      break;
    case Mentis::DType_BOOL:
      dtype = DType::Bool;
      break;
    }

    std::vector<std::string> inputs;
    std::vector<std::string> outputs;
    std::vector<int> shape;

    for (const auto *i : *node->inputs()) {
      inputs.push_back(i->str());
      std::cout << i->str() << "\n";
    }

    for (const auto *i : *node->outputs()) {
      outputs.push_back(i->str());
      std::cout << i->str() << "\n";
    }

    for (int s : *node->shape()) {
      shape.push_back(s);
    }

    LazyNode lazyNode(1, ops_from_string(op), dtype, shape, inputs, outputs);

    lazyGraph.addNode(lazyNode);
  }
  return lazyGraph;
}

void RunGraph(pybind11::bytes b) {
  LazyGraph lazyGraph = DeserializeGraph(b);
  std::cout << lazyGraph << "\n";
}

PYBIND11_MODULE(core_cpp, m) {
  m.doc() = "dl bindings";
  m.def("add", add);
  m.def("run_graph", &RunGraph);

  py::class_<Engine>(m, "Engine").def(py::init<>()).def("add", &Engine::Add);
}
