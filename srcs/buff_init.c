/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 17:28:32 by vroussea          #+#    #+#             */
/*   Updated: 2016/12/01 18:31:34 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/OpenClproject.h"

static int		write_buffer()
{

}

int				write_tab(cl_mem *tab, )
{

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
//	if (clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&tab[1]) != CL_SUCCESS)
//		return (error_msg("Error while setting kernel b variable"));
	return (tab);
}
