/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:36:03 by ansebast          #+#    #+#             */
/*   Updated: 2025/03/08 10:26:08 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>

# define PIPE 0
# define DOTE 1

void    ft_free_tab(char **tab)
{
        int     i;
        
        i = -1;
        while (tab[++i])
                free(tab[i]);
        free(tab);
}

int     ft_strlen(char *str)
{
        int i = 0;

        while (str[i])
                i++;
        return (i);
}

int     ft_tablen(char **tab)
{
        int     len = 0;
        
        while (tab[len])
                len++;
        return (len);
}

char    *ft_strdup(char *str)
{
        char    *new_str;
        int     i;
        
        new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
        
        i = -1;
        while (str[++i])
                new_str[i] = str[i];
        new_str[i] = '\0';
        return (new_str);
}

int     ft_count_args(char **tab, int *delimiter)
{
        int     end = 0;

        while (tab[end])
        {
                if (!strcmp(tab[end], ";"))
                {
                        *delimiter = DOTE;
                        break;
                }
                if (!strcmp(tab[end], "|"))
                {
                        *delimiter = PIPE;
                        break;
                }
                end++;
        }
        return (end);
}

char    **ft_subtab(char **tab, int start, int end)
{
        char    **subtab;
        int     i = 0;
        
        subtab = malloc(sizeof(char *) * (end - start + 2));
        while (start <= end)    
        {
                subtab[i] = ft_strdup(tab[start]);
                i++;
                start++;
        }
        subtab[i] = NULL;
        return (subtab);
}

void    ft_putstr_fd(int fd, char *str)
{
        write(fd, str, ft_strlen(str));
}

void    ft_puterror(char *message, char *var)
{
        ft_putstr_fd(2, message);
        if (var)
                ft_putstr_fd(2, var);
        write(2, "\n", 1);
}

int     ft_cd(char **args)
{
        char    *path;
        
        if (ft_tablen(args) != 2)
        {
                ft_puterror("error: cd: bad arguments", NULL);
                return (2);
        }
        path = args[1];
        if (chdir(path))
        {
                ft_puterror("error: cd: cannot change directory to ", path);
                return (2);
        }
        return (0);
}

int     main(int ac, char **av, char **env)
{
        int     i, end, delimiter, prev_fd, backup_fd, pipes[2];
        int     pid, status;
        char    **cmd;
        (void)env;
        if (ac < 2)
        {
                ft_putstr_fd(2, "Usage: ./microshell <args>");
                return (1);
        }
        i = 1;
        backup_fd = dup(STDIN_FILENO);
        prev_fd = backup_fd;
        while (i < ac)
        {
                delimiter = -1;
                end = ft_count_args(av + i, &delimiter);
                if (end == 0)
                {
                        i++;
                        continue;
                }
                cmd = ft_subtab(av + i, 0, end - 1);
                if (!strcmp(cmd[0], "cd"))
                {
                        ft_cd(cmd);
                }
                else
                {
                        if (delimiter == PIPE)
                        {
                                if (pipe(pipes))
                                {
                                        ft_puterror("error: fatal", NULL);
                                        exit(1);
                                }
                                pid = fork();
                                if (pid == 0)
                                {
                                        dup2(prev_fd, STDIN_FILENO);
                                        dup2(pipes[1], STDOUT_FILENO);
                                        close(pipes[0]);
                                        close(pipes[1]);
                                        if (execve(cmd[0], cmd, env) == -1)
                                        {
                                                ft_puterror("error: cannot execute ", cmd[0]);
                                        }
                                }
                                close(pipes[1]);
                                if (prev_fd != backup_fd)
                                        close(prev_fd);
                                prev_fd = pipes[0];
                                waitpid(pid, &status, 0);
                        }
                        else
                        {
                                pid = fork();
                                if (pid == 0)
                                {
                                        dup2(prev_fd, STDIN_FILENO);
                                        if (execve(cmd[0], cmd, env) == -1)
                                        {
                                                ft_puterror("error: cannot execute ", cmd[0]);
                                        }
                                }
                                if (prev_fd != backup_fd)
                                        close(prev_fd);
                                prev_fd = backup_fd;
                                waitpid(pid, &status, 0);
                        }
                }
                i += end + 1;
                ft_free_tab(cmd);
        }
        dup2(backup_fd, STDIN_FILENO);
        close(backup_fd);
        return (0);
}