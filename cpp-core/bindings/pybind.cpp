#include "engine/engine.h"
#include "graph_generated.h"
#include <iostream>
#include <pybind11/pybind11.h>

namespace py = pybind11;

int add(int x, int y) { return x + y; }

void RunGraph(pybind11::bytes b) {
  std::string buf = b;
  const Mentis::Graph *graph = Mentis::GetGraph(buf.data());

  for (const auto *node : *graph->nodes()) {
    std::string op = node->op()->str();
    std::vector<std::string> inputs;
    for (const auto *i : *node->inputs())
      inputs.push_back(i->str());

    std::vector<int> shape;
    for (int s : *node->shape())
      shape.push_back(s);
    std::cout << node;
  }
}

PYBIND11_MODULE(core_cpp, m) {
  m.doc() = "dl bindings";
  m.def("add", add);
  m.def("run_graph", &RunGraph);

  py::class_<Engine>(m, "Engine").def(py::init<>()).def("add", &Engine::Add);
}
