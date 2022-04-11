/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujilee <sujilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:17:25 by okwon             #+#    #+#             */
/*   Updated: 2022/02/17 21:44:01 by sujilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		main(int ac, int **av, char **env)
{
	t_data data;

	// minishell���� ���� �ñ׳� ����
	//ctrl + c -> ����
	signal(SIGINT, signal_handler);
	//ctrl + W �Է� �� -> �ھ� ����
	signal(SIGQUIT, SIG_IGN);


	//term1 : �̴Ͻ����� ����� �͹̳�
	//ǥ���Է��� �Ӽ��� term1��??
	tcgetattr(STDIN_FILENO, term1);

	
}