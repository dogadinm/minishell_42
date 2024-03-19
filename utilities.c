#include "./include/minishell.h"

char	**ft_extend_matrix(char **in, char *newstr)
{
	char	**out;
	int		len;
	int		i;

	i = -1;
	out = NULL;
	if (!newstr)
		return (in);
	len = ft_matrixlen(in);
	out = malloc(sizeof(char *) * (len + 2));
	out[len + 1] = NULL;
	if (!out)
		return (in);
	while (++i < len)
	{
		out[i] = ft_strdup(in[i]);
		if (!out[i])
		{
			ft_free_matrix(&in);
			ft_free_matrix(&out);
		}
	}
	out[i] = ft_strdup(newstr);
	ft_free_matrix(&in);
	return (out);
}


int	ft_strchr_i(const char *s, int c)
{
	unsigned char	c_unsigned;
	int				i;

	i = 0;
	if (!s)
		return (-1);
	c_unsigned = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == c_unsigned)
			return (i);
		i++;
	}
	if (c_unsigned == '\0')
		return (i);
	return (-1);
}

void ft_free_matrix(char **matrix)
{
    int i;

    i = 0;
	while (matrix && matrix[0] && matrix[0][i])
	{
		free(m[0][i]);
		i++;
	}
	if (m)
	{
		free(m[0]);
		*matrix = NULL;
	}
}


int ft_matrix_row_len(char **matrix)
{
    int i;

    i = 0;
    while (matrix && matrix[i])
        i++;
    return(i);
    
}

char **ft_matrix_dup(char **matrix)
{
    char **out;
    int n_rows;
    int i;

    i = 0;
    n_rows = ft_matrix_row_len(matrix);
    out = malloc(sizeof(char *) * (n_rows + 1));
    if (out == NULL)
        return(NULL);
    while (matrix[i])
    {
        out[i] = ft_strdup(matrix[i]);
        if (out[i] == NULL)
        {
            ft_free_matrix(&out);
            return (NULL);
        }
        i++;
    }
    out[i] = NULL;
    return (out);
}