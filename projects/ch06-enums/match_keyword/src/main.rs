#[derive(Debug)]
enum UsState {
    Alabama,
    Alaska,
    Arizona,
    Arkansas,
    California,
    Colorado,
    Connecticut,
    Delaware,
    Florida,
    Georgia,
}

impl UsState {
    fn existed_in(&self, year: u16) -> bool {
        match self {
            UsState::Alabama => year >= 1819,
            UsState::Alaska => year >= 1959,
            _ => false,
        }
    }
}

#[derive(Debug)]
enum Coin {
    Penny,
    Nickel,
    Dime,
    Quarter(UsState),
}

fn value_in_cents(coin: Coin) -> u32 {
    match coin {
        Coin::Penny => 1,
        Coin::Nickel => 5,
        Coin::Dime => 10,
        Coin::Quarter(state) => {
            println!("State quarter from {:?}!", state);
            25
        }
    }
}

fn plus_one(value: Option<i32>) -> Option<i32> {
    match value {
        None => None,
        Some(x) => Some(x + 1),
    }
}

fn describe_state_quarter(coin: Coin) -> Option<String> {
    let Coin::Quarter(state) = coin else {
        return None;
    };

    const TARGET_YEAR: u16 = 1900;

    if state.existed_in(TARGET_YEAR) {
        Some(format!("State quarter from {:?}!", state))
    } else {
        Some(format!(
            "State quarter from {:?} did not exist in {}.",
            state, TARGET_YEAR
        ))
    }
}

fn main() {
    let coin = Coin::Dime;
    println!("The value of the coin is {} cents.", value_in_cents(coin));

    value_in_cents(Coin::Quarter(UsState::Alaska));

    let mut test_val = Some(5);
    println!("The value of test_val is {:?}.", test_val);
    test_val = plus_one(test_val);
    println!("The value of test_val is {:?}.", test_val);

    // Concise Control Flow with `if let` and `let .. else` statements

    let config_max = Some(3u8);
    match config_max {
        Some(max) => println!("The maximum is configured to be {}.", max),
        _ => (),
    }

    if let Some(max) = config_max {
        println!("The maximum is configured to be {}.", max);
    }

    // let coin = Coin::Quarter(UsState::Alabama);

    let mut count = 0;
    if let Coin::Quarter(state) = coin {
        println!("State quarter from {:?}!", state);
    } else {
        count = count + 1;
    }
}
