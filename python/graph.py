import json
from dataclasses import dataclass


@dataclass
class LazyGraph:
    curr_id = 0
    data_id = 0

    def __init__(self):
        LazyGraph.curr_id += 1
        self.id = f"lazydata{LazyGraph.curr_id}"
        self.nodes = []

    def add_node(self, op, shape, dtype):
        node = Node(op, shape, dtype)
        self.nodes.append(node)
        return node

    @staticmethod
    def get_next_data_id():
        LazyGraph.data_id += 1
        return f"data{LazyGraph.data_id}"

    def to_dict(self):
        return {
            "id": self.id,
            "nodes": [node.to_dict() for node in self.nodes],
        }

    def to_json(self):
        return json.dumps(self.to_dict(), indent=2)

    def __repr__(self):
        return f"LazyGraph(id={self.id}, nodes={self.nodes})"


@dataclass
class Node:
    def __init__(self, op, shape, dtype):
        self.op = op
        self.shape = shape
        self.dtype = dtype
        self.inputs = []
        self.outputs = []

    def add_input(self):
        data_id = LazyGraph.get_next_data_id()
        self.inputs.append(data_id)
        return data_id

    def add_input_from_id(self, id):
        self.inputs.append(id)

    def add_output(self):
        data_id = LazyGraph.get_next_data_id()
        self.outputs.append(data_id)
        return data_id

    def __repr__(self):
        return f"Node(op={self.op}, shape={self.shape}, dtype={self.dtype}, inputs={self.inputs}, outputs={self.outputs})"

    def to_dict(self):
        return {
            "op": self.op,
            "shape": self.shape,
            "dtype": self.dtype,
            "inputs": self.inputs,
            "outputs": self.outputs,
        }


graph = LazyGraph()
