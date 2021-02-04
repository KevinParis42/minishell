/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:47:36 by kparis            #+#    #+#             */
/*   Updated: 2021/01/12 23:01:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_struct
{
	char	*buf;
	char	*str;
	char	*tmp;
	int		nb_read;
	int		init;
}				t_struct;

int				ft_atoi(const char *str);
void			*ft_bzero(void *ptr, size_t size);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
void			*ft_memccpy(void *dest, const void *src, int c, size_t size);
void			*ft_memchr(const void *str, int c, size_t n);
int				ft_memcmp(const void *str1, const void *str2, size_t size);
void			*ft_memcpy(void *dest, const void *src, size_t size);
void			*ft_memmove(void *dest, const void *src, size_t size);
void			*ft_memset(void *ptr, int val, size_t size);
char			*ft_strchr(const char *str, int c);
char			*ft_strdup(const char *src);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *str);
int				ft_strncmp(const char *str1, const char *str2, size_t n);
char			*ft_strnstr(const char *s1, const char *s2, size_t size);
char			*ft_strrchr(const char *str, int c);
int				ft_tolower(int c);
int				ft_toupper(int c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_itoa(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putchar(char c);
void			ft_putstr(char *s);
void			ft_putnbr(int n);
void			ft_putendl(char *s);
int				get_next_line(int fd, char **line);
char			*ft_convert_base(long long nbr, char *base);
int				*ft_realloc_int(int *tab, int size, int nbr);
char			*ft_realloc_char(char *str, char c);
int				ft_str_tab_len(char **tab);
void			ft_free_str_tab(char **tab, int size);
char			**ft_realloc_char_tab(char **tab, char *str);
char			**ft_pop_char_tab(char **tab, char *str);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_cutend(char *str, char c);
int				is_av_spaces(char **av);
int				with_no_av_spaces(char **av, int *n_option);

#endif
