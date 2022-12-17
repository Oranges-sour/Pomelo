#[link(name = "PomeloLib", kind = "static")]
extern "C" {
    pub fn p_initgraph(w: i32, h: i32, flag: i32);

    pub fn p_getlinestyle(pstyle: *mut c_void);

    pub fn p_setlinestyle_1(pstyle: *mut c_void);
}

#[derive(Debug)]
#[repr(C)]
struct Test {
    a: i32,
    b: i32,
    c: i64,
    d: i32,
}

use std::ffi::c_void;
use std::thread;
use std::time;

fn main() {
    unsafe {
        p_initgraph(600, 400, 0);

        let mut p = Test {
            a: 0,
            b: 0,
            c: 0,
            d: 0,
        };



        p_getlinestyle(&mut p as *mut Test as *mut c_void);

        println!("{:?}", p);

        p.b = 2;

        p_setlinestyle_1(&mut p as *mut Test as *mut c_void);

        p_getlinestyle(&mut p as *mut Test as *mut c_void);

        
        println!("{:?}", p);
    }

    

    let _ = std::io::stdin().read_line(&mut String::new());

    //println!("Hello, world!");
}
