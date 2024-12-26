/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:32:38 by ansebast          #+#    #+#             */
/*   Updated: 2024/10/03 10:27:07 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

void				ft_bzero(void *s, size_t size);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *ptr, int value, size_t size);
void				*ft_calloc(size_t num, size_t size);
void				*ft_memchr(const void *ptr, int value, size_t num);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
int					ft_memcmp(const void *ptr1, const void *ptr2, size_t num);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_isascii(int c);
int					ft_atoi(const char *str);
int					ft_atoi_base(const char *str, int str_base);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_itoa(int n);
char				*get_next_line(int fd);
char				**ft_split(char const *str, char c);
char				*ft_strtrim(const char *s1, const char *set);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strdup(const char *s);
char				*ft_strchr(const char *str, int c);
char				*ft_strrchr(const char *str, int c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *str);
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstadd_back(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
void				ft_puterror(char *str, int ext);
char				*ft_strtok(char *str, const char *delimiter);
int					ft_isvalid_digit(int ch, int baselen);
int					ft_isspace(int c);
long				ft_strtol(char *str, char **endptr, int base);
int					hex_to_int(char *hex_str);
void				ft_freearray(char **array, int pos);
int					ft_abs(int n);
void				ft_convert_digits(char *str, int i, long *res,
						int str_base);
#endif
