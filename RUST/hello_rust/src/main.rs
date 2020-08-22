//mod print;
//mod vars;
use rayon::prelude::*;

fn main() {
    let input_arr: [i32;4] = [0,1,2,3];
    let mut prefix_sum: [i32;4] = [0,0,0,0];
    prefix_sum[0] = input_arr[0];
    let n = input_arr.len();
    (1..n).into_iter().for_each(|i|{
        prefix_sum[i] = prefix_sum[i-1] + input_arr[i];
    });
    
    println!("{:?}", prefix_sum);
}
