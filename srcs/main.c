/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:12:41 by vroussea          #+#    #+#             */
/*   Updated: 2016/12/01 18:28:40 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/OpenClproject.h"
#include <stdio.h>

/*static void	print_result(cl_kernel kernel, cl_mem *tab, cl_context context, cl_device_id device_id)
{
	float				a;
	float				b;
	float				*c;
	cl_int				errcode;
	cl_command_queue	queue;

	c = (float *)ft_memalloc(sizeof(float));
	if (errcode != CL_SUCCESS)
		error_msg("Error while creating queue");
	a = 5;
	b = 3;
	errcode = clEnqueueWriteBuffer(queue, tab[0], CL_TRUE, 0, sizeof(float), &a, 0, NULL, NULL);
	errcode = clEnqueueWriteBuffer(queue, tab[1], CL_TRUE, 0, sizeof(float), &b, 0, NULL, NULL);
	errcode = clEnqueueTask(queue, kernel, 0, NULL,NULL);
	if (errcode != CL_SUCCESS)
		error_msg("Error while enqueing task");
	if (clEnqueueReadBuffer(queue, tab[3], CL_TRUE, 0, sizeof(float), &c, 0, NULL, NULL) != CL_SUCCESS)
		error_msg("Error while reading buffer");
	printf("c = %f\n", *c);
}*/

static int	caller(cl_context ctxt, cl_program prog, cl_device_id dvic, cl_kernel kernel)
{
	cl_command_queue	queue;
	cl_mem				*tab;

	if (!(queue = init_queue(ctxt, dvic)) ||
		!(tab = tab_buffer(ctxt, 3)))
		return (1);
	prog = NULL;
	kernel = NULL;
	return (0);
//	kernel = print_result(kernel, tab, context, device);
}

int			main(void)
{
	cl_context		ctxt;
	cl_device_id	dvic;
	cl_program		prog;
	cl_kernel		kernel;
	char			*src;

	if (!(src = load_source_code()) ||
		!(ctxt = get_context(&dvic)) ||
		!(prog = build_program(src, ctxt, dvic)) ||
		!(kernel = init_kernel(prog)) ||
		(caller(ctxt, prog, dvic, kernel)))
	{
		ft_putendl("Program abort");
		return (1);
	}
	ft_putendl("finis");
	return (0);
}
