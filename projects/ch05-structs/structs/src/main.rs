fn main() {
    let mut user = User {
        active: true,
        username: String::from("some_username_123"),
        email: String::from("someone@email.com"),
        sign_in_count: 1,
    };
    user.sign_in_count += 1;

    println!("Username: {}", user.username);
    println!("Email: {}", user.email);
    println!("Active: {}", user.active);
    println!("Sign in count: {}", user.sign_in_count);

    let user2 = build_user(
        String::from("another@email.com"),
        String::from("another_username"),
    );

    println!("Username: {}", user2.username);
    println!("Email: {}", user2.email);
    println!("Active: {}", user2.active);
    println!("Sign in count: {}", user2.sign_in_count);

    let black = Color(0, 0, 0);
    let origin = Point(0, 0, 0);

}

struct User {
    active: bool,
    username: String,
    email: String,
    sign_in_count: u64,
}

fn build_user(email: String, username: String) -> User {
    return User {
        active: true,
        username,
        email,
        sign_in_count: 1,
    };
}

struct  Color(i32, i32, i32);
struct  Point(i32, i32, i32);