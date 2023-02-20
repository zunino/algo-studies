use roman::*;

fn main() {
    let decimals = vec![17, 172, 999, 1000, 1728, 3560, 4000, 4298, 8165, 9999];
    for n in decimals {
        println!("{:4} => {}", n, decimal_to_roman(n));
    }
}
