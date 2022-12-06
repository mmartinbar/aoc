use std::fs::File;
use std::io::{BufReader, BufRead, Error};

fn main() -> Result<(), Error> {
    let file = BufReader::new(File::open("./input.txt")?);

    let mut vec = Vec::new();

    let mut acc_value = 0;

    for line in file.lines() {
        match line?.as_str() {
            "" => {
                vec.push(acc_value);
                acc_value = 0;
            },
            number => {
                acc_value += number.parse::<i32>().unwrap();
            }
        }
    }
    vec.push(acc_value);

    vec.sort_by(|a, b| b.cmp(a));

    println!("Result {:?}", &vec[0..3].iter().sum::<i32>());

    Ok(())
}
