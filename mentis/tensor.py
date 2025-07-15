from graph import graph


class Tensor:
    def __init__(self, shape, dtype=None):
        self.shape = shape
        self.dtype = dtype

        # add the graph input
        node = graph.add_node("input", shape, dtype)
        self.id = node.add_input()

    def __matmul__(self, tensor: "Tensor"):
        node = graph.add_node("matmul", self.shape, self.dtype)
        node.add_input_from_id(self.id)
        node.add_input_from_id(tensor.id)
        return self

    def __add__(self, tensor: "Tensor"):
        node = graph.add_node("add", self.shape, self.dtype)
        node.add_input_from_id(self.id)
        node.add_input_from_id(tensor.id)
        return self

    def relu(self):
        node = graph.add_node("relu", self.shape, self.dtype)
        node.add_input_from_id(self.id)
        return self

    def elu(self):
        node = graph.add_node("elu", self.shape, self.dtype)
        node.add_input_from_id(self.id)
        return self

    def __repr__(self):
        return f"Tensor(shape={self.shape}, dtype={self.dtype})"


t1 = Tensor([10, 10], dtype="float32")
t2 = Tensor([10, 10], dtype="float32")
t3 = t1 @ t2
t2.elu().elu()
print(graph)
