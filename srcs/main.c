/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:12:41 by vroussea          #+#    #+#             */
/*   Updated: 2016/12/02 19:13:32 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/openclproject.h"

static int	print_result(cl_kernel kernel, cl_command_queue queue, cl_mem *tab)
{
	int		c;
	cl_int	errcode;

	errcode = clEnqueueTask(queue, kernel, 0, NULL,NULL);
	if (errcode != CL_SUCCESS)
	{
		ft_putnbr(errcode);
		ft_putendl("");
		ft_putendl("Error while enqueing task");
		return (1);
	}
	if (clEnqueueReadBuffer(queue, tab[2], CL_TRUE, 0, sizeof(int), &c, 0, NULL, NULL) != CL_SUCCESS)
	{
		ft_putendl("Error while reading buffer");
		return (1);
	}
	ft_putstr("c = ");
	ft_putnbr(c);
	ft_putendl("");
	return (0);
}

static int	caller(cl_context ctxt, cl_device_id dvic, cl_kernel kernel)
{
	cl_command_queue	queue;
	cl_mem				*tab;

	if (!(queue = init_queue(ctxt, dvic)) ||
		!(tab = tab_buffer(ctxt, 3)) ||
		write_tab(tab, 3, queue) ||
		set_args(tab, 3, kernel) ||
		print_result(kernel, queue, tab))
		return (1);
	return (0);
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
		caller(ctxt, dvic, kernel))
	{
		ft_putendl("Program abort");
		return (1);
	}
	ft_putendl("finis");
	return (0);
}
