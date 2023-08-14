/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rays_v2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:10:10 by omoreno-          #+#    #+#             */
/*   Updated: 2023/08/14 15:21:02 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../../common.h"

static void	origin_configure(t_camera *cam, t_vector origin, int size[2])
{
	t_vector		trash;

	(void)size;
	ft_addition(origin, cam->point, ft_scale_vector(trash, \
		cam->orientation, cam->focal_dis));
	ft_substraction(origin, origin, ft_scale_vector(trash, \
		cam->horizontal, (size[W] - 1.0) / 2.0));
	ft_substraction(origin, origin, ft_scale_vector(trash, \
		cam->vertical, (size[H] - 1.0) / 2.0));
}

static void	camera_configure(t_camera *cam, int width)
{
	t_vector	z_axis;

	z_axis[0] = 0;
	z_axis[1] = 0;
	z_axis[2] = 1;
	cam->focal_dis = ((width - 1.0) / 2.0) / tan(cam->fov / 2);
	ft_cross_product(cam->horizontal, cam->orientation, z_axis);
	ft_normalize(cam->horizontal, cam->horizontal);
	ft_cross_product(cam->vertical, cam->orientation, cam->horizontal);
	ft_normalize(cam->vertical, cam->vertical);
	// ft_cross_product(cam->orientation, cam->vertical, cam->horizontal);
	// ft_normalize(cam->orientation, cam->orientation);
}

void	camera_rays_v2(t_minirt_data *minirt, t_camera *cam, \
						t_img *img, int size[2])
{
	t_vector		origin;
	t_vector		pixel;
	t_vector		trash;
	t_line			ray;
	int				iter[2];

	camera_configure(cam, size[W]);
	origin_configure(cam, origin, size);
	ft_copy_vector(ray.point, cam->point);
	iter[H] = -1;
	while (++iter[H] < size[H])
	{
		iter[W] = -1;
		while (++iter[W] < size[W])
		{
			ft_copy_vector(pixel, origin);
			ft_addition(pixel, pixel, ft_scale_vector(trash, \
				cam->horizontal, iter[W]));
			ft_addition(pixel, pixel, ft_scale_vector(trash, \
				cam->vertical, iter[H]));
			ft_substraction(ray.orientation, pixel, ray.point);
			ft_normalize(ray.orientation, ray.orientation);
			ft_pixel_put(img, iter[W], iter[H], raytrace(minirt, ray));
		}
	}
}
