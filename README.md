
# philosophers

## Description 📄

***philosophers*** is a project based on the classic synchronization and concurrency problem, where multiple processes require limited resources. The project was written in C and utilizes the POSIX library ***pthreads***. Built as a school project at 42 Warsaw.

## ❔The problem
The classic synchronization problem known as the Dining Philosophers Problem was formulated by Edsger Dijkstra to illustrate the complexities of allocating resources among multiple processes in a concurrent system. In this problem, ***n*** philosophers sit around a table, each engaged in a repetitive cycle of thinking, sleeping and eating. The philosophers need two forks to eat, but there are only ***n*** forks available, leading to potential conflicts and the need for a synchronization mechanism to ensure that no philosopher starves.

## Why It Matters 🧠
Understanding and solving the Dining Philosophers Problem is crucial for grasping fundamental concepts in operating systems, such as:
* Deadlock: Situations where a set of processes are unable to proceed because each is waiting for a resource held by another.
* Starvation: Scenarios where a process is perpetually denied necessary resources to proceed.
* Concurrency: The ability to manage multiple processes that are executing simultaneously, ensuring they do not interfere with each other.
By tackling this problem, we develop a deeper understanding of how to manage resource allocation in concurrent systems, which is essential for building efficient and reliable software.

## ⚙️ How it works:

To compile the program:
```bash
make
```

To execute the simulation:
```bash
./philo <no_philo> <time_to_die> <time_to_eat> <time_to_sleep> [<no_times_a_philosopher_should_eat>]
```
Replace the placeholders with actual values:
* no_philo: Number of philosophers
* time_to_die: Time (in milliseconds) a philosopher can live without eating
* time_to_eat: Time (in milliseconds) it takes for a philosopher to eat
* time_to_sleep: Time (in milliseconds) a philosopher spends sleeping
* no_times_a_philosopher_should_eat: (Optional) Number of times each philosopher must eat before the program ends. If not specified, the philosophers will continue indefinitely.

## 🚫Project's restrictions
* Any data races were forbidden
* Usage of a global variable was forbidden
* A displayed state message shouldn't have been mixed up with another message
* A message announcing a philosopher's death shouldn't have been displayed no more than 10ms after the actual death of the philosopher.

## 📌 Notes
- **The bonus part was not finished**
- **Bugs?** If you encounter any bugs, don't hesitate to submit a pull request! Contributions are always welcome. ✨

- **For 42 Students:** 📢 This repository is meant as a guide at most. **Don't cheat, learn!** <3 

- **Created in January 2025** as part of 42's Common Core at **42 Warsaw**🌍
