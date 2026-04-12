// use std::{fs::File, io::BufReader};

use clap::Parser;

/// Search for a pattern in a file and display the lines that contain it.
#[derive(Parser)]
struct CLI {
    /// The pattern to search for
    pattern: String,
    /// The path to the file to read
    path: std::path::PathBuf,
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let args = CLI::parse();

    let content = std::fs::read_to_string(args.path);
    let content = match content {
        Ok(content) => content,
        Err(error) => return Err(error.into()),
    };

    println!("The content of the file is:\n{}", content);

    Ok(())

    // for (index, line) in content.lines().enumerate() {
    //     if line.contains(&args.pattern) {
    //         println!("{}:\t {}", index + 1, line);
    //     }
    // }
}
