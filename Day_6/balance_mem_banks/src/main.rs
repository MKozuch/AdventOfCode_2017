use std::env;
use std::fs::File;  
use std::io::prelude::*;


fn main(){
    let args: Vec<String> = env::args().collect();

    if args.len() < 2{
        panic!("not enough arguments");
    }
    let filename  = &args[1];

    let mut f = File::open(filename).expect("Something went wrong while accessing file");
    let mut contents = String::new();
    f.read_to_string(&mut contents).expect("Something went wrong while reading file");
    
    let split = contents.split("\t").collect::<Vec<&str>>();
    let vect_int = split.into_iter().map(|x| x.parse().unwrap()).collect::<Vec<i32>>();

    let mut current_balances = vect_int.clone();
    let mut balance_history = vec![current_balances.clone()];
    
    let mut cycles_to_duplicate = 0;
    let mut duplicate_detected = false;
    loop{
        balance_banks(&mut current_balances);
        cycles_to_duplicate += 1;
        
        let mut i = 0;
        while i < balance_history.len(){
            if balance_history[i] == current_balances {
                duplicate_detected = true;
                break;
            }
            i += 1;
        }

        if duplicate_detected == true{
            break;
        }
        else{
            balance_history.push(current_balances.clone());
        }
    }
    println!("{:?}", cycles_to_duplicate);


    let start_balance = current_balances.clone();
    let mut cycles_in_loop = 1;
    balance_banks(&mut current_balances);
    while start_balance != current_balances{
        balance_banks(&mut current_balances);
        cycles_in_loop += 1;
    }
    println!("{:?}", cycles_in_loop);
}

fn balance_banks(banks: &mut Vec<i32>){
    let banks_num = banks.len();
    let max_element = banks.iter().max().unwrap().clone();
    let max_index = banks.iter().position(|&x| x == max_element).unwrap().clone();
    let mut blocks = max_element;
    banks[max_index] = 0;

    let mut i = 1;
    while blocks > 0{
        banks[(max_index + i) % banks_num] += 1;
        blocks -= 1;
        i += 1;
    }
}