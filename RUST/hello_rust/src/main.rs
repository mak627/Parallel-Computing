//mod print;
//mod vars;
use std::sync::{Arc, Mutex};
use rayon::prelude::*;

fn main() {
    let input_arr: [i32;4] = [0,1,2,3];
    let mut prefix_sum: [i32;4] = [0,0,0,0];
    prefix_sum[0] = input_arr[0];
    let n = input_arr.len();
    let prefix_sum = Mutex::new(prefix_sum);
    (1..n).into_par_iter().for_each(|i|{
        let mut prefix_sum = prefix_sum.lock().unwrap();
        let val = prefix_sum[i-1] + input_arr[i];
        prefix_sum[i] = val;
    });
    
    println!("{:?}", prefix_sum);
}
