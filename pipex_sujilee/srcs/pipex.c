/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujilee <sujilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 09:13:59 by sujilee           #+#    #+#             */
/*   Updated: 2022/02/14 12:45:42 by sujilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"


//������ ��
void	second_part(t_pipe *mypipe, char **argv, char **envp)
{
	t_exec	exec;

	close(mypipe->pipe_fd[1]);

	//
	//outfile�� ������ �׳� ����� �Ǵϱ�. 0664 : Chmod�� 644�� 
	exec.fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (exec.fd < 0)
		print_error(mypipe, argv[4], ": No such file or directory\n");
	//cmd2 �۾�
	exec.cmd_split = ft_split(argv[3], ' ');
	exec.cmd_path = make_path(argv[3], envp);
	//�������Ա��� ǥ���Է�(0)�� ����
	dup2(mypipe->pipe_fd[0], STDIN_FILENO);
	//exec.fd(outfile)�� ǥ�����(1)�� ����
	dup2(exec.fd, STDOUT_FILENO);
	if (ft_strncmp(exec.cmd_path, "", 1) != 0)
	{
		//execve()�� cmd2�� ����. �׷� ���� dup2�� ���� ��η� outfile�� ����� ���
		//��� : exec.cmd_path ��ɾ� : exec.cmd_split
		exec.status = execve(exec.cmd_path, exec.cmd_split, envp);
		if (exec.status == -1)
			print_error(mypipe, "", "execute error\n");
	}
	else
		print_error(mypipe, argv[3], ": command not found\n");
	//���� ���μ����� ��������� �ȵǴϱ� exit(0)
	exit(0);
}

//������ ��
void	first_part(t_pipe *mypipe, char **argv, char **envp)
{
	t_exec	exec;

	//���⸦ ���ϰ� �ޱ⸸ �ϰڴ�. �Է��� ������ �Ա� close
	close(mypipe->pipe_fd[0]);
	//���ڷ� ���� ù path�� open�ϰ� �� fd���� exec.fd�� �Ҵ�
	exec.fd = open(argv[1], O_RDONLY);
		if (exec.fd < 0)
		print_error(mypipe, argv[1], " : No such file or directory");
	//������ �����ڷ� �ؼ� ��ɾ ���߹迭�� �ɼǱ��� ��Ƴ���
	exec.cmd_split = ft_split(argv[2], ' ');
	exec.cmd_path = make_path(argv[2], envp);
	
	//exec.fd(��, infile)�� ǥ���Է�(0)�� ����
	dup2(exec.fd, STDIN_FILENO);
	//mypipe�� �ⱸ�� ǥ�����(1)�� ����
	dup2(mypipe->pipe_fd[1], STDOUT_FILENO);
	

	// ��ɾ� ���� ��θ� ���� ������
	if (ft_strncmp(exec.cmd_path, "", 1) != 0)
	{
		//execve�� exec.cmd_path�� ������ �����Ų��.
		//���� -> ��ɾ �����Ű�� �� ���μ����� ����
		exec.status = execve(exec.cmd_path, exec.cmd_split, envp);
		//���н� ���� ���
		if (exec.status == -1)
			print_error(mypipe, "", " : execute error\n");
	}
	//Ŀ�ǵ尡 ����� �ȵ������� ���� ���
	else
		print_error(mypipe, argv[2], " : command not found\n");
}

void	fork_execute(t_pipe	*mypipe, char **argv, char **envp)
{
	//fork�� �ڽ� ���μ��� ���� & ��ȯ.
	//������ �Ա��� �ش� �ڽ��� pid�� �ִ´�?
	mypipe->pid[0] = fork();
	//�Ա� ��ũ ���� ��
	if (mypipe->pid[0] < 0)
		print_error(mypipe, "", "pid[0] fork error\n");
	//mypipe �Ա��� �ڽ��̸�
	else if (mypipe->pid[0] == 0)
		first_part(mypipe, argv, envp);
	//�ⱸ ��ũ ���� ��
	if (mypipe->pid[1] < 0)
		print_error(mypipe, "", "pid[1]] fork error\n");
	//mypipe �ⱸ�� �ڽ��̸�
	else if (mypipe->pid[1] == 0)
		second_part(mypipe, argv, envp);
}

void	init_pipe(t_pipe *mypipe)
{
	mypipe->write_fd = 0;
	mypipe->pid[0] = 0;
	mypipe->pid[1] = 0;
	mypipe->status = 0;
	// pipe�� ������ش�.
	pipe(mypipe->pipe_fd);

}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	mypipe;
	
	if (argc != 5)
		//���� ���. ����
		print_error("", "argument error\n", &mypipe);
	//mypipe �ʱ�ȭ
	init_pipe(&mypipe);
	//pipex ����, �Ľ� �Լ�
	fork_execute(&mypipe, argv, envp);
	//�Ա� �ݱ�. pipe()�� fd�� �����ޱ� ������ ����� fd�� �ݾ������
	close(mypipe.pipe_fd[0]);
	//�ⱸ �ݱ�. 
	close(mypipe.pipe_fd[1]);
	//wait�Լ��� ���� ���� : �ڽ� ���μ����� ���� ���μ����� �Ǵ� �� ����
	//�θ� ���μ����� �ڽ� ���μ����� exeve()���� ����Ǵ� �� ����
	//������ �Ա��� �����ϸ鼭 ���������� �����.
	waitpid(mypipe.pid[0], &(mypipe.status), 0);
	//������ �ⱸ�� �����ϸ鼭 ���������� �����.
	waitpid(mypipe.pid[1], &(mypipe.status), 0);
	return (0);
}