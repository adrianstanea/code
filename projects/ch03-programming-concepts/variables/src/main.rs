fn main() {
    let mut x = 5;
    println!("The value of x is: {x}");
    x = 6;
    println!("The value of x is: {x}");

    const THREE_HOURS_IN_SECONDS: u32 = 3 * 60 * 60;
    println!("The value of THREE_HOURS_IN_SECONDS is: {THREE_HOURS_IN_SECONDS}");

    let x = 5;
    let x = x + 1;
    {
        let x = x * 2;
        println!("The value of x in the inner scope is: {x}");
    }
    println!("The value of x in the outer scope is: {x}");

    let _x = 2.0;
    let _x = 3.0f32;

    // Adition
    let sum = 5 + 10;

    // subtraction
    let difference = 95.5 - 4.5;

    // multiplication
    let product = 4 * 430;

    // division
    let quotiend = 4.2 / 1.1;
    let truncated = -5 / 3;

    // modulo
    let remainder = 43 % 5;

    let t: bool = true;

    let f: bool = false;

    let c = 'z';
    let z: char = 'z';

    // Compound types

    // Tuple
    let tuple = (599, 6.2, 'z');

    let (x, y, z) = tuple;
    let first = tuple.0;
    let second = tuple.1;
    let third = tuple.2;

    // Array
    let arr = [1, 2, 3, 4];

    let arr2: [i32; 5] = [3; 5];
    for val in arr2 {
        println!("Value is: {val}");
    }
}
