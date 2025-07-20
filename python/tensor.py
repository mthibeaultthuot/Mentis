import core_cpp
from convert_graph import lazygraph_to_flatbuffer
from graph import graph


class Tensor:
    def __init__(self, shape, dtype=None):
        self.shape = shape
        self.dtype = dtype

        node = graph.add_node("input", shape, dtype)
        self.id = node.add_input()

    def __matmul__(self, tensor: "Tensor"):
        node = graph.add_node("matmul", self.shape, self.dtype)
        node.add_input_from_id(self.id)
        node.add_input_from_id(tensor.id)
        self.id = node.add_output()
        return self

    def __add__(self, tensor: "Tensor"):
        node = graph.add_node("add", self.shape, self.dtype)
        node.add_input_from_id(self.id)
        node.add_input_from_id(tensor.id)
        self.id = node.add_output()
        return self

    def relu(self):
        node = graph.add_node("relu", self.shape, self.dtype)
        node.add_input_from_id(self.id)
        self.id = node.add_input()
        return self

    def elu(self):
        node = graph.add_node("elu", self.shape, self.dtype)
        # node.add_input_from_id(self.id)
        self.id = node.add_input()
        return self

    def realize(self):
        buf = lazygraph_to_flatbuffer(graph)
        core_cpp.run_graph(buf)

    def __repr__(self):
        return f"Tensor(shape={self.shape}, dtype={self.dtype})"


t1 = Tensor([10, 10], dtype="float32")
t2 = Tensor([10, 10], dtype="float32")
t3 = t1 @ t2
t4 = Tensor([10, 10], dtype="float32")
t5 = t3 + t4
t6 = t2.elu().elu()

print(graph)
t6.realize()
