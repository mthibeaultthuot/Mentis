#include "engine/engine.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

int add(int x, int y) { return x + y; }

PYBIND11_MODULE(core_cpp, m) {
  m.doc() = "dl bindings";
  m.def("add", add);

  py::class_<Engine>(m, "Engine").def(py::init<>()).def("add", &Engine::Add);
}
