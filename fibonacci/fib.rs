/**
 * Non-recursive Fibonacci implementation.
 *
 * Andre Zunino <neyzunino@gmail.com>
 * 14 June 2021
 */

fn fib(n: u16) -> u64 {
    let mut f1 = 1;
    let mut f2 = 0;
    for _i in 0..n {
        let tmp = f1;
        f1 = f2;
        f2 = tmp + f1;
    }
    f2
}

fn main() {
    for i in 0..10 {
        println!("fib({}) = {}", i, fib(i));
    }
}
