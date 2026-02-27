# tpmp-lab2-task3

## Overview

This repository contains Task 3 of the laboratory work.  
The goal of this task is to implement a C program using structures and organize the project according to the KIS-2 model (Client–Interface–Server).  
The project is built using the make utility and includes CI configuration with GitHub Actions.

## Author

Shamruk Polina Alexandrovna  
Course: 2  
Group: 11  

## Usage

Clone the repository:

    git clone git@github.com:Polina707-lab/tpmp-lab2-task3.git
    cd tpmp-lab2-task3

Build the project:

    make

Run the program:

    ./my_program

Clean build files:

    make clean

## Additional Notes

- The source code is located in the src/ directory.
- The project follows the KIS-2 architecture model.
- The project is compiled using gcc with flags:
  - -Wall
  - -Wextra
  - -Wpedantic
  - -std=c11
- Continuous Integration is configured in .github/workflows/ci.yml.
- Repl.it is not used for this assignment, as required.
