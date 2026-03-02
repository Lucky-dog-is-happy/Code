use rand::RngExt;
use std::io;
use std::cmp::Ordering;

// let can't be global
// let PI: f64 = 3.14;
fn main() {
    println!("Guess the number!");
    const PI: f64 = 3.14159265358;
    println!("Pi is {PI}");

    let secret_number: u32 = rand::rng().random_range(1..=100);
    println!("The secret_number is :{}", secret_number);

    let mut count: u32 = 0;
    loop {
        println!("Input Your Guess:");
        let mut guess: String = String::new();
        
        io::stdin()
            .read_line(&mut guess)
            .expect("Failed to read line.");

        let guess: u32 = guess.trim().parse().expect("Please type a valid number!");
        println!("You guessed: {}", guess);

        match guess.cmp(&secret_number) {
            Ordering::Less => 
            {
                println!("Too small!");
                count+=1;
            },
            Ordering::Greater => 
            {
                println!("Too big!");
                count+=1;
            },
            Ordering::Equal => {
                println!("You guess correctly!");
                break;
            }
        }
    }
    println!("You have guessed {} times", count)
}
