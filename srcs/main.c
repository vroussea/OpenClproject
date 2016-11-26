/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:12:41 by vroussea          #+#    #+#             */
/*   Updated: 2016/11/26 17:52:47 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/OpenClproject.h"

static void	print_result(cl_kernel kernel, cl_command_queue queue, cl_mem memobj)
{
	char	*string;

	string = (char *)ft_memalloc(128);
	if (clEnqueueTask(queue, kernel, 0, NULL,NULL) != CL_SUCCESS)
		error_msg("Error while enqueing task");
	if (clEnqueueReadBuffer(queue, memobj, CL_TRUE, 0, 128, string, 0, NULL, NULL) != CL_SUCCESS)
		error_msg("Error while reading buffer");
	if (ft_strlen(string) > 0)
		ft_putendl(string);
	ft_strdel(&string);
}

int	main(void)
{
	cl_command_queue	command_queue;
	cl_kernel			kernel;
	cl_mem				memobj;
	cl_context			context;
	cl_program			program;
	
	if (!(kernel = get_kernel(&context, &program, &memobj)))
	{
		ft_putendl("Program abort");
		return (1);
	}
	command_queue = NULL;
	print_result(kernel, command_queue, memobj);
	return (0);
}
