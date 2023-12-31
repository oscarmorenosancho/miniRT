/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cyl_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:10:10 by omoreno-          #+#    #+#             */
/*   Updated: 2023/09/06 14:42:40 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../common.h"
#include <math.h>
#include <stdio.h>

static int	ft_coef_calc(double coef[3], t_line line, const t_cylinder *cyl)
{
	t_vector			w;
	double				v_dot_h;
	double				v_dot_w;
	double				w_dot_h;

	v_dot_h = ft_dot_product(line.orientation, (double *)cyl->orientation);
	ft_substraction(w, line.point, (double *)cyl->point);
	v_dot_w = ft_dot_product(line.orientation, w);
	w_dot_h = ft_dot_product(w, (double *)cyl->orientation);
	coef[0] = 1.0 - v_dot_h * v_dot_h;
	coef[1] = (v_dot_w - v_dot_h * w_dot_h);
	coef[2] = ft_dot_product(w, w) - w_dot_h * w_dot_h - cyl->radius_sq;
	if (fabs(v_dot_h) > 0.9)
		return (0);
	return (1);
}

static int	ft_cap_inters(t_intersect_data *ret, \
	t_line line, const t_cylinder *cyl)
{
	double		sign;
	double		axe_dist;
	int			cap_id;

	ret->color = (t_rgba){0, 0, 0, 0};
	ft_copy_vector(ret->tan_plane.orientation, (double *)cyl->orientation);
	sign = -ft_dot_product(line.orientation, (double *)cyl->orientation);
	if (sign == 0.0)
		return (0);
	sign /= fabs(sign);
	cap_id = (sign > 0.0);
	ret->tan_plane = cyl->caps[cap_id];
	if (inter_plane_line(ret, line, (void *)&ret->tan_plane) == 0)
		return (0);
	ret->color = chess_cylin_pick_color(ret->tan_plane.point, cyl);
	axe_dist = ft_distance_sq((double *)cyl->caps[cap_id].point, \
					ret->tan_plane.point);
	return (axe_dist <= cyl->radius_sq);
}

static int	ft_give_inters(t_intersect_data *ret, \
	t_vector line_int, const t_cylinder *cyl, double int_height)
{
	t_vector	center;

	ret->tan_plane.material = cyl->material;
	ft_addition(center, (double *) cyl->point, \
		ft_scale_vector(center, (double *) cyl->orientation, int_height));
	ft_copy_vector(ret->tan_plane.point, line_int);
	ft_substraction(ret->tan_plane.orientation, line_int, center);
	ft_normalize(ret->tan_plane.orientation, ret->tan_plane.orientation);
	ret->color = chess_cylin_pick_color(ret->tan_plane.point, cyl);
	return (1);
}

int	inter_cyl_line(t_intersect_data *ret, t_line line, void *figure)
{
	const t_cylinder	*cyl = (t_cylinder *)figure;
	double				coefs[3];
	double				roots[2];
	double				int_height;
	t_vector			line_int;

	ret->tan_plane.material = cyl->material;
	if (ft_cap_inters(ret, line, figure))
		return (1);
	ft_coef_calc(coefs, line, cyl);
	ft_quadrat_eq2(coefs, roots);
	if (!ft_take_min_pos_root(&ret->distance, roots))
		return (0);
	ft_addition(line_int, line.point, \
		ft_scale_vector(line_int, line.orientation, ret->distance));
	int_height = ft_dot_product((double *)cyl->orientation, \
		ft_substraction(ret->tan_plane.point, line_int, (double *)cyl->point));
	if (fabs(int_height) <= cyl->half_height)
		return (ft_give_inters(ret, line_int, cyl, int_height));
	return (0);
}
