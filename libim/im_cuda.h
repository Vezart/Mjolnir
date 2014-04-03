//============================================================
//  File:       im_cuda.h
//  Author:     John Gauch
//  Date:       Summer 2010
//============================================================

void query_cuda();

float *binomial_cuda(float *data, int count, int xdim, int ydim);
short *binomial_cuda(short *data, int count, int xdim, int ydim);

float *gradient_cuda(float *data, int xdim, int ydim);
short *gradient_cuda(short *data, int xdim, int ydim);
