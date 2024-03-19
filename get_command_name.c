#include "./include/minishell.h"

void	get_user(t_prompt prompt, char **temp)
{
	char	**user;
	char	*temp2;

	user = NULL;
	temp2 = NULL;
	get_execve(&user, "/usr/bin/whoami", "whoami", prompt.envp);
	if (!user)
		user = ft_extend_matrix(user, "guest");
	if (!ft_strncmp(user[0], "root", 4))
		temp2 = ft_strjoin(NULL, RED);
	else if (user[0])
		temp2 = ft_strjoin(NULL, GREEN);
	*temp = ft_strjoin(temp2, *user);
	free(temp2);
	ft_free_matrix(&user);
}

char *get_command_name(t_command_info command)
{
    char *temp;
    char *user;
    char *home;

    get_user(command, &temp);
	user = ft_strjoin(temp, "@minishell");
	free(user);

}