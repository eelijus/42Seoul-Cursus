/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujilee <sujilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 09:41:27 by sujilee           #+#    #+#             */
/*   Updated: 2022/03/25 13:47:28 by sujilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_info(int argc, char **argv, t_info *info)
{
	memset(info, 0, sizeof(t_info));
	info->num_of_must_eat = -1;
	info->num_of_philos = ft_atoi(argv[1]);
	info->time_to_die = (unsigned long)ft_atoi(argv[2]);
	info->time_to_eat = (unsigned long)ft_atoi(argv[3]);
	info->time_to_sleep = (unsigned long)ft_atoi(argv[4]);
	if (argc == 6)
		info->num_of_must_eat = ft_atoi(argv[5]);
	pthread_mutex_init(&info->print, NULL);
	info->start = ft_gettimeofday();
	return (TRUE);
}

int		init_philo(t_info *info, t_philo **philo)
{
	int	i;

	//ö���� �����ŭ philo ����ü ����
	*philo = (t_philo *)malloc(sizeof(t_philo) * info->num_of_philos);
	if (*philo == 0)
		return (FALSE);
	//��ũ�� �޸𸮵� ö���� �����ŭ �Ҵ�����(������ �迭ó�� ���Ŵϱ�)
	info->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info->num_of_philos);
	if (info->fork == 0)
	{
		free(*philo);
		return (FALSE);
	}
	//memset �Լ��� �� 0���� �ʱ�ȭ��
	memset(*philo, 0, sizeof(t_philo) * info->num_of_philos);
	i = -1;
	//��Ź�� �ð�������� �ɾ��ִ� ö���ڵ鿡�� �˸��� ������ �Ҵ�����
	while (++i < info->num_of_philos)
	{
		pthread_mutex_init(&info->fork[i], NULL);
		(*philo)[i].info = info;
		(*philo)[i].num = i + 1;
		(*philo)[i].eat = ft_gettimeofday();
		(*philo)[i].eat_num = 0;
		(*philo)[i].right_fork = i;
		(*philo)[i].left_fork = i + 1;
	}
	(*philo)[info->num_of_philos - 1].left_fork = 0;
	return (TRUE);
}


void	init_table(t_info *info, t_philo *philo)
{
	pthread_t	state;
	int			i;

	// ���� ������ �������� 
	pthread_create(&state, NULL, handle_state, philo);
	i = -1;
	//ö���� �����ŭ �ݺ��� ���鼭 ������ ������� ��������
	while (++i < info->num_of_philos)
		pthread_create(&philo[i].thread, NULL, handle_loop, &philo[i]);
	//������ �����带 ���ν�Ŵ...�� ������ ����
	pthread_join(state, NULL);
	i = -1;
	while (++i < info->num_of_philos)
		pthread_join(philo[i].thread, NULL);
}