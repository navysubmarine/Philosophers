# ⋆˚✰ ݁˖⭑. Philosophers ⋆˚✰ ݁˖⭑.

> Concurrency, mutexes & dining philosophers — a 42 project
> 
> by **marthoma** · [subject PDF](https://cdn.intra.42.fr/pdf/pdf/199862/en.subject.pdf)

---

## ⋆˚✰ ݁˖⭑. Description ⋆˚✰ ݁˖⭑.

This project is an introduction to concurrent programming — specifically multithreading — through the classic *dining philosophers problem*.

**Thread** — a logical set of instructions inside a process, managed by the OS kernel. Threads share the same memory space but each has its own instruction pointer. When two threads try to modify the same variable simultaneously, the value gets corrupted — this is called a **data race**.

To prevent data races, we use **mutexes** (mutual exclusion locks). A mutex ensures that only one thread can access a protected resource at a time — others must wait until it's released.

**The simulation** — philosophers sit at a round table with one fork between each pair of neighbours. To eat their spaghetti, a philosopher needs two forks. The forks are mutexes. Each philosopher loops through three states: **thinking → eating → sleeping**. If a philosopher goes too long without eating, they die and the simulation stops.

> This project builds on concepts from *Pipex*, which covered processes — here we focus on threads instead.

---

## ⋆˚✰ ݁˖⭑. Usage ⋆˚✰ ݁˖⭑.

Compile the project:

```bash
make
```

or 

```bash
make good
```

Then run the simulation with the following arguments:

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

All times are in **milliseconds**. The last argument is optional — if provided, the simulation ends once every philosopher has eaten at least that many times.

| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers (and forks) at the table |
| `time_to_die` | Time (ms) before a philosopher dies if they haven't started eating |
| `time_to_eat` | Time (ms) it takes to eat (holds both forks during this) |
| `time_to_sleep` | Time (ms) spent sleeping before thinking again |
| `[...must_eat]` | *(optional)* Simulation ends when every philosopher has eaten this many times |

### Examples

Nobody should die:
```bash
./philo 5 800 200 200
```

Nobody should die:
```bash
./philo 4 410 200 200
```

Philosopher 1 should die:
```bash
./philo 4 310 200 100
```

---

## ⋆˚✰ ݁˖⭑. Resources ⋆˚✰ ݁˖⭑.

- [codequoi.com — Threads, mutex et programmation concurrente en C](https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/)
- [philosophers-visualizer](https://nafuka11.github.io/philosophers-visualizer/) — visualize your simulation in real time
- [42-philosophers-tester](https://github.com/dantonik/42-philosophers-tester) — automated test suite on GitHub

---

## ⋆˚✰ ݁˖⭑. AI Use ⋆˚✰ ݁˖⭑.

This project felt pretty straightforward (especially compared to minishell), so AI didn't play a big role. I used Claude to generate some debug print functions to inspect my structs, and occasionally to help restructure functions into norminette compliance.

---

*⋆˚✰ ݁˖⭑. ⋆˚✰ ݁˖⭑. ⋆˚✰ ݁˖⭑.*
