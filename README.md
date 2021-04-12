# philosophers
Philosophers 42

Threads, processes.
https://en.wikipedia.org/wiki/Dining_philosophers_problem

To test program:
1) make
2) ./philo_* a b c d e
where:
a - (integer) amount of philosophers
b - (integer) time to die (being hangry more than this time will cause death)
c - (integer) time to eat (meal time)
d - (integer) time to sleep (sleep time)
e - (integer) is optional. Amount of meal that will make philosopher full.

If philosopher will stay hangry more than "b", he will die.

Examples:
./philo_one 4 400 150 75
./philo_two 4 400 150 75 5
./philo_three 3 500 200 100 5
