fn main() {
    println!("Hello world");
    // shadowing();
    // integer();
    // float();
    // boolen();
    // turple();
    // array();
    //let n = func("lucky", 10);
    //println!("{n}");
    //dbg!(n);
    state();
}

fn shadowing() {
    let spaces = "     ";
    let spaces = spaces.len();
    println!("Space: {spaces}");
}

fn variable_type() {
    let user_input = "100";
    let converted: u32 = user_input.parse().expect("Could not parse...");
    let number: i8 = 10;
    let pi: f32 = 3.1415926;
    let turned_on: bool = false;
    let delta: char = 'd';
    let coordinates: (f32, f32) = (1.50, 1.25);
    let people: [&str; 3] = ["Bob", "Foo", "Calio"];
}

fn integer() {
    let n1: i8 = -10; // -128 to 127
    let n2: u8 = 2_0_0; // 0 to 255
    let arch_max: isize = isize::MAX;
    let arch_min: isize = isize::MIN;
    println!("{arch_max}");
    println!("{arch_min}");
}

fn float() {
    let a: f64 = 0.1;
    let b: f64 = 0.2;
    let sum: f64 = a + b;
    println!("{sum}");
}

fn boolen() {
    println!("500 > 250 is {}", 500 > 250);
    if 250 > 500 {
        println!("Hey hey");
    } else {
        println!("Ha ha");
    }
}

fn turple() {
    let data: (u8, f32, bool) = (10, 3.5, false);
    println!("data={:?}", data);
    let (n, d, b) = data;
    println!("{n}, {d}, {b}");
    let first = data.0;
    let second = data.1;
    let last = data.2;
    println!("{first}, {second}, {last}");
    let coordinates: (f32, f32) = (2.5, 1.5);
    println!("The treasure is located here: {:?}", coordinates);
    let empty: () = ();
}

fn array() {
    let numbers: [u8;5] = [1, 2, 3, 4, 5];

    let days = ["Mon", "Tue", "Weds", "Thurs", "Fri", "Sat", "Sun"];
    println!("numbers={:?}", numbers);

    let repeat = ["lucky"; 100];
    println!("Hello {:?}", repeat);

    let first = days[0];
    let last = days[6];
    // let invalid = days[7];
}

fn func(name: &str, times: usize) -> i32 {
    println!("Hello, {}!", name.repeat(times));
    // return 111;
    (123 + times) as i32
}

fn state() {
    let sum = {
        let x = 10;
        let y = 20;
        x + y
    };
}
