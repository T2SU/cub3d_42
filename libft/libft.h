/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:11:30 by smun              #+#    #+#             */
/*   Updated: 2021/01/30 18:41:51 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define TRUE 1
# define FALSE 0
# include <unistd.h>
# include <stdarg.h>

typedef int			t_bool;

/*
** ============================================================================
**   Common Functions
** ============================================================================
*/

int					ft_min(int a, int b);
int					ft_max(int a, int b);
int					ft_abs(int n);
char				*ft_itoa(int n);

/*
** ============================================================================
**   C type Functions
** ============================================================================
*/

int					ft_isspace(int c);

/*
** ============================================================================
**   List Functions
** ============================================================================
*/

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstdelone(t_list *lst, void (*del)(void*));

/*
** ============================================================================
**   Memory Functions
** ============================================================================
*/

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_calloc(size_t count, size_t size);

/*
** ============================================================================
**   String Functions
** ============================================================================
*/

size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
char				*ft_strchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strtrim(const char *s1, const char *set);
char				**ft_split(const char *s, char c);
size_t				ft_strlens(const char *s);
char				*ft_strdup(const char *s1);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);

/*
** ============================================================================
**   GNL
** ============================================================================
*/

int					get_next_line(int fd, char **line);

#endif
