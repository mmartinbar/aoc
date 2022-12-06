use std::fs::File;
use std::io::{BufReader, BufRead, Error};

fn main() -> Result<(), Error> {
    let file = BufReader::new(File::open("./input.txt")?);

    let mut max_value = i32::MIN; 
    let mut acc_value = 0;

    for line in file.lines() {
        match line?.as_str() {
            "" => {
                if acc_value > max_value {
                    max_value = acc_value;
                }
                acc_value = 0;
            },
            number => {
                acc_value += number.parse::<i32>().unwrap();
            }
        }
    }

    println!("Result is {}", max_value);

    Ok(())
}
