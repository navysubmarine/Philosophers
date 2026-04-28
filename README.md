*This project has been created as part of the 42 curriculum by marthoma.*

[Subject](https://cdn.intra.42.fr/pdf/pdf/199862/en.subject.pdf)

# ⋆˚✰ ݁˖⭑. Description *⋆˚✰ ݁˖⭑.

This project was made as an introduction to concurrent programming, multithreading to be precise. 

It is common to feel the need to optimize a process when it's too slow, for example when displaying an image on screen, at high speed. In order to do that, you can choose to build your program in a non-sequential manner, in concurrent manner. Doing so, your program will be able to execute different tasks at the exact same time, therefore gaining a lot of time. There are different types of concurrent programming : processes (child & parent), threads and multiplexes, with this project, we will be focusing on threads, and we've already worked on processes with the Pipex project. 

A thread is a logical set of instructions inside a process, which is automatically handled by the kernel of the OS. Each thread has its own instruction pointer, but they all share the same memory, since they live in the same process. But this shared memory can cause problems, when two threads try to access (modify) the same variable at the same moment, therefore corrupting the variable's value. When this happens it is called a data race. To prevent it, you have to use what we call mutexes. A mutex (= mutual exclusion) is like a protection on a specific variable or action the threads can execute, to prevent them from doing it at the exact same time. When one of them has locked it, they have to wait until it has been unlocked, and then lock it themselves.

With this project, threads are metaphorically represented by philosophers, each of them having a routine they repeat, over and over : thinking, eating and sleeping. There is a table in front of them, with as many forks as there are philosophers. In order to eat their spaghetti, they have to pick up two forks, therefore stopping their two neighbours from eating. Those forks are mutexes. If they don't eat for too much time, they die and the simulation stops for everyone. If they reached the appropriate number of times each of them has to eat, the simulation ends without anyone dying.

# *⋆˚✰ ݁˖⭑. Instructions *⋆˚✰ ݁˖⭑.

To be able to launch the simulation you have to make the executable file :

```bash
make
```

And then run it with the following arguments :


```bash
./philo time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

for example :

```bash
./philo 5 800 200 200
```

```bash
./philo 4 410 200 200
```


# *⋆˚✰ ݁˖⭑. Resources  *⋆˚✰ ݁˖⭑.

Codequoi.com : [Threads, mutex et programmation concurrente](https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/).

Philosophers visualizer : [here](https://nafuka11.github.io/philosophers-visualizer/).

Philosophers tester on GitHub : [here](https://github.com/dantonik/42-philosophers-tester).

# *⋆˚✰ ݁˖⭑. AI Use  *⋆˚✰ ݁˖⭑.

I thought this project was pretty straightforward (especially compared to minishell), therefore it didn't use a lot of AI to help me. I used Claude to make some "print" functions, to print everything I had in my structures, which I used for debugging. I also used it to help me restructure some functions, and make them norminette compliant.