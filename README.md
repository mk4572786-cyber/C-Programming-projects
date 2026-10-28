# SimpleC-Vote

A lightweight, robust command-line electronic voting system written in C. **SimpleC-Vote** allows an administrator to register a pool of candidates, assign unique election symbols, manage active ballot inputs from voters, and calculate final results with tie detection.

## Features

- **Dynamic Candidate Registration:** Register between 1 and 10 candidates with multi-word names (e.g., "Jane Doe").
- **Unique Symbol Allocation:** Assigns distinct typographical symbols (`!`, `@`, `#`, `$`, `%`, `^`, `&`, `*`, `~`, `+`) without allowing duplicate assignments.
- **Input Sanitization:** Protects against invalid character entries, misformatted integers, and buffer overflows during setup and voting phases.
- **Automated Tallying & Results:** Computes total vote counts, announces the winning candidate and their assigned symbol, or correctly identifies a tie.

## Getting Started

### Prerequisites

You need a standard C compiler installed on your system (such as `gcc`, `clang`, or MSVC).

### Compilation

Compile the program using a terminal command like `gcc`:

```bash
gcc -o simple_vote main.c
```
*(Replace `main.c` with the actual filename if saved differently).*

### Execution

Run the compiled binary:

```bash
./simple_vote
```

## How to Use

1. **Set Candidate Count:** Enter the total number of candidates participating (must be between `1` and `10`).
2. **Assign Symbols and Names:** 
   - Select an available symbol index from the displayed list for each candidate.
   - Enter the full name of the candidate.
3. **Set Voter Count:** Enter the total number of people voting.
4. **Cast Ballots:** For each voter, the current candidate lineup and symbols are displayed. Enter the index corresponding to your preferred candidate.
5. **View Results:** After all ballots are processed, the system outputs the winner or flags a tie.
