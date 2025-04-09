#include "philo_bonus.h"

void free_data(t_table *data)
{
	if (!data)
		return ;
	if (data->philosophers)
		free(data->philosophers);
	if (data->pids)
		free(data->pids);
	sem_close(data->forks_sem);
	sem_close(data->print_sem);
	sem_close(data->each_eat_sem);
	sem_unlink(FORKS_SEM_NAME);
	sem_unlink(PRINT_SEM_NAME);
	sem_unlink(EACH_EAT_SEM_NAME);
}

int	check_die(t_philosopher *philo)
{
	sem_wait(philo->table->last_eat_time_sem);
	if (get_time_in_ms() - philo->last_meal_time >= philo->table->time_to_die)
	{
		log_action(philo, "died", philo->table, 1);
		exit(1);
	}
	sem_post(philo->table->last_eat_time_sem);
	return (0);
}

int	check_eat(t_philosopher *philo)
{
	sem_wait(philo->table->each_eat_sem);
	if (philo->meals_eaten == philo->table->must_eat_count)
	{
		sem_post(philo->table->each_eat_sem);
		exit (0);
	}
	sem_post(philo->table->each_eat_sem);
	return (0);
}


void	got_eat_time(t_philosopher *philo)
{
	sem_wait(philo->table->last_eat_time_sem);
	philo->last_meal_time = get_time_in_ms();
	sem_post(philo->table->last_eat_time_sem);
}

static void try_take_forks_and_eat(t_philosopher *philo)
{

	sem_wait(philo->table->forks_sem);
	log_action(philo, "has taken a fork", philo->table, 0);
	sem_wait(philo->table->forks_sem);
	log_action(philo, "has taken a fork", philo->table, 0);
	log_action(philo, "is eating", philo->table, 0);
	usleep(philo->table->time_to_eat * 1000);
	sem_post(philo->table->forks_sem);
	sem_post(philo->table->forks_sem);
	got_eat_time(philo);
	sem_wait(philo->table->each_eat_sem);
	philo->meals_eaten++;
	sem_post(philo->table->each_eat_sem);
}

static void *monitor_death(t_philosopher *philo)
{
	while (1)
	{
		if (check_die(philo) == 1 || check_eat(philo) == 1)
			break ;
	}
	return (NULL);
}

void philosopher_routine(t_philosopher *philo)
{
	if (philo->table->num_philosophers == 1)
		do_single_philo(philo);
	pthread_create(&philo->monitoring_thread, NULL, (void *)monitor_death, philo);
	got_eat_time(philo);
	while (1)
	{
		try_take_forks_and_eat(philo);
		log_action(philo, "is sleeping", philo->table, 0);
		usleep(philo->table->time_to_sleep * 1000);
		log_action(philo, "is thinking", philo->table, 0);
	}
	pthread_join(philo->monitoring_thread, NULL);
	exit(0);
}

void create_philosophers(t_table *data)
{
	int i;

	data->start_time = get_time_in_ms();

	i = -1;
	while (++i < data->num_philosophers)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].last_meal_time = LLONG_MAX;
		data->philosophers[i].meals_eaten = 0;
		data->philosophers[i].table = data;

		data->pids[i] = fork();
		if (data->pids[i] == 0)
			philosopher_routine(&data->philosophers[i]);
		else if (data->pids[i] == -1)
			throw_err(FORK_ERROR, data);
	}
}

void start_simulation(t_table *data)
{
	int status;
	int i;

	create_philosophers(data);
	i = -1;
	while (++i <= data->num_philosophers)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) > 0)
		{
			i = -1;
			while (++i < data->num_philosophers)
				kill(data->pids[i], SIGKILL);
			break ;
		}
	}
	free_data(data);
}

int	main(int argc, char *argv[])
{
	t_table	data;

	if (argc < 5 || argc > 6)
        throw_err(ARGUMENT_ERROR, NULL);
	init_data(&data, argc, argv);
	start_simulation(&data);
	return (0);
}
