```markdown
# Philo

An implementation of the classic [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) in C using POSIX threads. The primary aim is to demonstrate concurrency, resource sharing, and thread synchronization.

---

## Table of Contents
1. [Introduction](#introduction)
2. [Project Structure](#project-structure)
3. [How It Works](#how-it-works)
4. [Building](#building)
5. [Usage](#usage)
6. [Example](#example)
7. [Additional Notes](#additional-notes)
8. [Author](#author)

---

## Introduction

The Dining Philosophers Problem describes a scenario where a number of philosophers sit around a table, each alternating between eating, thinking, and sleeping. Every philosopher needs two forks (shared resources) to eat. The core challenge is to ensure that:
- No two philosophers can hold the same fork simultaneously.
- No philosopher starves indefinitely.

This solution focuses on:
- **Thread creation** using `pthread_create()`.
- **Mutex locks** for resource (fork) protection.
- **Timing** using `gettimeofday()` for simulating real-time events (eating, sleeping, etc.).
- **Safe termination** when a philosopher dies (exceeds `die_time`), or when all have eaten a required number of meals (if specified).

---

## Project Structure

```plaintext
philo
├── Makefile
├── main.c
├── parsing.c
├── philo.h
├── philo_action.c
└── utils
    ├── ft_atoi.c
    ├── ft_strchr.c
    ├── ft_strlen.c
    └── utils.h
```

- **Makefile**: Script to compile and manage the project.
- **main.c**: Entry point; sets up the simulation, spawns threads, and supervises philosopher states.
- **parsing.c**: Parses and validates the command-line arguments, initializes data structures.
- **philo_action.c**: Implements behaviors for the philosophers (eating, sleeping, thinking).
- **philo.h**: Header file containing project-wide structures and function prototypes.
- **utils**: Contains helper functions (`ft_atoi`, `ft_strlen`, etc.) and their header file.

---

## How It Works

1. **Initialization**  
   - Command-line arguments are read and validated.  
   - The `t_data` structure holds simulation-wide parameters (e.g., `die_time`, `eat_time`, etc.).  
   - An array of `t_philo` structures is allocated, each representing a philosopher.  
   - A fork (mutex) is associated with each philosopher.

2. **Thread Creation**  
   - Philosophers are split into two creation groups (even-indexed first, then odd-indexed) to mitigate immediate contention for resources.  
   - Each philosopher thread runs in an infinite loop: eat → sleep → think.

3. **Eating**  
   - A philosopher grabs the fork on their left, then the fork on their right (mutex locking).  
   - The philosopher prints status messages, updates `last_eat`, increments local counters, and then releases both forks (mutex unlocking).

4. **Sleeping and Thinking**  
   - After eating, a philosopher sleeps for `sleep_time`.  
   - Once sleeping is finished, the philosopher thinks until they decide to eat again.

5. **Monitoring**  
   - The `main` thread continuously checks:  
     - Has any philosopher exceeded their `die_time` since last meal?  
     - Have all philosophers eaten the required number of times (if `eat_nbr` is set)?

6. **Termination**  
   - If a philosopher dies or everyone has eaten enough, the simulation stops.  
   - All threads are joined (or allowed to exit naturally), and mutexes/memory are cleaned up.

---

## Building

1. **Clone / Download** this repository (ensure you are in the `philo` directory).
2. Run `make`:
   ```bash
   make
   ```
   This creates an executable named `philo`.

3. To remove object files:
   ```bash
   make clean
   ```
4. To remove both object files and the executable:
   ```bash
   make fclean
   ```
5. To rebuild everything from scratch:
   ```bash
   make re
   ```

---

## Usage

**Syntax:**
```bash
./philo <number_of_philosophers> <die_time> <eat_time> <sleep_time> [number_of_meals]
```

**Required Arguments:**
1. **number_of_philosophers** – total number of philosophers/threads.
2. **die_time** – time (in ms) a philosopher can live without eating.
3. **eat_time** – time (in ms) spent eating per cycle.
4. **sleep_time** – time (in ms) spent sleeping per cycle.

**Optional Argument:**
- **number_of_meals** – if specified, the simulation ends once each philosopher has eaten these many times.

**Constraints:**
- `number_of_philosophers` must be between 1 and 200.
- `die_time`, `eat_time`, and `sleep_time` must be ≥ 60 ms.
- All values must be valid integers (no negative numbers or non-digit characters).

---

## Example

1. **Minimum Arguments**  
   ```bash
   # 4 philosophers, 200ms die_time, 100ms eat_time, 100ms sleep_time
   ./philo 4 200 100 100
   ```

2. **Optional Meals**  
   ```bash
   # 5 philosophers, 800ms die_time, 200ms eat_time, 200ms sleep_time,
   # each philosopher must eat 5 times
   ./philo 5 800 200 200 5
   ```

---

## Additional Notes

- Internally, the program uses `usleep` in combination with timestamps for more precise timing (instead of just relying on `usleep` alone).  
- The code has been tested on a Unix-like environment (macOS/Linux). Behaviors on other systems may differ.

---

## Author

- **yamrire**  
  \[ [Email](mailto:yamrire@student.42.fr) \]  
  \[ [42 Profile](https://profile.intra.42.fr/users/yamrire) \]  

Feel free to contribute or reach out for any questions or improvements!
```