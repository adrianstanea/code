fn main() {
    let s = "hello world";
    println!("{}", s);

    let mut s = String::from("hello");
    s.push_str(", world!");
    println!("{}", s);
}
