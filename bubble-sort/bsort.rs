fn bsort(data: &mut[i64]) {
    loop {
        let mut swapped = false;
        for i in 0..data.len() - 1 {
            if data[i] > data[i+1] {
                let temp = data[i];
                data[i] = data[i+1];
                data[i+1] = temp;
                swapped = true;
            }
        }
        if !swapped {
            break;
        }
    }
}

fn main() {
    let mut data = [10, 3, 8, 1, 12];
    println!("0. data: {:#?}", data);
    bsort(&mut data);
    println!("1. data: {:#?}", data);
}

