use mentis_fusion::graph;
use mentis_ops::Op;

#[test]
fn graph_new() {
    let mut graph = graph::Graph::new();
    let node = graph.add_node().unwrap();
    node.add_input();
    node.add_input();

    assert_eq!(Op::Add, node.op());
    assert_eq!(node.inputs().get(0).unwrap(), &String::from("data1"));
    assert_eq!(node.inputs().get(1).unwrap(), &String::from("data2"));
}
