/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujilee <sujilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 09:55:21 by sujilee           #+#    #+#             */
/*   Updated: 2022/02/14 10:40:53 by sujilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	print_error( t_pipe *mypipe, char *cmd, char *mess)
{
	char *error;

	//error : "Ŀ�ǵ� + message"
	error = ft_strjoin(cmd, mess);
	//�������� ���fd(�Ƹ� ǥ�����)�� ���� ���
	write(mypipe->write_fd, error, ft_strlen(error));
	free(error);
	exit(1);
}

//ȯ�溯�� �긣�� ���ö� �� PATH ã�� �ǰ�?
char	**find_path(char **envp)
{
	int	i;
	char	**cmd;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			break ;
		i++;
		// : �� �����ڷ� cmd�� ���Ե�
		cmd = ft_split(envp[i] + 5, ':');
		return (cmd);
	}
}

char	*make_path(char *cmd, char **envp)
{
	char	**envp_split;
	char	*cmd_path; //Ŀ�ǵ尡 ����� ���
	char	*temp_cmd;
	char	**exec_cmd; //����� Ŀ�ǵ�
	int		i;

	//access()�� cmd�� ���� Ȯ���Ѵ�.
	//���� �ּ� : cmd, üũ�� �� : �������� | ���� ����
	//������ �����ϰ� ������ �����ϸ� cmd ��ȯ
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	//���ø��� ����� ������ �������� Ŀ�ǵ带 ����
	exec_cmd = ft_split(cmd, ' ');

//

	//strjoin���� "/Ŀ�ǵ�" �� ����
	temp_cmd = ft_strjoin("/", exec_cmd[0]);
	envp_split = find_path(envp);
	i = 0;
	while (envp_split[i])
	{	
		//cmd�� Ÿ�� = "���/Ŀ�ǵ�"
		cmd_path = ft_strjoin(envp_split[i], temp_cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
			break;
		i++;
	}
	//�� �̻� ���빰�� ������ ��, ��ɾ ������ �� ���ڿ� ��ȯ!
	//"command not found"
	if (!envp_split[i])
		return ("");
	return (cmd_path);

}
