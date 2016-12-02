/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 17:28:32 by vroussea          #+#    #+#             */
/*   Updated: 2016/12/02 19:04:24 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/openclproject.h"

static int		write_buffer(cl_command_queue queue,
		cl_mem buffer, void *ptr, size_t size)
{
	cl_int	errcode;

	errcode = clEnqueueWriteBuffer(queue, buffer, CL_TRUE, 0,
			size, ptr, 0, NULL, NULL);
	if (errcode != CL_SUCCESS)
		return (1);
	return (0);
}

int				write_tab(cl_mem *tab, int nb, cl_command_queue queue)
{
	int	*abc;
	int	i;

	abc = (int *)ft_memalloc(sizeof(int) * nb);
	abc[0] = 5;
	abc[1] = 3;
	abc[2] = 1;
	i = 0;
	while (i < nb)
	{
		if (write_buffer(queue, tab[i], (void *)&(abc[i]), sizeof(int)))
		{
			ft_putendl("Error while writting in a buffer");
			return (1);
		}
		i++;
	}
	ft_memdel((void **)&abc);
	return (0);
}

static cl_mem	create_buffer(cl_context context, size_t size)
{
	cl_mem	buffer;
	cl_int	errcode;

	buffer = NULL;
	buffer = clCreateBuffer(context, CL_MEM_READ_WRITE, size, NULL, &errcode);
	if (errcode != CL_SUCCESS)
		return (error_msg("Error while creating Buffer"));
	return (buffer);
}

cl_mem			*tab_buffer(cl_context context, size_t nb)
{
	cl_mem	*tab;
	size_t	i;

	i = 0;
	if (!(tab = (cl_mem *)ft_memalloc(sizeof(cl_mem) * nb)))
		return (error_msg("Error while allocationg memory for buffers"));
	while (i < nb)
	{
		if (!(tab[i] = create_buffer(context, sizeof(int))))
			return (error_msg("Can't finish to build all buffers, abort"));
		i++;
	}
	return (tab);
}

int				set_args(cl_mem *tab, int nb, cl_kernel kernel)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		if (clSetKernelArg(kernel, i, sizeof(cl_mem),
					(void *)&tab[i]) != CL_SUCCESS)
		{
			ft_putendl("Error while setting a kernel argument");
			return (1);
		}
		i++;
	}
	return (0);
}
