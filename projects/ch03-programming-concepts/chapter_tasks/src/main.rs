fn main() {
    let fahrenheit = 98.6;
    let celsius = to_celsius(fahrenheit);
    println!(
        "{} degrees Fahrenheit is {} degrees Celsius.",
        fahrenheit, celsius
    );

    let n = 10;
    let fibo_n = fibo(n);
    println!("The {}th Fibonacci number is {}.", n, fibo_n);
}

fn to_celsius(fahrenheit: f64) -> f64 {
    let celsius = (fahrenheit - 32.0) * 5.0 / 9.0;
    return celsius;
}

fn fibo(n: u32) -> u32 {
    if n <= 1 {
        return n;
    }
    return fibo(n - 1) + fibo(n - 2);
}
