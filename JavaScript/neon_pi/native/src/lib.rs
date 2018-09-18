#[macro_use]
extern crate neon;
extern crate rand;
extern crate num_cpus;
extern crate futures;
extern crate futures_cpupool;

use neon::prelude::*;
use rand::Rng;
use futures::Future;
use futures_cpupool::CpuPool;

fn pi(mut cx: FunctionContext) -> JsResult<JsNumber> {
    let js_reps: Handle<JsNumber> = cx.argument(0)?;
    let reps = js_reps.value() as u64;

    let cores = num_cpus::get();
    let pool = CpuPool::new_num_cpus();

    let mut futures = Vec::new();
    for _ in 0..cores {
        let input_reps = reps / cores as u64;
        let future = pool.spawn_fn(move || {
            let count = monte_carlo_pi(input_reps);
            let res: Result<u64, ()> = Ok(count);
            return res;
        });

        futures.push(future);
    }

    let mut total_count: u64 = 0;
    for future in futures {
        total_count = total_count + future.wait().unwrap();
    }

    let pi = total_count as f64 / reps as f64 * 4.0;

    Ok(cx.number(pi))
}

fn in_unit_circle(x: f64, y: f64) -> bool {
    if x*x + y*y <= 1.0 {
        true
    } else {
        false
    }
}

fn monte_carlo_pi(reps: u64) -> u64 {
    let mut count: u64 = 0;
    let mut rng = rand::thread_rng();

    for _ in 0..reps {
        if in_unit_circle(rng.gen::<f64>(), rng.gen::<f64>()) {
            count += 1;
        }
    }

    count
}

register_module!(mut cx, {
    cx.export_function("pi", pi)
});

#[cfg(test)]
#[test]
fn in_unit_circle_test() {
    assert_eq!(in_unit_circle(0.0, 0.0), true);
    assert_eq!(in_unit_circle(0.5, 0.5), true);
    assert_eq!(in_unit_circle(1.0, 0.0), true);
    assert_eq!(in_unit_circle(0.0, 1.0), true);
    assert_eq!(in_unit_circle(1.0, 0.1), false);
    assert_eq!(in_unit_circle(0.1, 1.0), false);
    assert_eq!(in_unit_circle(1.0, 1.0), false);

}