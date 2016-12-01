/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenCl_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 16:49:32 by vroussea          #+#    #+#             */
/*   Updated: 2016/12/01 17:55:41 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/OpenClproject.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

char				*load_source_code()
{
	char	*source;
	char	*path;
	int		fd;

	path = ft_strdup("./srcs/mult.cl");
	if ((fd = open(path, O_RDONLY)) == -1)
		return (error_msg("Error with file"));
	if (!(source = (char *)ft_memalloc(SOURCE_SIZE)))
		return (error_msg("Error while allocting memory to source string"));
	if ((read(fd, source, SOURCE_SIZE)) == -1)
		return (error_msg("Error while reading .cl source code"));
	ft_strdel(&path);
	ft_putstr(source);
	close(fd);
	return (source);
}

cl_context			get_context(cl_device_id *dvic)
{
	cl_platform_id	platform;
	cl_context		context;
	cl_int			err_code;

	platform = NULL;
	context = NULL;
	if ((clGetPlatformIDs(1, &platform, NULL)) != CL_SUCCESS)
		return (error_msg("Error while retrieving platform informations"));
	if (clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, dvic, NULL)
			!= CL_SUCCESS)
		return (error_msg("Error while retrieving device informations"));
	context = clCreateContext(NULL, 1, &(*dvic), NULL, NULL, &err_code);
	if (err_code != CL_SUCCESS)
		return (error_msg("Error while creating context"));
	return (context);
}

cl_program			build_program(char *src, cl_context ctxt, cl_device_id dvic)
{
	cl_program		prog;
	cl_int			err_code;
	size_t			size;
	char			*log;

	prog = NULL;
	prog = clCreateProgramWithSource(ctxt, 1, (const char **)&src,
			NULL, &err_code);
	if (err_code != CL_SUCCESS)
		return (error_msg("Error while creating program with source"));
	err_code = clBuildProgram(prog, 1, &dvic, NULL, NULL, NULL);
	if (err_code != CL_SUCCESS)
	{
		clGetProgramBuildInfo(prog, dvic, CL_PROGRAM_BUILD_LOG, 0, NULL, &size);
		log = (char*)ft_strnew(size);
		clGetProgramBuildInfo(prog, dvic, 
				CL_PROGRAM_BUILD_LOG, size + 1, log, NULL);
		return (error_msg(log));
		ft_strdel(&log);
	}
	ft_strdel(&src);
	return (prog);
}

cl_kernel			init_kernel(cl_program prog)
{
	cl_kernel	kernel;
	cl_int		errcode;

	kernel = NULL;
	kernel = clCreateKernel(prog, "mult", &errcode);
	if (errcode != CL_SUCCESS)
		return (error_msg("Error while creating Kernel"));
	return (kernel);
}

cl_command_queue	init_queue(cl_context ctxt, cl_device_id dvic)
{
	cl_command_queue	queue;
	cl_int				errcode;

	queue = NULL;
	queue = clCreateCommandQueue(ctxt, dvic, 0, &errcode);
	if	(errcode != CL_SUCCESS)
		return (error_msg("Error while creating command queue"));
	return (queue);
}
