/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:51:04 by omoreno-          #+#    #+#             */
/*   Updated: 2023/08/02 14:51:06 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define FAIL_MEM_ALLOC_READ_RET	-1000
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	1024
# endif

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

size_t	ft_strlen_x(const char *s);
size_t	ft_strncpy_x(char *dst, const char *src, size_t n);
char	*ft_strjoin_x(char const *s1, char const *s2, \
			size_t *s1_len, size_t s2_len);
char	*ft_substr_empty2null(char const *s, unsigned int start,	size_t len,
			int empty2null);
void	free_x(void **p);
char	*ft_strnl(const char *s);
char	*get_next_line(int fd);

#endif