//mod print;
//mod vars;
use rayon::prelude::*;

fn main() {
    let input_arr = vec![0,1,2,3];
    let mut prefix_sum = vec![0,0,0,0];
    prefix_sum[0] = input_arr[0];

    input_arr.par_iter().for_each(|i|{
        prefix_sum[i] = prefix_sum[i-1] + input_arr[i];
    });
}
