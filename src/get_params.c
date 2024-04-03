#include "../include/minishell.h"

extern int	signal_status;

t_mini	*get_outfile1(t_mini *node, **args, int *i)
{
    char *error_msg;
    int redirector[2];

    redirector[0] = 1;
    redirector[1] = 0;
    error_msg = "minishell: syntax error near unexpected token `newline'";
    (*i)++;
	if (args[*i])
		node->outfile = get_fd(node->outfile, args[*i], redirector);
	if (!args[*i] || node->outfile == -1)
	{
		*i = -1;
		if (node->outfile != -1)
		{
			ft_putendl_fd(error_msg, 2);
			signal_status = 2;
		}
		else
			signal_status = 1;
	}
	return (node);  
}


t_mini	*get_outfile2(t_mini *node, **args, int *i)
{
    char *error_msg;
    int redirector[2];

    redirector[0] = 1;
    redirector[1] = 1;
    error_msg = "minishell: syntax error near unexpected token `newline'";
    (*i)++;
	if (args[++(*i)])
		node->outfile = get_fd(node->outfile, args[*i], redirector);
	if (!args[*i] || node->outfile == -1)
	{
		*i = -1;
		if (node->outfile != -1)
		{
			ft_putendl_fd(error_msg, 2);
			signal_status = 2;
		}
		else
			signal_status = 1;
	}
	return (node);  
}

t_mini	*get_infile1(t_mini *node, char **args, int *i)
{
	char	*error_msg;
	int		redirector[2];

	redirector[0] = 0;
	redirector[1] = 0;
	error_msg = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[*i])
		node->infile = get_fd(node->infile, args[*i], redirector);
	if (!args[*i] || node->infile == -1)
	{
		*i = -1;
		if (node->infile != -1)
		{
			ft_putendl_fd(error_msg, 2);
			signal_status = 2;
		}
		else
			signal_status = 1;
	}
	return (node);
}

t_mini	*get_infile2(t_mini *node, char **args, int *i)
{
	char	*aux;
	char	*nl;
	char	*str[2];

	str[0] = NULL;
	str[1] = NULL;

	aux = NULL;
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[++(*i)])
	{
		aux = args[*i];
		node->infile = virtual_doc(str, aux);
	}
	if (!args[*i] || node->infile == -1)
	{
		*i = -1;
		if (node->infile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_status = 2;
		}
	}
	return (node);
}