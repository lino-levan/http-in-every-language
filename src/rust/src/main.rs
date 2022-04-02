extern crate chrono;

use std::io::prelude::*;
use std::net::TcpListener;
use std::net::TcpStream;
use chrono::Local;

fn main() {
    let port = 8080;
    let url = format!("127.0.0.1:{}", port);

    println!("Listening on http://{}", url);
    let listener = TcpListener::bind(url).unwrap();

    for stream in listener.incoming() {
        let stream = stream.unwrap();

        handle_connection(stream);
    }
}

fn handle_connection(mut stream: TcpStream) {
    let mut buffer = [0; 1024];

    stream.read(&mut buffer).unwrap();

    // Definitely not the best way to do this, but it works for now
    let path: String = String::from_utf8_lossy(&buffer[..]).split("GET ").collect::<Vec<&str>>()[1].split(" HTTP").collect::<Vec<&str>>()[0].to_string();
    let date = Local::now().format("%Y-%m-%d %H:%M:%S");

    let content = format!("Hello world! The time is {} and you requested the path {}", date, path);

    let response = format!("HTTP/1.1 200 OK\r\nContent-Length: {}\r\n\r\n{}", content.len(), content);

    stream.write(response.as_bytes()).unwrap();
    stream.flush().unwrap();
}