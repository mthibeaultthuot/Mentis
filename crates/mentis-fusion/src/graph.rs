use mentis_ops::Op;
use thiserror::Error;

#[derive(Error, Debug)]

pub enum GraphError {
    #[error("Node creation failed")]
    NodeCreationFailed,
}

#[derive(Debug, Clone)]
pub struct Graph {
    nodes: Vec<Node>,
    nb_input: usize,
}

type NodeId = usize;

#[derive(Debug, Clone)]
pub struct Node {
    node_id: NodeId,
    op: Op,
    inputs: Vec<String>,
}

impl Graph {
    pub fn new() -> Self {
        Self {
            nodes: Vec::new(),
            nb_input: 0,
        }
    }

    pub fn nodes(&self) -> Vec<Node> {
        self.nodes.clone()
    }

    pub fn add_node(&mut self, op: Op) -> Result<&mut Node, GraphError> {
        let node = Node::new(self.get_next_node_id(), op);
        self.nodes.push(node);

        match self.nodes.last_mut() {
            Some(node) => Ok(node),
            None => Err(GraphError::NodeCreationFailed),
        }
    }

    pub fn get_next_node_id(&mut self) -> usize {
        self.nb_input + 1
    }
}

impl Node {
    pub fn new(node_id: NodeId, op: Op) -> Self {
        Self {
            node_id,
            op,
            inputs: Vec::new(),
        }
    }

    pub fn inputs(&self) -> Vec<String> {
        self.inputs.clone()
    }

    pub fn op(&self) -> Op {
        self.op
    }

    pub fn add_input(&mut self) -> &String {
        let string_input = String::from(format!("data{:?}", self.inputs.len() + 1));

        self.inputs.push(string_input);
        self.inputs.last().expect("string input")
    }
}
