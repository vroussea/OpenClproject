/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenCl_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 16:49:32 by vroussea          #+#    #+#             */
/*   Updated: 2016/11/26 17:45:04 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/OpenClproject.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static char			*load_source_code()
{
	char	*source;
	char	*path;
	int		fd;

	path = ft_strdup("./srcs/mult.cl");
	fd = open(path, O_RDONLY);
	if (!(source = (char *)ft_memalloc(SOURCE_SIZE)))
		return (error_msg("Error while allocting memory to source string"));
	if ((read(fd, source, SOURCE_SIZE)) == -1)
		return (error_msg("Error while reading .cl source code"));
	ft_strdel(&path);
	close(fd);
	return (source);
}

static cl_context	get_context(cl_device_id *device)
{
	cl_platform_id	platform;
	cl_context		context;
	cl_int			err_code;

	if ((clGetPlatformIDs(1, &platform, NULL)) != CL_SUCCESS)
		return (error_msg("Error while retrieving platform informations"));
	if (clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &(*device), NULL)
			!= CL_SUCCESS)
		return (error_msg("Error while retrieving device informations"));
	context = clCreateContext(NULL, 1, &(*device), NULL, NULL, &err_code);
	if (err_code != CL_SUCCESS)
		return (error_msg("Error while creating context"));
	return (context);
}

static cl_program	build_program(const char *source, cl_context context, cl_device_id device)
{
	cl_program	program;
	cl_int		err_code;

	program = clCreateProgramWithSource(context, 1, &source, NULL, &err_code);
	if (err_code != CL_SUCCESS)
		return (error_msg("Error while creating program with source"));
	if (clBuildProgram(program, 1, &device, NULL, NULL, NULL) != CL_SUCCESS)
		return (error_msg("Error while building program"));
	return (program);
}

static cl_kernel	init_kernel(cl_program prog, cl_mem *memobj, cl_context context)
{
	cl_kernel	kernel;
	cl_int		errcode;

	*memobj = clCreateBuffer(context, CL_MEM_READ_WRITE, 128, NULL, &errcode);
	if (errcode != CL_SUCCESS)
		return (error_msg("Error while creating Buffer"));
	kernel = clCreateKernel(prog, "hello", &errcode);
	if (errcode != CL_SUCCESS)
		return (error_msg("Error while creating Kernel"));
	if (clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)memobj) != CL_SUCCESS)
		return (error_msg("Error while setting kernel variable"));
	return (kernel);
}

cl_kernel			get_kernel(cl_context *context, cl_program *prog, cl_mem *memobj)
{
	char			*source;
	cl_kernel		kernel;
	cl_device_id	device;

	device = NULL;
	kernel = NULL;
	if (!(source = load_source_code()) ||
	!(*context = get_context(&device)) ||
	!(*prog = build_program(source, *context, device)) ||
	!(kernel = init_kernel(*prog, memobj, *context)))
		return (NULL);
	ft_strdel(&source);
	return (kernel);
}
