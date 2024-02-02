# Dynamic Memory Allocation Simulation

## Overview
This project, developed by me, presents a custom implementation of dynamic memory allocation functions, `malloc` and `free`, using a free list approach. Aimed at demonstrating the underlying mechanisms of memory management in C programming, the project offers a practical exploration of managing heap memory efficiently.

## Features
- **Custom Malloc Implementation:** Utilizes a free list to allocate memory blocks dynamically, ensuring efficient space utilization.
- **Custom Free Implementation:** Allows for the freeing of allocated memory blocks, making them available for future allocations.
- **Space Efficiency:** Implements strategies to minimize space wastage and manage memory fragmentation.
- **Memory Block Management:** Includes functionalities for merging adjacent free blocks to combat fragmentation.
- **Struct-Based Linked List:** Employs a linked list for free blocks tracking, with each node containing metadata for memory management.

## Getting Started
To run the simulation:
1. Clone the repository to your local machine.
2. Compile the C files using your preferred compiler, e.g., `gcc -o memory_simulation main.c`.
3. Run the executable, e.g., `./memory_simulation`.

## Usage
- The program simulates memory allocation and deallocation processes, showcasing how the custom `malloc` and `free` functions manage memory.
- Detailed logs provide insights into the allocation/deallocation patterns and the state of the heap at various stages.

## Reflections and Learning Outcomes
- Gained deep insights into dynamic memory management and the complexities of implementing efficient allocation/deallocation functions.
- Understood the importance and challenges of managing memory fragmentation and the benefits of a linked list in dynamic memory allocation.

## Future Improvements
- Implementation of a shrink function for optimizing memory usage further.
- Consideration of a double-linked list for enhanced management of memory blocks.

## Acknowledgments
Special thanks to the resources and tutorials that provided invaluable guidance:
- Burelle M. (2009). A Malloc Tutorial.
- Luu D. (2014). Malloc Tutorial.

For more information and detailed documentation on the implementation, please refer to the project report included in the repository.
