# Machine Rite Core Library

A modular collection of foundational C data structures and memory utilities themed around the Adeptus Mechanicus.
A learning project/portfolio showcase written by Aaron Chavez.

This document is meant to serve as a personal Astronomican as I work on this project.
I also hope that any potential employers perusing my CV site can give this a glance to understand the goals with the project.

<!--toc:start-->
- [Machine Rite Core Library](#machine-rite-core-library)
  - [Project Overview](#project-overview)
  - [Foundational goals](#foundational-goals)
  - [Code Structure](#code-structure)
  - [Planned Modules](#planned-modules)
    - [Tier 1 - Fundamentals](#tier-1-fundamentals)
    - [Tier 2 - Intermediate Structures](#tier-2-intermediate-structures)
    - [Tier 3 - Infrastructure  Tools](#tier-3-infrastructure-tools)
  - [Theming / Presentation Layer](#theming-presentation-layer)
  - [Quality Goals](#quality-goals)
  - [Showcase Goals](#showcase-goals)
  - [Stretch Goals](#stretch-goals)
<!--toc:end-->

## Project Overview

The Machine Rite Core Library will be a set of standalone, reusable C modules implementing data structures, allocators, and low-level utilities. My goals with this project are:

- To build a strong foundation in C memory management, pointers, ownership, and error handling.
- Develop high-quality, dependency-free C modules suitable for use in future systems and projects.
- Showcase solid C fundamentals for my professional portfolio.

## Foundational goals

- Written in ISO C11 (while working to maintain C99 compatibility.
- Compiled using gcc
- Dependency-free (outside the standard lib of course)
- All modules compile cleanly with: `-Wall -Wextra -Werror`

## Code Structure

As I'm still learning, these should help keep me focused on what matters for solid C code:

- Use a `.h` and `.c` file per module:
  - `.h` files: What other code is allowed to use.
  - `.c` files: The actual impleemntation.
  - Purpose: keep things clean and prevent name collision.
- Document ownership clearly:
  - As C doesn't manage memory for me, I need to document:
    - When the user must call `free()`.
    - When memory is owned by the module.
    - When memory is borrowed temporarily.
- Provide init and free functions:
  - Each module should have something like:

  ```
  vector_init(&vec);
  vector_free(&vec);
  ```

  - This avoid uninitizlized memory bugs and keeps things consistent.
- Don't expose internal struct details unless there are no other options:
  - If I expose internal fields, it's easy to break invariants when users modify them incorrectly.
- Keep helper functions private:
  - Internal helper functions should be static in the `.c` file so they don't leak into the global namespace.

## Planned Modules

I've got a rough roadmap for what I'd like to implement. This will store resources I found and the general gameplan I've devised while researching C.
This may change over time as I learn about the language, but these seem to be some of the most common footguns and concepts folks stumble over.

### Tier 1 - Fundamentals

#### 1. Dynamic Vector

- A growable array, similar to `std::vector` in C++ or `Vec` in Rust:
  - Should resize dynamically
  - Push/Pop, Insert/Remove, Clear functionality
  - Handle allocation failures gracefully
- Resources:
  - [Dynamic Arrays in C](https://www.youtube.com/watch?v=lXvPgEaOKXA)
  - [Creating a Dynamic Array in C: A Step-by-Step Guide](https://www.youtube.com/watch?v=Nn_hbAGnBOs)
  - [Implementing a vector-like data structure in C](https://www.youtube.com/watch?v=bQvxQbUzZZM)
  - [GeeksForGeeks - Dynamic Array in C](https://www.geeksforgeeks.org/c/dynamic-array-in-c/)

#### 2. String Builder

- A buffer that grows as I append text.
  - Useful for constructing strings without constant reallocations.
- Resources:
  - [Strings in C - Jacob Sorber](https://www.youtube.com/watch?v=5TzFNouc0PE)
  - [why do hackers love strings? - Low Level](https://www.youtube.com/watch?v=fjMrDDj47E8)

#### 3. Arena Allocator

- A simple allocator where a big chunk of memory is handed out in order.
- Resources:
  - [Memory Arenas, Explained Simply - Nic Barker](https://www.youtube.com/watch?v=hI9aN8ZG4vg)
  - [Enter The Arena: Simplifying Memory Management (2023)](https://www.youtube.com/watch?v=TZ5a3gCCZYo)
  - [An Introduction to Arenas in C - Ali Awan](https://www.youtube.com/watch?v=5uuTS1xN0X0)

### Tier 2 - Intermediate Structures

#### 4. Ring Buffer

- A circular buffer used for fixed-size queues, audio processing, and IPC.
- Resources:
  - [Data Structures: What is Circular Array / Ring Buffer / Dequeue? - CS Hero](https://www.youtube.com/watch?v=hOPYEI_d50s)
  - [Circular Buffer Implementation in C - TechVedas.learn](https://www.youtube.com/watch?v=uvD9_Wdtjtw)
  - [Interrupt Safe Ring Buffer - Low Byte Productions](https://www.youtube.com/watch?v=uIJnATS9j_0)
  - [Implementing a Circular Queue in C - Jacob Sorber](https://www.youtube.com/watch?v=oyX30WVuEos)
  - [Creating a Circular Buffer in C and C++ - Embedded Artistry](https://embeddedartistry.com/blog/2017/05/17/creating-a-circular-buffer-in-c-and-c/)

#### 5. Pool Allocator

- Allocates fixed-size blocks from a pool. Useful for stable pointers.
- Resources:
  - [An Introduction to Pool Allocators in C - Ali Awan](https://www.youtube.com/watch?v=XNJCs64dDqY)
  - [What is an object pool, and how to create one in C? - Jacob Sorber](https://www.youtube.com/watch?v=CpgsQLSc7KY)
  - [Writing a simple pool allocator in C - 8dcc](https://8dcc.github.io/programming/pool-allocator.html)

#### 6. Hash Table (Open Addressing)

- A hash map storing key/value pairs with collision resolution.
  - [What is a HashTable Data Structure - Paul Programming](https://www.youtube.com/watch?v=MfhjkfocRR0)
  - [Understanding and implementing a Hash Table (in C) - Jacob Sorber](https://www.youtube.com/watch?v=2Ti5yvumFTU)
  - [Learn Hash Tables in 13 minutes - Bro Code](https://www.youtube.com/watch?v=FsfRsGFHuv4)
  - [Faster than Rust and C++: the PERFECT hash table - strager](https://www.youtube.com/watch?v=DMQ_HcNSOAI)

### Tier 3 - Infrastructure  Tools

For now these are rough ideas. Once I complete the projects above, I'll refresh this section with more details.

#### 7. Logger

- Prints messages with levels (DEBUG, INFO, WARN, ERROR), optionally using colors.

#### 8. Job Queue (Task System)

- A simple FIFO queue of function pointers and associated data.

#### 9. Minimal Test Harness

- A tiny custom testing framework.

#### 10. Scope Guard / RAII utilities

- A poor man's RAII
  - Small header-only helpers for scope-based cleanup patterns.
  - Macros to guarantee cleanup runs when leaving a function.
  - Used by examples and tests to keep resource-handling code consistent and less error-prone.

## Theming / Presentation Layer

The C modules themselves will be neutral, however, my goal is to build a system of CLI demos and/or a WASM showcase.
I'm a bit of a 40k nerd, and love the Adeptus Mechanics vibe, so I've decided to theme the presentation layer around AdMech aesthetics.
My goal is to include, roughly, the following:

- Terminal palettes inspired by Mechanicus cyber-ritual aesthetics
- ASCII borders and glyphs
- Module names referencing "rites", "litanies", "cogitators", or "noospheric diagnostics"

To be clear, theming will NOT effect:

- API Clearly
- Naming conventions within the codebase
- Architectural decisions
- Documentation correctness

The goal is for the AdMech theme to be purely presentational.

## Quality Goals

- Every module must have tests to confirm the code actually works.
- No memory leaks, no out-of-bounds access, and no undefined behavior.
- Each module should document how long operations take (Big-O practice)
- Every public function should explain who owns which memory, and when to free it.
- Include simple init/teardown examples.
- The final library must work cleanly under `valgrind` and `asan` where applicable.

## Showcase Goals

- Provide WebAssembly demos where possible.
- Mechanicus-themed presentation but keeping the code clean.
- Include write-ups explaining:
  - how each module works
  - what problems it solves
  - how memory is managed
  - comparisons to higher-level languages like Rust and Python.

## Stretch Goals

- Embedded-friendly "no malloc" mode
- Performance benchmarks
