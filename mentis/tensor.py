class Tensor:
    def __init__(self, shape, dtype=None):
        self.shape = shape
        self.dtype = dtype

    def __repr__(self):
        return f"Tensor(shape={self.shape}, dtype={self.dtype})"


tensor = Tensor([10, 10], dtype="float32")
print(tensor)
