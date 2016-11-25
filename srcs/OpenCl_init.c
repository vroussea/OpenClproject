/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenCl_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 16:49:32 by vroussea          #+#    #+#             */
/*   Updated: 2016/11/25 17:44:36 by vroussea         ###   ########.fr       */
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
//	cl_device_id	device;
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
	cl_program_build_info	param_name;
	cl_build_status param_value;
	size_t	size;

	program = clCreateProgramWithSource(context, 1, &source, NULL, &err_code);
	if (err_code != CL_SUCCESS)
		return (error_msg("Error while creating program with source"));
	err_code = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
	param_value = (cl_build_status)ft_memalloc(1000);
	param_name = CL_PROGRAM_BUILD_STATUS;
	clGetProgramBuildInfo (program, device, param_name, 1000, (void *)&param_value, &size);
	if (param_value == CL_BUILD_ERROR)
		ft_putendl("mdr");
	if (err_code == CL_BUILD_PROGRAM_FAILURE)
		ft_putendl("mdr");
	//	return (error_msg("Error while building program"));
	return (program);
}

cl_kernel			get_kernel()
{
	char		*source;
	cl_kernel	kernel;
	cl_context	context;
	cl_program	program;
	cl_device_id	device;

	kernel = NULL;
	if (!(source = load_source_code()) ||
	!(context = get_context(&device)) ||
	!(program = build_program(source, context, device)))
		return (NULL);
	//cl_kernel kernel = clCreateKernel(program, "dp_mul", NULL);
	//clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&d_buffer);
	//clSetKernelArg(kernel, 1, sizeof(int), (void*)&N);
	kernel = (cl_kernel)source;
	ft_strdel(&source);
	return (kernel);
}
