__kernel void reset_depth_buffer(__global float *buf)
{
	buf[get_global_id(1) * get_global_size(0) + get_global_id(0)] = -100000;
}