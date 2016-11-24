/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenCl_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 16:49:32 by vroussea          #+#    #+#             */
/*   Updated: 2016/11/24 17:47:00 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/OpenClproject.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static char	*load_source_code()
{
	char	*source;
	char	*path;
	int		fd;

	path = ft_strdup("./srcs/mult.cl");
	fd = open(path, O_RDONLY);
	source = ft_memalloc(SOURCE_SIZE);
	if ((read(fd, source, SOURCE_SIZE)) == -1)
	{
		ft_putendl("Error while reading .cl source code");
		exit(1);
	}
	ft_strdel(&path);
	close(fd);
	return (source);
}

//get_context

cl_kernel	get_kernel()
{
	char		*source;
	cl_kernel	kernel;

	kernel = NULL;
	source = load_source_code();
	ft_putendl(source);
	ft_strdel(&source);
	return (kernel);
}
