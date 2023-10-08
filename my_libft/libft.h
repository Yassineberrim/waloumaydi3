/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:43:14 by slazar            #+#    #+#             */
/*   Updated: 2023/09/22 15:53:13 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_lst{
	void			*content;
	struct s_lst	*next;
}	t_lst;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strrchr(const char *s, int c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_bzero(void *s, size_t n);
int		ft_strlen(const char *s);
int		ft_atoi(const char *str);
void	*ft_memchr(const void *str, int c, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
int		ft_tolower(int c);
int		ft_toupper(int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	**ft_split(char const *s, char c);
t_lst	*ft_lstnew(void *content);
void	ft_lstadd_front(t_lst **lst, t_lst *new);
int		ft_lstsize(t_lst *lst);
t_lst	*ft_lstlast(t_lst *lst);
void	ft_lstadd_back(t_lst **lst, t_lst *new);
void	ft_lstdelone(t_lst *lst, void (*del)(void *));
void	ft_lstclear(t_lst **lst, void (*del)(void	*));
void	ft_lstiter(t_lst *lst, void (*f)(void *));
t_lst	*ft_lstmap(t_lst *lst, void *(*f)(void *), void (*del)(void *));

#endif