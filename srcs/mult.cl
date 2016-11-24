__kernel void	mult(__global const int *a, __global const int *b, __global int *c)
{
	int	id;

	id = get_global_id(0);
	c[i] = a[i] * b[i];
}
