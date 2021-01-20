use std::fs::File;
use std::io::prelude::*;
use std::path::Path;
use rand::{Rng, SeedableRng, rngs::StdRng};

fn main() {
    let path = Path::new("flag");

    let mut file = match File::open(&path) {
        Err(_) => panic!("open failed"),
        Ok(file) => file,
    };

    let mut s = String::new();
    file.read_to_string(&mut s);

    let mut bs = s.into_bytes(); 
    //let key = bs.clone();
    let mut seed : [u8; 32] = [0; 32];
    for i in 0..bs.len() {
        let idx = (7*i+4)%bs.len();
        seed[i%32] = bs[idx];
        let mut rng = StdRng::from_seed(seed);
        let r: u8 = rng.gen();
        bs[idx] ^= r;
    }

    let path = Path::new("output");

    let mut file = match File::create(&path) {
        Err(_) => panic!("open failed"),
        Ok(file) => file,
    };
    file.write_all(bs.as_slice());
}
