/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 21:14:36 by sstyx             #+#    #+#             */
/*   Updated: 2022/01/20 16:41:31 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>

# define SLEEP 500

typedef struct s_forks
{
	int				fork;
	pthread_mutex_t	mutex;
}	t_forks;

typedef struct philosopher_args_tag {
	pthread_t			*thread;
	int					philo_num;
	int					time_to_sleep;
	int					time_to_eat;
	int					time_to_die;
	int					death;
	struct timeval		star_time;
	int					number_of_time_to_eat;
	pthread_mutex_t		*deadlock;
	pthread_mutex_t		*write;
}	t_threads;

typedef struct philosopher_tag
{
	int					id_p;
	int					group;
	struct timeval		eatime;
	int					eat;
	pthread_mutex_t		*mutex;
	pthread_mutex_t		*lock;
	t_forks				*forks;
	t_threads			*table;
	int					*how_forks;
	int					iamfull;

}	t_p;

int					ft_atoi(const char *str);
int					ft_isdigit(int c);
void				ft_putstr_fd(char *s, int fd);
int					is_all_digit(char *argv);
int					ft_error(char *str);

int					is_dead(t_p *philo);
int					any_dead(t_p *philo);
long int			o_clock(t_p *philo);
int					my_uslip(int time);
void				*philos(void *philo);
int					parse(int argc, char **argv,
						t_threads *threads, t_forks **forks);
int					check_parse(t_threads *threads, int argc, char **argv);

int					eating(t_p *philo);;
int					sleeping(t_p *philo);
int					thinking(t_p *philo);
void				*life(void *data_data);
// static int			set_forks(t_threads *table, t_forks **forks);
void				*philos(void *philo);
void				free_mem(t_threads *table, t_forks *forks);
void				*check(void *argc);
int					ft_write(t_p *philo, char *str, long time);
void				free_all(t_threads *table, t_p philo);
void				init_p(t_p	*philo, int i);

#endif
