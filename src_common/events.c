/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:44:35 by omoreno-          #+#    #+#             */
/*   Updated: 2023/08/26 15:43:22 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	ft_handle_no_event(void *data)
{
	t_minirt_data		*minirt;

	if (! data)
		return (0);
	minirt = data;
	if (minirt->exit_cmd || ! minirt->gr_ctx->wnd)
	{
		minirt_dispose(&minirt);
		exit(0);
	}
	else
		ft_draw(minirt);
	return (0);
}

int	ft_close(void *param)
{
	t_minirt_data	*minirt;

	minirt = param;
	if (! minirt)
		return (0);
	minirt->exit_cmd = 1;
	return (0);
}

int	ft_key_input(int keycode, void *param)
{
	t_minirt_data		*minirt;

	if (! param)
		return (0);
	minirt = param;
	if (! minirt)
		return (0);
	if (keycode == KC_ESC || keycode == KC_Q)
	{
		minirt->exit_cmd = 1;
		return (0);
	}
	return (0);
}
	// ft_update_pos(keycode, minirt);
	// return (ft_draw(minirt));
