#include "../include/minishell.h"

int g_signal_status;

void	signal_new_line(int sign)
{
	if (sign == SIGINT)
	{
		g_signal_status = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}