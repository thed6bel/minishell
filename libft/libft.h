/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowathar <lowathar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:57:52 by lwathar           #+#    #+#             */
/*   Updated: 2023/03/28 13:05:33 by lowathar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>
# include <stdio.h> 
# include <limits.h>
# include <fcntl.h>
# define BUFFER_SIZE	1

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_atoi(const char *str);
void				ft_bzero(void *str, size_t n);
void				*ft_calloc(size_t count, size_t size);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
char				*ft_itoa(int n);
char				*ft_itoa_base(unsigned long long n, char *base, int b_size);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *str, int c, size_t n);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				**ft_split(char const *str, char c);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s1);
char				*ft_strjoin(const char *s1, const char *s2);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlen(const char *s);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strncmp(const char *s1,
						const char *s2, size_t n);
char				*ft_strnstr(const char *str,
						const char *to_find, size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_tolower(int c);
int					ft_toupper(int c);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstadd_front(t_list **alst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void*));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);

// ft_printf

typedef struct s_struct
{
	int		count_print;
	char	convert;
}		t_struct;

int					ft_printf(const char *format, ...);
int					ft_print(const char *format, va_list *ap, t_struct *tab);
int					ft_get_convert(t_struct *tab, const char *str, int i);
int					ft_print_with_convert(t_struct *tab, va_list *ap);
void				ft_putchar(char c, t_struct *tab);

void				ft_print_c(t_struct *tab, va_list *ap);

int					ft_print_s(t_struct *tab, va_list *ap);

int					ft_print_p(t_struct *tab, va_list *ap);

int					ft_print_i(t_struct *tab, va_list *ap);

int					ft_print_u(t_struct *tab, va_list *ap);

int					ft_print_x(t_struct *tab, va_list *ap);

// ft_get_next_line

char				*get_next_line(int fd);
char				*ft_read_file(int fd, char *lstr);
char				*ft_getline(char *lstr);
char				*ft_next(char *lstr);
char				*ft_next2(char *lstr, char *str, int i);
char				*ft_strchr_gnl(char *str);
size_t				ft_strlen_gnl(char *s);
char				*ft_strjoin_gnl(char *lstr, char *buf);
char				*ft_strjoin_gnl_2(char *lstr, char *buf, char *str);

#endif
