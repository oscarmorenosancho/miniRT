/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cone_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:37:00 by omoreno-          #+#    #+#             */
/*   Updated: 2023/09/09 11:35:43 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../common.h"
#include <math.h>
#include <stdio.h>

static int	ft_coef_calc(double coef[3], t_line line, const t_cone *cone)
{
	t_vector	w;
	double		v_dot_h;
	double		v_dot_w;
	double		w_dot_h;

	v_dot_h = ft_dot_product(line.orientation, (double *)cone->orientation);
	ft_substraction(w, line.point, (double *)cone->point);
	v_dot_w = ft_dot_product(line.orientation, w);
	w_dot_h = ft_dot_product(w, (double *)cone->orientation);
	coef[0] = v_dot_h * v_dot_h;
	coef[0] -= cone->cos_theta_sq;
	coef[1] = v_dot_h * w_dot_h;
	coef[1] -= v_dot_w * cone->cos_theta_sq;
	coef[2] = w_dot_h * w_dot_h;
	coef[2] -= ft_dot_product(w, w) * cone->cos_theta_sq;
	if ((coef[0]) < 1.0e-5)
		return (0);
	return (1);
}

static int	ft_cap_inters(t_intersect_data *ret, \
	t_line line, const t_cone *cone)
{
	double		sign;
	double		axe_dist;
	double		height;
	double		cap_radius;
	int			cap_id;

	ret->color = cone->material->color;
	ft_copy_vector(ret->tan_plane.orientation, (double *)cone->orientation);
	sign = ft_dot_product(line.orientation, (double *)cone->orientation);
	if (sign == 0.0)
		return (0);
	sign /= -fabs(sign);
	cap_id = (sign > 0.0);
	height = cone->heights[cap_id];
	cap_radius = height * cone->tan_theta;
	ret->tan_plane = cone->caps[cap_id];
	if (inter_plane_line(ret, line, (void *)&ret->tan_plane) == 0)
		return (0);
	ret->color = chess_cone_pick_color(ret->tan_plane.point, cone);
	axe_dist = ft_distance_sq((double *)cone->caps[cap_id].point, \
					ret->tan_plane.point);
	return (axe_dist <= (cap_radius * cap_radius));
}

static int	ft_give_inters(t_intersect_data *ret, \
	t_vector line_int, const t_cone *cone)
{
	t_vector	trash;

	ret->color = (t_rgba){0, 0, 0, 0};
	ft_copy_vector(ret->tan_plane.point, line_int);
	ft_cross_product(ret->tan_plane.orientation, \
		(double *)cone->orientation, ft_substraction(trash, \
			line_int, (double *)cone->point));
	ft_cross_product(ret->tan_plane.orientation, \
		ret->tan_plane.orientation, trash);
	ft_normalize(ret->tan_plane.orientation, ret->tan_plane.orientation);
	ret->color = chess_cone_pick_color(ret->tan_plane.point, cone);
	return (1);
}

int	inter_cone_line(t_intersect_data *ret, t_line line, void *figure)
{
	const t_cone	*cone = (t_cone *)figure;
	double			int_height;
	t_vector		line_int;
	double			coefs[3];
	double			roots[2];

	ret->tan_plane.material = cone->material;
	if (ft_cap_inters(ret, line, figure))
		return (1);
	ft_coef_calc(coefs, line, cone);
	ft_quadrat_eq2(coefs, roots);
	if (!ft_take_max_pos_root(&ret->distance, roots))
		return (0);
	ft_addition(line_int, line.point, \
		ft_scale_vector(line_int, line.orientation, ret->distance));
	int_height = ft_dot_product((double *)cone->orientation, \
		ft_substraction(ret->tan_plane.point, line_int, (double *)cone->point));
	if (int_height >= cone->heights[0] && int_height <= cone->heights[1])
		return (ft_give_inters(ret, line_int, cone));
	return (0);
}
