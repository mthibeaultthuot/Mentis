use mentis_engine::get_engine;
use mentis_engine::ENGINE;
use mentis_tensor::Tensor;

#[test]
fn tensor_graph() {
    let t1 = Tensor::new([[1.0, 2.0], [3.0, 4.0]]);
    let t2 = Tensor::new([[1.0, 2.0], [3.0, 4.0]]);
    t1.add(&t2).unwrap();

    println!("{:?}", t1);
    println!("{:?}", get_engine().unwrap());
}
