fn main() {
    let number = 3;

    if number < 5 {
        println!("Condition was truthy");
    } else {
        println!("Condition was falsy");
    }

    let condition = true;
    let number = if condition { 5 } else { 6 };

    println!("The value of number is: {number}");

    let mut counter = 0;

    loop {
        counter += 1;
        println!("The value of counter is: {counter}");

        if counter == 5 {
            break;
        }
    }

    let a = [10, 20, 30, 40, 50];

    for value in a {
        println!("The value is: {value}");
    }

    for number in 1..4  {
        println!("{number}");
    }
}
