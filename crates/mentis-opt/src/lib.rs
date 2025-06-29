use mentis_macros::Kernel;

#[Kernel]
pub fn add(left: u64, right: u64) -> u64 {
    left + right
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_add() {
        let str_res = Add::source();

        println!("{:?}", str_res);
    }
}
