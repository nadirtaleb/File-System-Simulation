# File System Simulation

## Overview
This project is a simple file system simulation written in C++. It allows users to create, manage, and manipulate a hierarchical file system consisting of directories and files. The program supports saving the state of the file system to a file and loading it back, making it a practical example of file I/O operations in C++.

## Features
- **Directory and File Management:**
  - Create directories and files within a hierarchical structure.
  - Move files between directories.
  - List the contents of directories.

- **Persistence:**
  - Save the current state of the file system to a text file.
  - Load a saved file system state from a text file.

- **Smart Pointers for Memory Management:**
  - Uses `std::unique_ptr` to manage dynamic memory safely and efficiently.

- **Error Handling:**
  - Basic error handling to manage file I/O and invalid operations.

## Key Concepts Demonstrated
- **Object-Oriented Programming (OOP):**
  - Inheritance and polymorphism through a base class `FileSystemEntity` and derived classes `File` and `Directory`.
  - Encapsulation of file and directory operations within appropriate classes.

- **Smart Pointers:**
  - Use of `std::unique_ptr` to ensure proper memory management and avoid memory leaks.

- **File I/O:**
  - Saving the file system state to a file and loading it back using text-based serialization.

- **Recursion:**
  - Recursive directory traversal to save and load the entire file system hierarchy.

