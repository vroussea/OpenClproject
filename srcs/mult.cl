__kernel void mult(__global int* a, __global int* b, __global int* c)
{
	*c = *a + *b;
}
