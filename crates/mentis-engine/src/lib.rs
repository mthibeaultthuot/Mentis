use mentis_fusion::graph::Graph;
use mentis_ops::Op;
use once_cell::sync::Lazy;
use std::sync::Mutex;
use std::sync::MutexGuard;
use thiserror::Error;

#[derive(Error, Debug)]
pub enum EngineError {
    #[error("Getting the engine failed")]
    GetEngineSingleton,

    #[error("Add op failed")]
    Operation,
}

#[derive(Debug)]
pub struct Engine {
    graph: Graph,
    input_ptrs: Vec<InputPtr>,
}

// keep track of the input string to identify the ptr in rust
#[derive(Debug)]
pub struct InputPtr {
    input: String,
    ptr: usize,
}

impl Engine {
    pub fn new() -> Self {
        Self {
            graph: Graph::new(),
            input_ptrs: Vec::new(),
        }
    }

    pub fn graph(&self) -> Graph {
        self.graph.clone()
    }

    // could add macro for enum of Ops to verify how much ptrs is needed
    pub fn add_op(&mut self, op: Op, ptrs: Vec<usize>) -> Result<(), EngineError> {
        let new_node = match self.graph.add_node(op) {
            Ok(node) => node,
            Err(_) => return Err(EngineError::Operation),
        };

        let iter = ptrs.into_iter();
        iter.for_each(|item| {
            let input_string = new_node.add_input();
            self.input_ptrs
                .push(InputPtr::new(input_string.to_owned(), item))
        });

        Ok(())
    }
}

impl InputPtr {
    pub fn new(input: String, ptr: usize) -> Self {
        Self { input, ptr }
    }
}

pub static ENGINE: Lazy<Mutex<Engine>> = Lazy::new(|| {
    let engine = Engine::new();
    Mutex::new(engine)
});

pub fn get_engine() -> Result<MutexGuard<'static, Engine>, EngineError> {
    Ok(ENGINE.lock().expect("poisonned"))
}
