/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_sphere_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:10:10 by omoreno-          #+#    #+#             */
/*   Updated: 2023/08/30 13:49:58 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../common.h"
#include <math.h>

static int	ft_coef_calc(double coefs[3], t_line line, const t_sphere *sphere)
{
	t_vector		rel_origin;
	const double	radius = sphere->diameter / 2.0;

	ft_substraction(rel_origin, line.point, (double *)sphere->point);
	coefs[0] = 1.0;
	coefs[1] = ft_dot_product(line.orientation, rel_origin);
	coefs[2] = ft_dot_product(rel_origin, rel_origin) - radius * radius;
	return (1);
}

void	spherical_map(double *uv, t_vector point)
{
	float	theta;
	float	phi;

	theta = atan2(point[0], point[2]);
	phi = acos(point[1]);
	uv[0] = 1 - ((theta / (M_PI * 2)) + 0.5);
	uv[1] = 1 - (phi / M_PI);
}

static double	module(double num)
{
	return (num - floor(num));
}

static t_rgba	material_pick_color(t_vector orientation, t_material *mat)
{
	double			uv[2];
	t_chess_ext		*chess_ext;

	if (mat->type == MTT_HOMOG)
		return (mat->color);
	chess_ext = (t_chess_ext *)mat->ext_prop;
	spherical_map(uv, orientation);
	if ((module(uv[0] * 20) < 0.5) ^ (module(uv[1] * 10) < 0.5))
		return (mat->color);
	return (chess_ext->color);
}

int	inter_sphere_line(t_intersect_data *ret, t_line line, void *figure)
{
	const t_sphere		*sphere = (t_sphere *)figure;
	double				coefs[3];

	if (!ft_coef_calc(coefs, line, sphere))
		return (0);
	ret->distance = ft_quadrat_eq(coefs, 1);
	if (ret->distance == INFINITY)
		return (0);
	if (ret->distance < 0)
		ret->distance = ft_quadrat_eq(coefs, -1);
	if (ret->distance < 0)
		return (0);
	ret->tan_plane.material = sphere->material;
	ft_addition(ret->tan_plane.point, line.point, \
		ft_scale_vector(ret->tan_plane.point, \
			line.orientation, ret->distance));
	ft_substraction(ret->tan_plane.orientation, \
		ret->tan_plane.point, (double *)sphere->point);
	ft_normalize(ret->tan_plane.orientation, ret->tan_plane.orientation);
	ret->color = material_pick_color(ret->tan_plane.orientation, \
										sphere->material);
	return (1);
}
