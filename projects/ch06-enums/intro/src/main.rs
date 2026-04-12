#[derive(Debug)]
enum IpAddr {
    V4(String),
    V6(String),
}

fn main() {
    // let four = IpAddr::V4;
    // let six = IpAddr::V6;

    let home = IpAddr::V4(String::from("127.0.0.1"));
    let loopback = IpAddr::V6(String::from("::1"));

    // route(four);
    // route(six);
}

// fn route(ip_addr: IpAddr) {
//     println!("Routing to {:?}", ip_addr);
// }
