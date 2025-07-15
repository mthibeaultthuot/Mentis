class LazyGraph:
    """Graph implentation"""

    curr_id = 0

    def __init__(self):
        LazyGraph.curr_id += 1
        self.id = "lazydata%s" % LazyGraph.curr_id
        self.nodes = []

    def add_node(self, op, shape, dtype):
        return self.nodes.append(Node(op, shape, dtype))

    def __repr__(self):
        return f"LazyGraph(id={self.id}, nodes={self.nodes})"


class Node:
    def __init__(self, op, shape, dtype):
        self.op = op
        self.shape = shape
        self.dtype = dtype
        self.inputs = []
        self.outputs = []

    def add_input(input_id):
        self.inputs.append(input_id)

    def add_ouput(output_id):
        self.outputs.append(output_id)

    def __repr__(self):
        return f"Node(op={self.op}, shape={self.shape}, dtype={self.dtype}, inputs={self.inputs}, outputs={self.outputs})"


graph = LazyGraph()


graph.add_node("input", [10, 10], "float32")
print(graph)
