# Pinecone Programming Language

**Pinecone** is a modern, high-performance programming language inspired by the best features of Python, C, and Rust. 

It aims to combine Python’s readability and ease of use, C’s low-level power, and Rust’s memory safety and fearless concurrency into one language.

---

## Features

- Clean, readable syntax with optional indentation-based blocks
- Statically typed with powerful type inference
- Ownership and borrowing system for memory safety without garbage collection
- Manual memory control with safe `unsafe` blocks for systems programming
- Built-in async/await and concurrency primitives
- Interoperability with C libraries via FFI
- Comprehensive standard library for I/O, collections, networking, and more

---

## Example

```pinecone
fn factorial(n: int) -> int {
    if n <= 1 {
        return 1
    } else {
        return n * factorial(n - 1)
    }
}

fn main() {
    let mut x = 5
    let y = factorial(x)
    print("Factorial of ", x, " is ", y)
}
