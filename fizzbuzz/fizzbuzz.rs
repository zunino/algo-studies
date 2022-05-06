// FizzBuzz
//
// Andre Zunino <neyzunino@gmail.com>
// 16 April 2021

fn fizzbuzz(n: u32) {
    for i in 1..=n {
        let by_3 = i % 3 == 0;
        let by_5 = i % 5 == 0;
        if !by_3 && !by_5 {
            println!("{}", i);
            continue;
        }
        if by_3 {
            print!("Fizz");
        }
        if by_5 {
            print!("Buzz");
        }
        println!();
    }
}

fn main() {
    fizzbuzz(50);
}

