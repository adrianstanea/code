use std::collections::HashMap as Map;

fn main() {
    restaurant::eat_at_restaurant();
    // customer::eat_at_restaurant();

    restaurant::hosting::add_to_waitlist();
    // restaurant::hosting::seat_at_table();

    let mut map = Map::new();
    map.insert(1, "Hello");
    map.insert(2, "World!");
    println!("{:?}", map);
}
