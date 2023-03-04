mod index;

use std::{io::{self, Write}, env, process::exit};

use index::TfIdfModel;

fn main() -> Result<(), io::Error> {
    let args: Vec<String> = env::args().collect();
    if args.len() != 2 {
        eprintln!("Usage: cargo run <data-path>");
        exit(1);
    }

    let model = TfIdfModel::build(&args[1])?;

    loop {
        print!("> ");
        io::stdout().flush()?;
        let mut input = String::new();
        io::stdin().read_line(&mut input)?;
        input = String::from(input.trim());
        if input == "quit" {
            break;
        }
        let result = model.search(&input);
        if result.is_empty() {
            println!("No matches");
            continue;
        }
        for (i, (doc_path, score)) in result.into_iter().enumerate() {
            println!("{:3}. {doc_path} (score: {score})", i + 1);
        }
    }

    Ok(())
}
