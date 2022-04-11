/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujilee <sujilee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:15:49 by okwon             #+#    #+#             */
/*   Updated: 2022/02/17 21:19:47 by sujilee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define DEL 127
# define LEFT 4479771
# define RIGHT 4414235
# define K_UP 4283163
# define DOWN 4348699

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <termcap.h>
# include <term.h>
# include <curses.h>
# include <termios.h>
# include <errno.h>
# include <string.h>
# include "../libft/libft.h"
# include "command.h"

typedef struct	s_glob
{
	char	*ret;
	int		curly_bracket;
}				t_glob;

typedef struct	s_exec
{
	char    **env_path;
	char    **argv;
	char    **split_cmd;
	char	*path;
}				t_exec;

typedef struct	s_cmd
{
	char	*cmd;
	char	*redir;
	char	*next_redir;
	char	*file;
	char	*cur_file;
	int		std_in;
	int		std_out;
}				t_cmd;

typedef struct	s_pipe
{
	char		*cur_cmd;
	int			flag;
	int			old_flag;
	int			*fds;
	int			*old_fds;
}				t_pipe;

// �͹̳� �Է��� ���� ������ ���� ����ü
typedef struct	s_input
{
	int			cflag;	// ctrl-c ����. 0 : ctrl-c�� ������ ����. 1 : ctrl-c�� ����
	int			buf;
	char		*tmp;
	char		*input;
	int			nidx;	// �����丮�� ��� �ε���
	t_list		*log;
}				t_input;

// �͹̳ο� ���� ������ ���� ����ü
typedef struct	s_term
{
	struct termios	term1;	// minishell���� ����� �͹̳�
	struct termios	ori_term;	// ���� �͹̳�. minishell ���� �� �ش� �͹̳η� ����
	char			*cm;	// Ŀ�� ��ġ �̵�
	char			*ce;	// �͹̳ο��� ���� ��ġ�� ���� ����
	int				r;	// �͹̳��� row ��ġ
	int				c;	// �͹̳��� column ��ġ
}				t_term;

// �⺻���� �����͸� ������ ����ü
typedef struct	s_data
{
	char		**cmd;	// minishell���� ����� cmd�� �̸��� ������.
	char		**envp;	// ȯ�溯���� ����
	t_term		term;
	t_input		input;
}				t_data;

/*	signal.c	*/
void	signal_handler(int signo);
int		ctrl_c_func(t_input *input);
void    ctrl_d_func(char *input, struct termios *ori_term);

/*	term.c	*/
void	term_init(struct termios *term1, struct termios *ori_term);
void	delete_end(char **input);
int		nbr_length(int n);
void	get_cursor_position(int *col, int *rows);
int		putchar_tc(int tc);

/*	cmd_utils.c	*/
void	cmd_init(char ***cmd);
int		**fds_set(int row);

/*	cmd.c	*/
void	c_func(t_data *data, t_pipe *pip);
void	execute(t_data *data, t_pipe *pip, int row); //���� row �߰���
void	p_func(char **cmd_split, char *cmd_line,
				int row, int **fds, t_data *data);
void	cmd_handler(char **cmd_split, char *cmd_line, t_data *data);

/*	utils.c	*/
void    prompt(int flag);
void	dfree(char **str);
void	difree(int **darr);
int		dlen(char **darr);

/*	input.c	*/
char	*print_history(t_term *term, t_input *input);
int		input_handler(t_input *input);
int		key_else(t_data *data, t_input *input);
char	*input_recive(t_data *data);

/*	pipe.c	*/
void    c_pipe(int *old_fds, int *fds, int old_flag, int flag);
void    p_pipe(int *old_fds, int *fds);

/*	execute.c	*/
void    execute_input(t_data *data, t_pipe *pipe, int process);
void    print_error(char *massage, t_cmd *cmd);

/*	execute_utils.c	*/
char	**get_argv(char **split,  char *file);
int		make_token(t_cmd *cmd, char *input);
int		make_path(t_exec *exec);
void	exec_init(t_exec *exec, t_cmd *cmd);
void	exec_cmd_init(t_cmd *cmd);

/*	exceute_check.c	*/
int     builtin_cmd_check(t_data *data, char *cmd);
void    redirection_check(t_cmd *cmd);

/*	quote.c	*/
char	*handle_quotes(char *input, t_cmd *cmd);

/*	dollar.c	*/
char	*dollar(int i, char *input, t_cmd *cmd);

/*	ft_echo.c	*/
void	ft_echo(t_cmd *cmd, t_exec exec, t_data *data);

/*	ft_pwd.c	*/
void	ft_pwd(t_cmd *cmd, t_exec exec, t_data *data);

/*	ft_cd.c		*/
void	ft_cd(t_cmd *cmd, char *path, int process);

/*	ft_env.c		*/
void	ft_env(t_data *data);

/*	ft_exit.c		*/
void	ft_exit(t_data *data, int process);

/*	ft_export.c		*/
void	ft_export(t_cmd *cmd, t_data *data, int process);

#endif
