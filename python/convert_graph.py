import flatbuffers
import Mentis.DType as fd
import Mentis.Graph as fb
import Mentis.Node as fn
from flatbuffers.compat import import_numpy

np = import_numpy()


def lazygraph_to_flatbuffer(graph):
    builder = flatbuffers.Builder(1024)
    node_offsets = []

    for node in graph.nodes:
        op_str = builder.CreateString(node.op)
        inputs = [builder.CreateString(i) for i in node.inputs]
        outputs = [builder.CreateString(o) for o in node.outputs]

        fn.NodeStartInputsVector(builder, len(inputs))
        for i in reversed(inputs):
            builder.PrependUOffsetTRelative(i)
        inputs_vec = builder.EndVector()

        fn.NodeStartOutputsVector(builder, len(outputs))
        for o in reversed(outputs):
            builder.PrependUOffsetTRelative(o)
        outputs_vec = builder.EndVector()

        shape_vec = builder.CreateNumpyVector(np.array(node.shape, dtype=np.int32))

        dtype_map = {"float32": fd.DType.FLOAT32, "int32": fd.DType.INT32}
        dtype_enum = dtype_map[node.dtype]

        fn.NodeStart(builder)
        fn.NodeAddOp(builder, op_str)
        fn.NodeAddInputs(builder, inputs_vec)
        fn.NodeAddOutputs(builder, outputs_vec)
        fn.NodeAddShape(builder, shape_vec)
        fn.NodeAddDtype(builder, dtype_enum)
        node_offset = fn.NodeEnd(builder)

        node_offsets.append(node_offset)

    fb.GraphStartNodesVector(builder, len(node_offsets))
    for n in reversed(node_offsets):
        builder.PrependUOffsetTRelative(n)
    nodes_vec = builder.EndVector()

    graph_id = builder.CreateString(graph.id)

    fb.GraphStart(builder)
    fb.GraphAddId(builder, graph_id)
    fb.GraphAddNodes(builder, nodes_vec)
    graph_offset = fb.GraphEnd(builder)

    builder.Finish(graph_offset)
    return bytes(builder.Output())
