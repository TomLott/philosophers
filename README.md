# philosophers
Philosophers 42

Threads, processes.<br />
https://en.wikipedia.org/wiki/Dining_philosophers_problem
<br />
To test program:<br />
1) make<br />
2) ./philo_* a b c d e<br />
where:<br />
a - (integer) amount of philosophers<br />
b - (integer) time to die (being hangry more than this time will cause death)<br />
c - (integer) time to eat (meal time)<br />
d - (integer) time to sleep (sleep time)<br />
e - (integer) is optional. Amount of meal that will make philosopher full.<br />
<br />
If philosopher will stay hangry more than "b", he will die.<br />
<br />
Examples:<br />
<br />
./philo_one 4 400 150 75<br />
./philo_two 4 400 150 75 5<br />
./philo_three 3 500 200 100 5<br />
