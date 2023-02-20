// Conversion from decimal to Roman numerals.
//
// Since my son is currently checking out Roman numerals at school, I decided to have a little chat
// with him about it and thought I would implement the conversion just for fun (and to practice
// Rust).
//
// Andre Zunino <neyzunino@gmail.com>
// 20 February 2023
//

struct Group<'a> {
    one_symbol: &'a str,
    five_symbol: &'a str,
    next_one_symbol: &'a str,
}

const GROUPS: [Group; 3] = [
    Group {
        one_symbol: "I",
        five_symbol: "V",
        next_one_symbol: "X",
    },
    Group {
        one_symbol: "X",
        five_symbol: "L",
        next_one_symbol: "C",
    },
    Group {
        one_symbol: "C",
        five_symbol: "D",
        next_one_symbol: "M",
    },
];

fn digit_to_roman(digit: usize, group_idx: usize) -> String {
    match group_idx {
        0..=2 => {
            let group = &GROUPS[group_idx];
            match digit {
                1..=3 => group.one_symbol.repeat(digit),
                4 => format!("{}{}", group.one_symbol, group.five_symbol),
                5 => group.five_symbol.to_string(),
                6..=8 => format!(
                    "{}{}",
                    group.five_symbol,
                    group.one_symbol.repeat(digit - 5)
                ),
                9 => format!("{}{}", group.one_symbol, group.next_one_symbol),
                _ => String::new(),
            }
        }
        3 => match digit {
            1..=3 => "M".repeat(digit),
            4..=9 => format!("{}'", digit_to_roman(digit, 0)),
            _ => String::new(),
        },
        _ => panic!("That's too big! (PAUSE)"),
    }
}

pub fn decimal_to_roman(mut n: usize) -> String {
    let mut group_idx: usize = 0;
    let mut roman = String::new();
    while n > 0 {
        let digit: usize = n % 10;
        roman = digit_to_roman(digit, group_idx) + &roman;
        n /= 10;
        group_idx += 1;
    }
    roman
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_decimal_to_roman_units() {
        let romans: Vec<String> = (1..10).map(|i| decimal_to_roman(i)).collect();
        let expected = vec!["I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"];
        assert_eq!(expected, romans);
    }

    #[test]
    fn test_decimal_to_roman_tens() {
        let romans: Vec<String> = (10..100).step_by(10).map(|i| decimal_to_roman(i)).collect();
        let expected = vec!["X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"];
        assert_eq!(expected, romans);
    }

    #[test]
    fn test_decimal_to_roman_hundreds() {
        let romans: Vec<String> = (100..1000)
            .step_by(100)
            .map(|i| decimal_to_roman(i))
            .collect();
        let expected = vec!["C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"];
        assert_eq!(expected, romans);
    }

    #[test]
    #[should_panic]
    fn test_maximum_supported_decimal_is_9999() {
        decimal_to_roman(10000);
    }
}
