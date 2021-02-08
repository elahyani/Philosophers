#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define PHILOS 5
#define DELAY 5000
#define FOOD 5
	
pthread_mutex_t forks[PHILOS];
pthread_t philo[PHILOS];
pthread_mutex_t food_lock;
int sleep_seconds = 0;

int		food_on_table()
{
	    static int food = FOOD;
	    int myfood;
	
	    pthread_mutex_lock (&food_lock);
	    if (food > 0) {
	        food--;
	    }
	    myfood = food;
	    pthread_mutex_unlock (&food_lock);
	    return myfood;
}
	
void	grab_forks(int phil, int c, char *hand)
{
   	pthread_mutex_lock (&forks[c]);
	printf ("Philosopher %d: got %s forks %d\n", phil, hand, c);
}

void	down_forks(int c1, int c2)
{
	pthread_mutex_unlock (&forks[c1]);
	pthread_mutex_unlock (&forks[c2]);
}

void	*philosopher(void *num)
{
	int id;
	int i, left_forks, right_forks, f;

	id = (int)num;
	printf ("Philosopher %d is done thinking and now ready to eat.\n", id);
	right_forks = id;
	left_forks = id + 1;

	/* Wrap around the forkss. */
	if (left_forks == PHILOS)
		left_forks = 0;

	while ((f = food_on_table())) {

		/* Thanks to philosophers #1 who would like to take a nap
			* before picking up the forkss, the other philosophers
			* may be able to eat their dishes and not deadlock.  
			*/
		if (id == 1)
			sleep (sleep_seconds);

		grab_forks (id, right_forks, "right ");
		grab_forks (id, left_forks, "left");

		printf ("Philosopher %d: eating.\n", id);
		usleep (DELAY * (FOOD - f + 1));
		down_forks (left_forks, right_forks);
	}

	printf ("Philosopher %d is done eating.\n", id);
	return (NULL);
}

int		main(int argn, char **argv)
{
	int i;

	if (argn == 2)
		sleep_seconds = atoi(argv[1]);
	pthread_mutex_init (&food_lock, NULL);
	for (i = 0; i < PHILOS; i++)
		pthread_mutex_init (&forks[i], NULL);
	for (i = 0; i < PHILOS; i++)
		pthread_create (&philo[i], NULL, philosopher, (void *)(size_t)i);
	for (i = 0; i < PHILOS; i++)
		pthread_join (philo[i], NULL);
	return 0;
}