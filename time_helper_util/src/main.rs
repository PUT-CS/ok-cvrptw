#[derive(Debug, Clone)]
struct Point {
    x: i32,
    y: i32
}

fn distance(a: &Point, b: &Point) -> f64 {
    (((b.x-a.x).pow(2) + (b.y-a.y).pow(2)) as f64).sqrt()
}

fn getline() -> String {
    let mut buf = String::new();
    std::io::stdin().read_line(&mut buf).unwrap();
    buf
}

fn main() {
    let args = std::env::args().collect::<Vec<String>>();
    let mut current_point = Point { x: args[1].parse().unwrap(), y: args[2].parse().unwrap()};
    let service_time: i32 = args[3].parse().unwrap();
    let mut total = 0.0;
    loop {
	println!("Next Depot: ");
	let mut line = getline();
	let new = Point {
	    x: line.split_whitespace().collect::<Vec<&str>>()[0].parse().unwrap(),
	    y: line.split_whitespace().collect::<Vec<&str>>()[1].parse().unwrap()
	};
	total += distance(&current_point, &new);
	println!("Total: {:.5}", total);
	if new.x == args[1].parse().unwrap() && new.y == args[2].parse().unwrap() {return;}
	println!("Wait until:");
	line = getline();
	if !line.trim().is_empty() {
	    total = line.split_whitespace().collect::<Vec<&str>>()[0].parse::<f64>().unwrap();
	}
	total += service_time as f64;
	println!("After service: {:.5}", total);
	current_point = new;
    }
}
