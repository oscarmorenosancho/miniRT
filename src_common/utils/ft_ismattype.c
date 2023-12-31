/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ismattype.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:30:53 by omoreno-          #+#    #+#             */
/*   Updated: 2023/09/08 11:17:02 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../common.h"

int	ft_ismattype(char *str, t_material_type *ret)
{
	const size_t			len = ft_strlen_x(str);
	const char				*type_str_id[3] = {"HOMOG", "CHESS", "IMAGE"};
	const t_material_type	type_id[3] = {MTT_HOMOG, MTT_CHESS, MTT_IMAGE};
	int						i;

	if (len != 5)
	{
		ft_log_error(ISMATTYPE_INVALID);
		return (0);
	}
	i = 0;
	while (i < 3)
	{
		if (!ft_strncmp(str, type_str_id[i], 5))
		{
			*ret = type_id[i];
			return (1);
		}
		i++;
	}
	ft_log_error(ISMATTYPE_INVALID);
	return (0);
}
