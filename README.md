# Philosophers (42 Project) — Mandatory Part Only

## 📘 Overview

The **Philosophers** project introduces concepts of concurrency, threads, mutexes,
race conditions, timing precision, and deadlock avoidance.  
Each philosopher alternates between **thinking**, **eating**, and **sleeping**,
using shared forks that must be accessed with proper synchronization.

This repository contains the **mandatory part only**, following all requirements
of the 42 subject.

---

## 🧵 Program Behavior

### Usage
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]

markdown
Copiar código

### Parameters
- `number_of_philosophers` — number of philosophers and forks  
- `time_to_die` — time (ms) before a philosopher dies without eating  
- `time_to_eat` — time (ms) spent eating  
- `time_to_sleep` — time (ms) spent sleeping  
- `number_of_meals` — optional: stops simulation when all philosophers have eaten this many times  

---

## 🛠 Implementation Summary

### Threads
- One thread per philosopher.
- Separate monitoring routine that checks:
  - If a philosopher died.
  - If all philosophers have eaten enough meals.

### Mutexes
- One mutex per fork.
- Mutex for printing to keep output consistent.
- Mutexes to protect shared state (stop condition, meal counters).

### Avoiding Deadlock
- Fork acquisition follows a strict order or odd/even strategy.
- Prevents all philosophers from waiting indefinitely.

### Timing
- Custom timestamp function for millisecond precision.
- Each philosopher tracks when they last ate.
- Accurate checks prevent false deaths.

### Termination
- Simulation stops immediately if a philosopher dies.
- If a meal limit is provided, ends when all philosophers meet the requirement.

---

## ▶ Compilation

The project comes with a Makefile supporting the required rules:

make # compile philo
make clean # remove object files
make fclean # remove objects + binary
make re # rebuild everything

yaml
Copiar código

Compiler flags:
-Wall -Wextra -Werror -pthread

yaml
Copiar código

---

## ▶ Running Examples

./philo 5 800 200 200

sql
Copiar código

With required meals:

./philo 5 800 200 200 3

yaml
Copiar código

---

## 📦 Example Output

0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
201 1 is sleeping
201 2 has taken a fork
...

yaml
Copiar código

(Exact order varies depending on the scheduler.)

---

## 📚 What This Project Teaches

- Thread creation and lifecycle  
- Mutual exclusion (mutex)  
- Protecting shared data  
- Handling race conditions  
- Deadlock avoidance  
- Timing accuracy  
- Structured C design following 42 norms  

---

## ✔ Mandatory Constraints Observed

- No data races  
- No deadlocks  
- No global variables  
- Clean exit on death or completion  
- Accurate timestamps  
- Strict compliance with the subject  

---

## 📄 License

This project follows the academic rules of the 42 curriculum.  
It is meant to document and present the work, not to be copied for evaluation.
