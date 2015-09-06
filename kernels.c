/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/*
 * Please fill in the following team struct
 */
team_t team = {
	"MTM416+SPP216",              /* Team name */

	"Michael Martinsky",     /* First member full name */
	"mtm416@lehigh.edu",  /* First member email address */

	"Sean Purcell",                   /* Second member full name (leave blank if none) */
	"spp216@lehigh.edu"                    /* Second member email addr (leave blank if none) */
};

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/*
 * naive_rotate - The naive baseline version of rotate
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst)
{
	int i, j;
	for (i = 0; i < dim; i++)
	  for (j = 0; j < dim; j++)
		dst[array_index(dim-1-j, i, dim)] = src[array_index(i, j, dim)];
}

/*
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *src, pixel *dst)
{
	temp_rotate32g(dim, src, dst);
}

/*char temp_rotate_descr[] = "temp_rotate: unrolled j loop into 16, removed function call";
void temp_rotate(int dim, pixel *src, pixel *dst)
{
	int i, j;
	for (i = 0; i < dim; i++){
	  for (j = 0; j < dim; j+=16){
		dst[(dim-1-j)*dim+i] = src[i*dim+j];
		dst[(dim-2-j)*dim+i] = src[i*dim+j+1];
		dst[(dim-3-j)*dim+i] = src[i*dim+j+2];
		dst[(dim-4-j)*dim+i] = src[i*dim+j+3];
		dst[(dim-5-j)*dim+i] = src[i*dim+j+4];
		dst[(dim-6-j)*dim+i] = src[i*dim+j+5];
		dst[(dim-7-j)*dim+i] = src[i*dim+j+6];
		dst[(dim-8-j)*dim+i] = src[i*dim+j+7];
		dst[(dim-9-j)*dim+i] = src[i*dim+j+8];
		dst[(dim-10-j)*dim+i] = src[i*dim+j+9];
		dst[(dim-11-j)*dim+i] = src[i*dim+j+10];
		dst[(dim-12-j)*dim+i] = src[i*dim+j+11];
		dst[(dim-13-j)*dim+i] = src[i*dim+j+12];
		dst[(dim-14-j)*dim+i] = src[i*dim+j+13];
		dst[(dim-15-j)*dim+i] = src[i*dim+j+14];
		dst[(dim-16-j)*dim+i] = src[i*dim+j+15];
	  }
	}

}*/

/*char temp_rotate32_descr[] = "temp_rotate32: unrolled j loop into 32, removed function call";
void temp_rotate32(int dim, pixel *src, pixel *dst)
{
	int i, j;
	for (i = 0; i < dim; i++){
	  for (j = 0; j < dim; j+=32){
		dst[(dim-1-j)*dim+i] = src[i*dim+j];
		dst[(dim-2-j)*dim+i] = src[i*dim+j+1];
		dst[(dim-3-j)*dim+i] = src[i*dim+j+2];
		dst[(dim-4-j)*dim+i] = src[i*dim+j+3];
		dst[(dim-5-j)*dim+i] = src[i*dim+j+4];
		dst[(dim-6-j)*dim+i] = src[i*dim+j+5];
		dst[(dim-7-j)*dim+i] = src[i*dim+j+6];
		dst[(dim-8-j)*dim+i] = src[i*dim+j+7];
		dst[(dim-9-j)*dim+i] = src[i*dim+j+8];
		dst[(dim-10-j)*dim+i] = src[i*dim+j+9];
		dst[(dim-11-j)*dim+i] = src[i*dim+j+10];
		dst[(dim-12-j)*dim+i] = src[i*dim+j+11];
		dst[(dim-13-j)*dim+i] = src[i*dim+j+12];
		dst[(dim-14-j)*dim+i] = src[i*dim+j+13];
		dst[(dim-15-j)*dim+i] = src[i*dim+j+14];
		dst[(dim-16-j)*dim+i] = src[i*dim+j+15];
		dst[(dim-17-j)*dim+i] = src[i*dim+j+16];
		dst[(dim-18-j)*dim+i] = src[i*dim+j+17];
		dst[(dim-19-j)*dim+i] = src[i*dim+j+18];
		dst[(dim-20-j)*dim+i] = src[i*dim+j+19];
		dst[(dim-21-j)*dim+i] = src[i*dim+j+20];
		dst[(dim-22-j)*dim+i] = src[i*dim+j+21];
		dst[(dim-23-j)*dim+i] = src[i*dim+j+22];
		dst[(dim-24-j)*dim+i] = src[i*dim+j+23];
		dst[(dim-25-j)*dim+i] = src[i*dim+j+24];
		dst[(dim-26-j)*dim+i] = src[i*dim+j+25];
		dst[(dim-27-j)*dim+i] = src[i*dim+j+26];
		dst[(dim-28-j)*dim+i] = src[i*dim+j+27];
		dst[(dim-29-j)*dim+i] = src[i*dim+j+28];
		dst[(dim-30-j)*dim+i] = src[i*dim+j+29];
		dst[(dim-31-j)*dim+i] = src[i*dim+j+30];
		dst[(dim-32-j)*dim+i] = src[i*dim+j+31];
	  }
	}

}*/

char temp_rotate32a_descr[] = "temp_rotate32a: unrolled j loop into 32, removed function call, idim, dimj";
void temp_rotate32a(int dim, pixel *src, pixel *dst)
{
	int i, j;
	for (i = 0; i < dim; i++){
	  int idim = dim*i;
	  for (j = 0; j < dim; j+=32){
		int idimj = idim+j;
	int dimj = dim-j;
	dst[(dimj-1)*dim+i] = src[idimj];
		dst[(dimj-2)*dim+i] = src[idimj+1];
		dst[(dimj-3)*dim+i] = src[idimj+2];
		dst[(dimj-4)*dim+i] = src[idimj+3];
		dst[(dimj-5)*dim+i] = src[idimj+4];
		dst[(dimj-6)*dim+i] = src[idimj+5];
		dst[(dimj-7)*dim+i] = src[idimj+6];
		dst[(dimj-8)*dim+i] = src[idimj+7];
		dst[(dimj-9)*dim+i] = src[idimj+8];
		dst[(dimj-10)*dim+i] = src[idimj+9];
		dst[(dimj-11)*dim+i] = src[idimj+10];
		dst[(dimj-12)*dim+i] = src[idimj+11];
		dst[(dimj-13)*dim+i] = src[idimj+12];
		dst[(dimj-14)*dim+i] = src[idimj+13];
		dst[(dimj-15)*dim+i] = src[idimj+14];
		dst[(dimj-16)*dim+i] = src[idimj+15];
		dst[(dimj-17)*dim+i] = src[idimj+16];
		dst[(dimj-18)*dim+i] = src[idimj+17];
		dst[(dimj-19)*dim+i] = src[idimj+18];
		dst[(dimj-20)*dim+i] = src[idimj+19];
		dst[(dimj-21)*dim+i] = src[idimj+20];
		dst[(dimj-22)*dim+i] = src[idimj+21];
		dst[(dimj-23)*dim+i] = src[idimj+22];
		dst[(dimj-24)*dim+i] = src[idimj+23];
		dst[(dimj-25)*dim+i] = src[idimj+24];
		dst[(dimj-26)*dim+i] = src[idimj+25];
		dst[(dimj-27)*dim+i] = src[idimj+26];
		dst[(dimj-28)*dim+i] = src[idimj+27];
		dst[(dimj-29)*dim+i] = src[idimj+28];
		dst[(dimj-30)*dim+i] = src[idimj+29];
		dst[(dimj-31)*dim+i] = src[idimj+30];
		dst[(dimj-32)*dim+i] = src[idimj+31];
	  }
	}
}

char temp_rotate32b_descr[] = "temp_rotate32b: unrolled j loop into 32, removed function call, idim, dimj, pointer";
void temp_rotate32b(int dim, pixel *src, pixel *dst)
{
	pixel *temp;
	int i, j;
	for (i = 0; i < dim; i++){
	  int idim = dim*i;
	  for (j = 0; j < dim; j+=32){
		int idimj = idim+j;
	temp = &dst[(dim-j-1)*dim+i];
	
	*temp = src[idimj];
	temp -= dim;
	*temp = src[idimj+1];
	temp -= dim;
	*temp = src[idimj+2];
	temp -= dim;
	*temp = src[idimj+3];
	temp -= dim;
	*temp = src[idimj+4];
	temp -= dim;
	*temp = src[idimj+5];
	temp -= dim;
	*temp = src[idimj+6];
	temp -= dim;
	*temp = src[idimj+7];
	temp -= dim;
	*temp = src[idimj+8];
	temp -= dim;
	*temp = src[idimj+9];
	temp -= dim;
	*temp = src[idimj+10];
	temp -= dim;
	*temp = src[idimj+11];
	temp -= dim;
	*temp = src[idimj+12];
	temp -= dim;
	*temp = src[idimj+13];
	temp -= dim;
	*temp = src[idimj+14];
	temp -= dim;
	*temp = src[idimj+15];
	temp -= dim;
	*temp = src[idimj+16];
	temp -= dim;
	*temp = src[idimj+17];
	temp -= dim;
	*temp = src[idimj+18];
	temp -= dim;
	*temp = src[idimj+19];
	temp -= dim;
	*temp = src[idimj+20];
	temp -= dim;
	*temp = src[idimj+21];
	temp -= dim;
	*temp = src[idimj+22];
	temp -= dim;
	*temp = src[idimj+23];
	temp -= dim;
	*temp = src[idimj+24];
	temp -= dim;
	*temp = src[idimj+25];
	temp -= dim;
	*temp = src[idimj+26];
	temp -= dim;
	*temp = src[idimj+27];
	temp -= dim;
	*temp = src[idimj+28];
	temp -= dim;
	*temp = src[idimj+29];
	temp -= dim;
	*temp = src[idimj+30];
	temp -= dim;
	*temp = src[idimj+31];
	temp -= dim;
	  }
	}
}

char temp_rotate32c_descr[] = "temp_rotate32c: unrolled j loop into 32, removed function call, idim, dimj";
void temp_rotate32c(int dim, pixel *src, pixel *dst)
{
	int i, j;
	for (i = 0; i < dim; i++){
	  int idim = dim*i;
	  for (j = 0; j < dim; j+=32){
		int idimj = idim+j;
	int dimj = (dim-j)*dim+i;
	dst[dimj-dim] = src[idimj];
		dst[dimj-dim*2] = src[idimj+1];
		dst[dimj-dim*3] = src[idimj+2];
		dst[dimj-dim*4] = src[idimj+3];
		dst[dimj-dim*5] = src[idimj+4];
		dst[dimj-dim*6] = src[idimj+5];
		dst[dimj-dim*7] = src[idimj+6];
		dst[dimj-dim*8] = src[idimj+7];
		dst[dimj-dim*9] = src[idimj+8];
		dst[dimj-dim*10] = src[idimj+9];
		dst[dimj-dim*11] = src[idimj+10];
		dst[dimj-dim*12] = src[idimj+11];
		dst[dimj-dim*13] = src[idimj+12];
		dst[dimj-dim*14] = src[idimj+13];
		dst[dimj-dim*15] = src[idimj+14];
		dst[dimj-dim*16] = src[idimj+15];
		dst[dimj-dim*17] = src[idimj+16];
		dst[dimj-dim*18] = src[idimj+17];
		dst[dimj-dim*19] = src[idimj+18];
		dst[dimj-dim*20] = src[idimj+19];
		dst[dimj-dim*21] = src[idimj+20];
		dst[dimj-dim*22] = src[idimj+21];
		dst[dimj-dim*23] = src[idimj+22];
		dst[dimj-dim*24] = src[idimj+23];
		dst[dimj-dim*25] = src[idimj+24];
		dst[dimj-dim*26] = src[idimj+25];
		dst[dimj-dim*27] = src[idimj+26];
		dst[dimj-dim*28] = src[idimj+27];
		dst[dimj-dim*29] = src[idimj+28];
		dst[dimj-dim*30] = src[idimj+29];
		dst[dimj-dim*31] = src[idimj+30];
		dst[dimj-dim*32] = src[idimj+31];
	  }
	}
}

char temp_rotate32e_descr[] = "temp_rotate32e: unrolled j loop into 32, removed function call, idim, dimj";
void temp_rotate32e(int dim, pixel *src, pixel *dst)
{
	
	int dim1 = dim-1;
	int i, j, i2 ;
	int b = 16;
	for (j = 0; j < dim; j+=b){
	  for (i = 0; i < dim; i+=b){
		for (i2 = i; i2 < i+b; i2++){
			dst[(dim1-j)*dim+i2] = src[i2*dim+j];
			dst[(dim1-j-1)*dim+i2] = src[i2*dim+j+1];
			dst[(dim1-j-2)*dim+i2] = src[i2*dim+j+2];
			dst[(dim1-j-3)*dim+i2] = src[i2*dim+j+3];
			dst[(dim1-j-4)*dim+i2] = src[i2*dim+j+4];
			dst[(dim1-j-5)*dim+i2] = src[i2*dim+j+5];
			dst[(dim1-j-6)*dim+i2] = src[i2*dim+j+6];
			dst[(dim1-j-7)*dim+i2] = src[i2*dim+j+7];
			dst[(dim1-j-8)*dim+i2] = src[i2*dim+j+8];
			dst[(dim1-j-9)*dim+i2] = src[i2*dim+j+9];
			dst[(dim1-j-10)*dim+i2] = src[i2*dim+j+10];
			dst[(dim1-j-11)*dim+i2] = src[i2*dim+j+11];
			dst[(dim1-j-12)*dim+i2] = src[i2*dim+j+12];
			dst[(dim1-j-13)*dim+i2] = src[i2*dim+j+13];
			dst[(dim1-j-14)*dim+i2] = src[i2*dim+j+14];
			dst[(dim1-j-15)*dim+i2] = src[i2*dim+j+15];
		}
	  }
	}
}

char temp_rotate32f_descr[] = "temp_rotate32f: 3.5, 3 loops, 32 unrolled";
void temp_rotate32f(int dim, pixel *src, pixel *dst)
{
	
	int dim1 = dim-1;
	int i, j, i2, dim1j, i2dimj;
	int b = 32;
	for (i = 0; i < dim; i+=b){
	  for (j = 0; j < dim; j+=b){
		for (i2 = i; i2 < i+b; i2++){
		dim1j = dim1-j;
			i2dimj = i2*dim+j;

/*	    dst = &dst[(dim-1-j)*dim+i2];
		src = &src[i2dimj];

		*dst = *src;
*/
			dst[(dim1j)*dim+i2] = src[i2dimj];
			dst[(dim1j-1)*dim+i2] = src[i2dimj+1];
			dst[(dim1j-2)*dim+i2] = src[i2dimj+2];
			dst[(dim1j-3)*dim+i2] = src[i2dimj+3];
			dst[(dim1j-4)*dim+i2] = src[i2dimj+4];
			dst[(dim1j-5)*dim+i2] = src[i2dimj+5];
			dst[(dim1j-6)*dim+i2] = src[i2dimj+6];
			dst[(dim1j-7)*dim+i2] = src[i2dimj+7];
			dst[(dim1j-8)*dim+i2] = src[i2dimj+8];
			dst[(dim1j-9)*dim+i2] = src[i2dimj+9];
			dst[(dim1j-10)*dim+i2] = src[i2dimj+10];
			dst[(dim1j-11)*dim+i2] = src[i2dimj+11];
			dst[(dim1j-12)*dim+i2] = src[i2dimj+12];
			dst[(dim1j-13)*dim+i2] = src[i2dimj+13];
			dst[(dim1j-14)*dim+i2] = src[i2dimj+14];
			dst[(dim1j-15)*dim+i2] = src[i2dimj+15];
			dst[(dim1j-16)*dim+i2] = src[i2dimj+16];
			dst[(dim1j-17)*dim+i2] = src[i2dimj+17];
			dst[(dim1j-18)*dim+i2] = src[i2dimj+18];
			dst[(dim1j-19)*dim+i2] = src[i2dimj+19];
			dst[(dim1j-20)*dim+i2] = src[i2dimj+20];
			dst[(dim1j-21)*dim+i2] = src[i2dimj+21];
			dst[(dim1j-22)*dim+i2] = src[i2dimj+22];
			dst[(dim1j-23)*dim+i2] = src[i2dimj+23];
			dst[(dim1j-24)*dim+i2] = src[i2dimj+24];
			dst[(dim1j-25)*dim+i2] = src[i2dimj+25];
			dst[(dim1j-26)*dim+i2] = src[i2dimj+26];
			dst[(dim1j-27)*dim+i2] = src[i2dimj+27];
			dst[(dim1j-28)*dim+i2] = src[i2dimj+28];
			dst[(dim1j-29)*dim+i2] = src[i2dimj+29];
			dst[(dim1j-30)*dim+i2] = src[i2dimj+30];
			dst[(dim1j-31)*dim+i2] = src[i2dimj+31];
		}
	  }
	}
}

char temp_rotate32g_descr[] = "temp_rotate32g: unrolled j loop into 32, removed function call, idim, dimj";
void temp_rotate32g(int dim, pixel *src, pixel *dst)
{

	int dim1 = dim-1;
	int i, j, i1,i2, i3,i4,i5,i6,i7, dim1j, j1,j2,j3;
	for (i = 0; i < dim; i+=8){
	  i1 = i+1;
	  i2 = i1+1;
	  i3 = i2+1;
	  i4 = i3+1;
	  i5 = i4+1;
	  i6 = i5+1;
	  i7 = i6+1;
	  
	  for (j = 0; j < dim; j+=4){
		j1 = j+1;
	j2 = j+2;
	j3 = j+3;
		dim1j = (dim1-j)*dim+i;
	dst[dim1j] = src[i*dim+j];
	dst[dim1j+1] = src[i1*dim+j];
	dst[dim1j+2] = src[i2*dim+j];
	dst[dim1j+3] = src[i3*dim+j];
	dst[dim1j+4] = src[i4*dim+j];
	dst[dim1j+5] = src[i5*dim+j];
	dst[dim1j+6] = src[i6*dim+j];
	dst[dim1j+7] = src[i7*dim+j];
		
	dim1j = (dim1-j1)*dim+i;
	dst[dim1j] = src[i*dim+j1];
	dst[dim1j+1] = src[i1*dim+j1];
	dst[dim1j+2] = src[i2*dim+j1];
	dst[dim1j+3] = src[i3*dim+j1];
	dst[dim1j+4] = src[i4*dim+j1];
	dst[dim1j+5] = src[i5*dim+j1];
	dst[dim1j+6] = src[i6*dim+j1];
	dst[dim1j+7] = src[i7*dim+j1];
	  
	dim1j = (dim1-j2)*dim+i;
	dst[dim1j] = src[i*dim+j2];
	dst[dim1j+1] = src[i1*dim+j2];
	dst[dim1j+2] = src[i2*dim+j2];
	dst[dim1j+3] = src[i3*dim+j2];
	dst[dim1j+4] = src[i4*dim+j2];
	dst[dim1j+5] = src[i5*dim+j2];
	dst[dim1j+6] = src[i6*dim+j2];
	dst[dim1j+7] = src[i7*dim+j2];
	  
		dim1j = (dim1-j3)*dim+i;
	dst[dim1j] = src[i*dim+j3];
	dst[dim1j+1] = src[i1*dim+j3];
	dst[dim1j+2] = src[i2*dim+j3];
	dst[dim1j+3] = src[i3*dim+j3];
	dst[dim1j+4] = src[i4*dim+j3];
	dst[dim1j+5] = src[i5*dim+j3];
	dst[dim1j+6] = src[i6*dim+j3];
	dst[dim1j+7] = src[i7*dim+j3];
	  
	  }
	}
}

char temp_rotate32h_descr[] = "temp_rotate32h: 3.5, 3 loops, 32 unrolled";
void temp_rotate32h(int dim, pixel *src, pixel *dst)
{
	
	int dim1 = dim-1;
	int i, j, i2, i3, i4, i5, dim1j, i2dimj;
	int dim1j1, dim1j2, dim1j3, dim1j4, dim1j5, dim1j6, dim1j7;
	int b = 8;
	for (i = 0; i < dim; i+=b){
	  for (j = 0; j < dim; j+=b){
		dim1j = dim1-j;
	dim1j1 = dim1j-1;
	dim1j2 = dim1j1-1;
	dim1j3 = dim1j2-1;
	dim1j4 = dim1j3-1;
	dim1j5 = dim1j4-1;
	dim1j6 = dim1j5-1;
	dim1j7 = dim1j6-1;
		for (i2 = i; i2 < i+b; i2+=4){
			i3 = i2+1;
		i4 = i3+1;
		i5 = i4+1;

			i2dimj = i2*dim+j;

			dst[(dim1j)*dim+i2] = src[i2dimj];
			dst[(dim1j1)*dim+i2] = src[i2dimj+1];
			dst[(dim1j2)*dim+i2] = src[i2dimj+2];
			dst[(dim1j3)*dim+i2] = src[i2dimj+3];
			dst[(dim1j4)*dim+i2] = src[i2dimj+4];
			dst[(dim1j5)*dim+i2] = src[i2dimj+5];
			dst[(dim1j6)*dim+i2] = src[i2dimj+6];
			dst[(dim1j7)*dim+i2] = src[i2dimj+7];

			i2dimj = i3*dim+j;

			dst[(dim1j)*dim+i3] = src[i2dimj];
			dst[(dim1j1)*dim+i3] = src[i2dimj+1];
			dst[(dim1j2)*dim+i3] = src[i2dimj+2];
			dst[(dim1j3)*dim+i3] = src[i2dimj+3];
			dst[(dim1j4)*dim+i3] = src[i2dimj+4];
			dst[(dim1j5)*dim+i3] = src[i2dimj+5];
			dst[(dim1j6)*dim+i3] = src[i2dimj+6];
			dst[(dim1j7)*dim+i3] = src[i2dimj+7];

			i2dimj = i4*dim+j;

			dst[(dim1j)*dim+i4] = src[i2dimj];
			dst[(dim1j1)*dim+i4] = src[i2dimj+1];
			dst[(dim1j2)*dim+i4] = src[i2dimj+2];
			dst[(dim1j3)*dim+i4] = src[i2dimj+3];
			dst[(dim1j4)*dim+i4] = src[i2dimj+4];
			dst[(dim1j5)*dim+i4] = src[i2dimj+5];
			dst[(dim1j6)*dim+i4] = src[i2dimj+6];
			dst[(dim1j7)*dim+i4] = src[i2dimj+7];

			i2dimj = i5*dim+j;

			dst[(dim1j)*dim+i5] = src[i2dimj];
			dst[(dim1j1)*dim+i5] = src[i2dimj+1];
			dst[(dim1j2)*dim+i5] = src[i2dimj+2];
			dst[(dim1j3)*dim+i5] = src[i2dimj+3];
			dst[(dim1j4)*dim+i5] = src[i2dimj+4];
			dst[(dim1j5)*dim+i5] = src[i2dimj+5];
			dst[(dim1j6)*dim+i5] = src[i2dimj+6];
			dst[(dim1j7)*dim+i5] = src[i2dimj+7];

	   }
	}
  }
}

char temp_rotate32i_descr[] = "temp_rotate32i: pointers";
void temp_rotate32i(int dim, pixel *src, pixel *dst)
{
	
	int dim1 = dim-1;
	int i, j, i2;
	int b = 8;
	for (i = 0; i < dim; i+=b){
	  for (j = 0; j < dim; j+=b){
	for (i2 = i; i2 < i+b; i2++){
	  dst = &dst[(dim1-j)*dim+i2];
	  src = &src[i2*dim+j];
	  
	  *dst = *src;
	  src++;
	  dst -= dim;
	  
	  *dst = *src;
	  src++;
	  dst -= dim;
	  
	  *dst = *src;
	  src++;
	  dst -= dim;
	  
	  *dst = *src;
	  src++;
	  dst -= dim;
	  
	  *dst = *src;
	  src++;
	  dst -= dim;
	  
	  *dst = *src;
	  src++;
	  dst -= dim;
	  
	  *dst = *src;
	  src++;
	  dst -= dim;
	  
	  *dst = *src;
		
	} 
	  }
	}
}


/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_rotate_functions()
{
   // add_rotate_function(&naive_rotate, naive_rotate_descr);
   add_rotate_function(&rotate, rotate_descr);
	/* ... Register additional test functions here */
   // add_rotate_function(&temp_rotate, temp_rotate_descr);
   // add_rotate_function(&temp_rotate32, temp_rotate32_descr);
   // add_rotate_function(&temp_rotate32a, temp_rotate32a_descr);
   // add_rotate_function(&temp_rotate32b, temp_rotate32b_descr);
   // add_rotate_function(&temp_rotate32c, temp_rotate32c_descr);
   // add_rotate_function(&temp_rotate32e, temp_rotate32e_descr);
   //add_rotate_function(&temp_rotate32f, temp_rotate32f_descr);
   //add_rotate_function(&temp_rotate32g, temp_rotate32g_descr);
   //add_rotate_function(&temp_rotate32h, temp_rotate32h_descr);
   //add_rotate_function(&temp_rotate32i, temp_rotate32i_descr);

}


/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
	int red;
	int green;
	int blue;
	int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/*
 * initialize_pixel_sum - Initializes all fields of sum to 0
 */
static void initialize_pixel_sum(pixel_sum *sum)
{
	sum->red = sum->green = sum->blue = 0;
	sum->num = 0;
	return;
}

/*
 * accumulate_sum - Accumulates field values of p in corresponding
 * fields of sum
 */
static void accumulate_sum(pixel_sum *sum, pixel p)
{
	sum->red += (int) p.red;
	sum->green += (int) p.green;
	sum->blue += (int) p.blue;
	sum->num++;
	return;
}

/*
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum)
{
	current_pixel->red = (unsigned short) (sum.red/sum.num);
	current_pixel->green = (unsigned short) (sum.green/sum.num);
	current_pixel->blue = (unsigned short) (sum.blue/sum.num);
	return;
}

/*
 * avg - Returns averaged pixel value at (i,j)
 */
static pixel avg(int dim, int i, int j, pixel *src)
{
	int ii, jj;
	pixel_sum sum;
	pixel current_pixel;

	initialize_pixel_sum(&sum);
	for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++)
  for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++)
	  accumulate_sum(&sum, src[array_index(ii, jj, dim)]);

	assign_sum_to_pixel(&current_pixel, sum);
	return current_pixel;
}

/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst)
{
	int i, j;
	for (j = 0; j < dim; j++)
	  for (i = 0; i < dim; i++)
		dst[array_index(i, j, dim)] = avg(dim, i, j, src);
}

/*
 * smooth - Your current working version of smooth.
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "smooth: Current working version";
void smooth(int dim, pixel *src, pixel *dst)
{
	smoothB(dim, src, dst);
}
char smoothA_descr[] = "smoothA: removed func calls";
void smoothA(int dim, pixel *src, pixel *dst)
{
	int i, j; 
	int dim1 = dim-1;
	int idim,idimM1, idimP1;
		pixel_sum sum;
		pixel current_pixel;

	for (i = 0; i < dim; i++)
		{	
		for (j = 0; j < dim; j++)
			{
			
				//initialize_pixel_sum(&sum);
			sum.red = sum.green = sum.blue = 0;
			sum.num = 0;
			
			if(i==0)
			{	
					idim = i*dim;
					idimP1 = (i+1)*dim;
				if(j==0)
				{
					sum.red += src[idim+j].red;
					sum.blue += src[idim+j].blue;
					sum.green += src[idim+j].green;
					sum.num++;
					sum.red += src[idim+j+1].red;
					sum.blue += src[idim+j+1].blue;
					sum.green += src[idim+j+1].green;
					sum.num++;
					//accumulate_sum(&sum, src[idim+j]);
					//accumulate_sum(&sum, src[idim+j+1]);
					
					sum.red += src[idimP1+j].red;
					sum.blue += src[idimP1+j].blue;
					sum.green += src[idimP1+j].green;
					sum.num++;
					sum.red += src[idimP1+j+1].red;
					sum.blue += src[idimP1+j+1].blue;
					sum.green += src[idimP1+j+1].green;
					sum.num++;
					//accumulate_sum(&sum, src[idimP1+j]);
					//accumulate_sum(&sum, src[idimP1+j+1]);
				
				}
				else if(j==dim1)
				{
					sum.red += src[idim+j-1].red;
					sum.blue += src[idim+j-1].blue;
					sum.green += src[idim+j-1].green;
					sum.num++;
					sum.red += src[idim+j].red;
					sum.blue += src[idim+j].blue;
					sum.green += src[idim+j].green;
					sum.num++;
					//accumulate_sum(&sum, src[idim+j-1]);
					//accumulate_sum(&sum, src[idim+j]);
	
					sum.red += src[idimP1+j-1].red;
					sum.blue += src[idimP1+j-1].blue;
					sum.green += src[idimP1+j-1].green;
					sum.num++;
					sum.red += src[idimP1+j].red;
					sum.blue += src[idimP1+j].blue;
					sum.green += src[idimP1+j].green;
					sum.num++;
					//accumulate_sum(&sum, src[idimP1+j-1]);
					//accumulate_sum(&sum, src[idimP1+j]);

				}
				else
				{
					sum.red += src[idim+j-1].red;
					sum.blue += src[idim+j-1].blue;
					sum.green += src[idim+j-1].green;
					sum.num++;
					sum.red += src[idim+j].red;
					sum.blue += src[idim+j].blue;
					sum.green += src[idim+j].green;
					sum.num++;
					sum.red += src[idim+j+1].red;
					sum.blue += src[idim+j+1].blue;
					sum.green += src[idim+j+1].green;
					sum.num++;
					//accumulate_sum(&sum, src[idim+j-1]);
					//accumulate_sum(&sum, src[idim+j]);
					//accumulate_sum(&sum, src[idim+j+1]);
					
					sum.red += src[idimP1+j-1].red;
					sum.blue += src[idimP1+j-1].blue;
					sum.green += src[idimP1+j-1].green;
					sum.num++;
					sum.red += src[idimP1+j].red;
					sum.blue += src[idimP1+j].blue;
					sum.green += src[idimP1+j].green;
					sum.num++;
					sum.red += src[idimP1+j+1].red;
					sum.blue += src[idimP1+j+1].blue;
					sum.green += src[idimP1+j+1].green;
					sum.num++;
					//accumulate_sum(&sum, src[idimP1+j-1]);
					//accumulate_sum(&sum, src[idimP1+j]);
					//accumulate_sum(&sum, src[idimP1+j+1]);
				}
			}
			else if(i==dim1)
			{	
					idim = i*dim;
					idimM1 = (i-1)*dim;
				if(j==0)
				{
					sum.red += src[idimM1+j].red;
					sum.blue += src[idimM1+j].blue;
					sum.green += src[idimM1+j].green;
					sum.num++;
					sum.red += src[idimM1+j+1].red;
					sum.blue += src[idimM1+j+1].blue;
					sum.green += src[idimM1+j+1].green;
					sum.num++;
					//accumulate_sum(&sum, src[idimM1+j]);
					//accumulate_sum(&sum, src[idimM1+j+1]);
					
					sum.red += src[idim+j].red;
					sum.blue += src[idim+j].blue;
					sum.green += src[idim+j].green;
					sum.num++;
					sum.red += src[idim+j+1].red;
					sum.blue += src[idim+j+1].blue;
					sum.green += src[idim+j+1].green;
					sum.num++;
					//accumulate_sum(&sum, src[idim+j]);
					//accumulate_sum(&sum, src[idim+j+1]);
				
				}
				else if(j==dim1)
				{
					sum.red += src[idimM1+j-1].red;
					sum.blue += src[idimM1+j-1].blue;
					sum.green += src[idimM1+j-1].green;
					sum.num++;
					sum.red += src[idimM1+j].red;
					sum.blue += src[idimM1+j].blue;
					sum.green += src[idimM1+j].green;
					sum.num++;
					//accumulate_sum(&sum, src[idimM1+j-1]);
					//accumulate_sum(&sum, src[idimM1+j]);
	
					sum.red += src[idim+j-1].red;
					sum.blue += src[idim+j-1].blue;
					sum.green += src[idim+j-1].green;
					sum.num++;
					sum.red += src[idim+j].red;
					sum.blue += src[idim+j].blue;
					sum.green += src[idim+j].green;
					sum.num++;
					//accumulate_sum(&sum, src[idim+j-1]);
					//accumulate_sum(&sum, src[idim+j]);

				}
				else
				{
					sum.red += src[idimM1+j-1].red;
					sum.blue += src[idimM1+j-1].blue;
					sum.green += src[idimM1+j-1].green;
					sum.num++;
					sum.red += src[idimM1+j].red;
					sum.blue += src[idimM1+j].blue;
					sum.green += src[idimM1+j].green;
					sum.num++;
					sum.red += src[idimM1+j+1].red;
					sum.blue += src[idimM1+j+1].blue;
					sum.green += src[idimM1+j+1].green;
					sum.num++;
					//accumulate_sum(&sum, src[idimM1+j-1]);
					//accumulate_sum(&sum, src[idimM1+j]);
					//accumulate_sum(&sum, src[idimM1+j+1]);
					
					sum.red += src[idim+j-1].red;
					sum.blue += src[idim+j-1].blue;
					sum.green += src[idim+j-1].green;
					sum.num++;
					sum.red += src[idim+j].red;
					sum.blue += src[idim+j].blue;
					sum.green += src[idim+j].green;
					sum.num++;
					sum.red += src[idim+j+1].red;
					sum.blue += src[idim+j+1].blue;
					sum.green += src[idim+j+1].green;
					sum.num++;
					//accumulate_sum(&sum, src[idim+j-1]);
					//accumulate_sum(&sum, src[idim+j]);
					//accumulate_sum(&sum, src[idim+j+1]);
				}
			}
			else
			{
					idim = i*dim;
					idimM1 = (i-1)*dim;
					idimP1 = (i+1)*dim;
				if(j==0)
				{
					sum.red += src[idimM1+j].red;
					sum.blue += src[idimM1+j].blue;
					sum.green += src[idimM1+j].green;
					sum.num++;
					sum.red += src[idimM1+j+1].red;
					sum.blue += src[idimM1+j+1].blue;
					sum.green += src[idimM1+j+1].green;
					sum.num++;
					//accumulate_sum(&sum, src[idimM1+j]);
					//accumulate_sum(&sum, src[idimM1+j+1]);
					
					sum.red += src[idim+j].red;
					sum.blue += src[idim+j].blue;
					sum.green += src[idim+j].green;
					sum.num++;
					sum.red += src[idim+j+1].red;
					sum.blue += src[idim+j+1].blue;
					sum.green += src[idim+j+1].green;
					sum.num++;
					//accumulate_sum(&sum, src[idim+j]);
					//accumulate_sum(&sum, src[idim+j+1]);
					
					sum.red += src[idimP1+j].red;
					sum.blue += src[idimP1+j].blue;
					sum.green += src[idimP1+j].green;
					sum.num++;
					sum.red += src[idimP1+j+1].red;
					sum.blue += src[idimP1+j+1].blue;
					sum.green += src[idimP1+j+1].green;
					sum.num++;
					//accumulate_sum(&sum, src[idimP1+j]);
					//accumulate_sum(&sum, src[idimP1+j+1]);
					
				}
				else if(j==dim1)
				{
					sum.red += src[idimM1+j-1].red;
					sum.blue += src[idimM1+j-1].blue;
					sum.green += src[idimM1+j-1].green;
					sum.num++;
					sum.red += src[idimM1+j].red;
					sum.blue += src[idimM1+j].blue;
					sum.green += src[idimM1+j].green;
					sum.num++;
					//accumulate_sum(&sum, src[idimM1+j-1]);
					//accumulate_sum(&sum, src[idimM1+j]);
				
					sum.red += src[idim+j-1].red;
					sum.blue += src[idim+j-1].blue;
					sum.green += src[idim+j-1].green;
					sum.num++;
					sum.red += src[idim+j].red;
					sum.blue += src[idim+j].blue;
					sum.green += src[idim+j].green;
					sum.num++;
					//accumulate_sum(&sum, src[idim+j-1]);
					//accumulate_sum(&sum, src[idim+j]);
		
					sum.red += src[idimP1+j-1].red;
					sum.blue += src[idimP1+j-1].blue;
					sum.green += src[idimP1+j-1].green;
					sum.num++;
					sum.red += src[idimP1+j].red;
					sum.blue += src[idimP1+j].blue;
					sum.green += src[idimP1+j].green;
					sum.num++;
					//accumulate_sum(&sum, src[idimP1+j-1]);
					//accumulate_sum(&sum, src[idimP1+j]);

				}
				else
				{
					sum.red += src[idimM1+j-1].red;
					sum.blue += src[idimM1+j-1].blue;
					sum.green += src[idimM1+j-1].green;
					sum.num++;
					sum.red += src[idimM1+j].red;
					sum.blue += src[idimM1+j].blue;
					sum.green += src[idimM1+j].green;
					sum.num++;
					sum.red += src[idimM1+j+1].red;
					sum.blue += src[idimM1+j+1].blue;
					sum.green += src[idimM1+j+1].green;
					sum.num++;
					//accumulate_sum(&sum, src[idimM1+j-1]);
					//accumulate_sum(&sum, src[idimM1+j]);
					//accumulate_sum(&sum, src[idimM1+j+1]);
		
					sum.red += src[idim+j-1].red;
					sum.blue += src[idim+j-1].blue;
					sum.green += src[idim+j-1].green;
					sum.num++;
					sum.red += src[idim+j].red;
					sum.blue += src[idim+j].blue;
					sum.green += src[idim+j].green;
					sum.num++;
					sum.red += src[idim+j+1].red;
					sum.blue += src[idim+j+1].blue;
					sum.green += src[idim+j+1].green;
					sum.num++;
					//accumulate_sum(&sum, src[idim+j-1]);
					//accumulate_sum(&sum, src[idim+j]);
					//accumulate_sum(&sum, src[idim+j+1]);
					
					sum.red += src[idimP1+j-1].red;
					sum.blue += src[idimP1+j-1].blue;
					sum.green += src[idimP1+j-1].green;
					sum.num++;
					sum.red += src[idimP1+j].red;
					sum.blue += src[idimP1+j].blue;
					sum.green += src[idimP1+j].green;
					sum.num++;
					sum.red += src[idimP1+j+1].red;
					sum.blue += src[idimP1+j+1].blue;
					sum.green += src[idimP1+j+1].green;
					sum.num++;
					//accumulate_sum(&sum, src[idimP1+j-1]);
					//accumulate_sum(&sum, src[idimP1+j]);
					//accumulate_sum(&sum, src[idimP1+j+1]);
				}
			}
		//assign_sum_to_pixel(&current_pixel, sum);
			current_pixel.red = (sum.red/sum.num);
			current_pixel.blue = (sum.blue/sum.num);
			current_pixel.green = (sum.green/sum.num);
		dst[i*dim+j] = current_pixel;
		}
	}
}

char smoothB_descr[] = "smoothB: removed func calls";
void smoothB(int dim, pixel *src, pixel *dst)
{
	int i = 0;
	int j = 0; 
	int idim,idimM1, idimP1;
		pixel_sum sum;
		pixel current_pixel;
	
	sum.red = sum.green = sum.blue = 0;
	sum.num = 0;
	//first row	
	idim = i*dim;
	idimP1 = (i+1)*dim;
	// first square
	sum.red += src[idim+j].red;
	sum.blue += src[idim+j].blue;
	sum.green += src[idim+j].green;
	sum.num++;
	sum.red += src[idim+j+1].red;
	sum.blue += src[idim+j+1].blue;
	sum.green += src[idim+j+1].green;
	sum.num++;
	//accumulate_sum(&sum, src[idim+j]);
	//accumulate_sum(&sum, src[idim+j+1]);
	sum.red += src[idimP1+j].red;
	sum.blue += src[idimP1+j].blue;
	sum.green += src[idimP1+j].green;
	sum.num++;
	sum.red += src[idimP1+j+1].red;
	sum.blue += src[idimP1+j+1].blue;
	sum.green += src[idimP1+j+1].green;
	sum.num++;
	//accumulate_sum(&sum, src[idimP1+j]);
	//accumulate_sum(&sum, src[idimP1+j+1]);
	current_pixel.red = (sum.red/sum.num);
	current_pixel.blue = (sum.blue/sum.num);
	current_pixel.green = (sum.green/sum.num);
	dst[i*dim+j] = current_pixel;
	//first row, 1-(dim-2)
	for (j = 1; j < dim - 1; j++){
		sum.red = sum.green = sum.blue = 0;
		sum.num = 0;
		
		sum.red += src[idim+j-1].red;
		sum.blue += src[idim+j-1].blue;
		sum.green += src[idim+j-1].green;
		sum.num++;
		sum.red += src[idim+j].red;
		sum.blue += src[idim+j].blue;
		sum.green += src[idim+j].green;
		sum.num++;
		sum.red += src[idim+j+1].red;
		sum.blue += src[idim+j+1].blue;
		sum.green += src[idim+j+1].green;
		sum.num++;
		//accumulate_sum(&sum, src[idim+j-1]);
		//accumulate_sum(&sum, src[idim+j]);
		//accumulate_sum(&sum, src[idim+j+1]);
		
		sum.red += src[idimP1+j-1].red;
		sum.blue += src[idimP1+j-1].blue;
		sum.green += src[idimP1+j-1].green;
		sum.num++;
		sum.red += src[idimP1+j].red;
		sum.blue += src[idimP1+j].blue;
		sum.green += src[idimP1+j].green;
		sum.num++;
		sum.red += src[idimP1+j+1].red;
		sum.blue += src[idimP1+j+1].blue;
		sum.green += src[idimP1+j+1].green;
		sum.num++;
		//accumulate_sum(&sum, src[idimP1+j-1]);
		//accumulate_sum(&sum, src[idimP1+j]);
		//accumulate_sum(&sum, src[idimP1+j+1]);
		
		current_pixel.red = (sum.red/sum.num);
		current_pixel.blue = (sum.blue/sum.num);
		current_pixel.green = (sum.green/sum.num);
		dst[i*dim+j] = current_pixel;
	}
	j = dim-1;
	//first row, last square
	sum.red = sum.green = sum.blue = 0;
	sum.num = 0;
	
	sum.red += src[idim+j-1].red;
	sum.blue += src[idim+j-1].blue;
	sum.green += src[idim+j-1].green;
	sum.num++;
	sum.red += src[idim+j].red;
	sum.blue += src[idim+j].blue;
	sum.green += src[idim+j].green;
	sum.num++;
	//accumulate_sum(&sum, src[idim+j-1]);
	//accumulate_sum(&sum, src[idim+j]);

	sum.red += src[idimP1+j-1].red;
	sum.blue += src[idimP1+j-1].blue;
	sum.green += src[idimP1+j-1].green;
	sum.num++;
	sum.red += src[idimP1+j].red;
	sum.blue += src[idimP1+j].blue;
	sum.green += src[idimP1+j].green;
	sum.num++;
	//accumulate_sum(&sum, src[idimP1+j-1]);
	//accumulate_sum(&sum, src[idimP1+j]);
	current_pixel.red = (sum.red/sum.num);
	current_pixel.blue = (sum.blue/sum.num);
	current_pixel.green = (sum.green/sum.num);
	dst[i*dim+j] = current_pixel;	
	
	i = dim-1;
	j = 0;
	idim = i*dim;
	idimM1 = (i-1)*dim;
	//last row, first square
	sum.red = sum.green = sum.blue = 0;
	sum.num = 0;
	sum.red += src[idimM1+j].red;
	sum.blue += src[idimM1+j].blue;
	sum.green += src[idimM1+j].green;
	sum.num++;
	sum.red += src[idimM1+j+1].red;
	sum.blue += src[idimM1+j+1].blue;
	sum.green += src[idimM1+j+1].green;
	sum.num++;
	//accumulate_sum(&sum, src[idimM1+j]);
	//accumulate_sum(&sum, src[idimM1+j+1]);
	
	sum.red += src[idim+j].red;
	sum.blue += src[idim+j].blue;
	sum.green += src[idim+j].green;
	sum.num++;
	sum.red += src[idim+j+1].red;
	sum.blue += src[idim+j+1].blue;
	sum.green += src[idim+j+1].green;
	sum.num++;
	//accumulate_sum(&sum, src[idim+j]);
	//accumulate_sum(&sum, src[idim+j+1]);
	current_pixel.red = (sum.red/sum.num);
	current_pixel.blue = (sum.blue/sum.num);
	current_pixel.green = (sum.green/sum.num);
	dst[i*dim+j] = current_pixel;
	
	//last row, middle 1 -> (dim-2)
	for (j = 1; j < dim-1; j++){
		sum.red = sum.green = sum.blue = 0;
		sum.num = 0;
		
		sum.red += src[idimM1+j-1].red;
		sum.blue += src[idimM1+j-1].blue;
		sum.green += src[idimM1+j-1].green;
		sum.num++;
		sum.red += src[idimM1+j].red;
		sum.blue += src[idimM1+j].blue;
		sum.green += src[idimM1+j].green;
		sum.num++;
		sum.red += src[idimM1+j+1].red;
		sum.blue += src[idimM1+j+1].blue;
		sum.green += src[idimM1+j+1].green;
		sum.num++;
		//accumulate_sum(&sum, src[idimM1+j-1]);
		//accumulate_sum(&sum, src[idimM1+j]);
		//accumulate_sum(&sum, src[idimM1+j+1]);
		
		sum.red += src[idim+j-1].red;
		sum.blue += src[idim+j-1].blue;
		sum.green += src[idim+j-1].green;
		sum.num++;
		sum.red += src[idim+j].red;
		sum.blue += src[idim+j].blue;
		sum.green += src[idim+j].green;
		sum.num++;
		sum.red += src[idim+j+1].red;
		sum.blue += src[idim+j+1].blue;
		sum.green += src[idim+j+1].green;
		sum.num++;
		//accumulate_sum(&sum, src[idim+j-1]);
		//accumulate_sum(&sum, src[idim+j]);
		//accumulate_sum(&sum, src[idim+j+1]);
		current_pixel.red = (sum.red/sum.num);
		current_pixel.blue = (sum.blue/sum.num);
		current_pixel.green = (sum.green/sum.num);
		dst[i*dim+j] = current_pixel;
	}
	
	//last row, last square
	j = dim-1;
	sum.red = sum.green = sum.blue = 0;
	sum.num = 0;
	
	sum.red += src[idimM1+j-1].red;
	sum.blue += src[idimM1+j-1].blue;
	sum.green += src[idimM1+j-1].green;
	sum.num++;
	sum.red += src[idimM1+j].red;
	sum.blue += src[idimM1+j].blue;
	sum.green += src[idimM1+j].green;
	sum.num++;
	//accumulate_sum(&sum, src[idimM1+j-1]);
	//accumulate_sum(&sum, src[idimM1+j]);

	sum.red += src[idim+j-1].red;
	sum.blue += src[idim+j-1].blue;
	sum.green += src[idim+j-1].green;
	sum.num++;
	sum.red += src[idim+j].red;
	sum.blue += src[idim+j].blue;
	sum.green += src[idim+j].green;
	sum.num++;
	//accumulate_sum(&sum, src[idim+j-1]);
	//accumulate_sum(&sum, src[idim+j]);
	current_pixel.red = (sum.red/sum.num);
	current_pixel.blue = (sum.blue/sum.num);
	current_pixel.green = (sum.green/sum.num);
	dst[i*dim+j] = current_pixel;
	
	
	for (i = 1; i < dim-1; i++){
		idim = i*dim;
		idimM1 = (i-1)*dim;
		idimP1 = (i+1)*dim;
		
		//first col
		j = 0;
		sum.red = sum.green = sum.blue = 0;
		sum.num = 0;
		
		sum.red += src[idimM1+j].red;
		sum.blue += src[idimM1+j].blue;
		sum.green += src[idimM1+j].green;
		sum.num++;
		sum.red += src[idimM1+j+1].red;
		sum.blue += src[idimM1+j+1].blue;
		sum.green += src[idimM1+j+1].green;
		sum.num++;
		//accumulate_sum(&sum, src[idimM1+j]);
		//accumulate_sum(&sum, src[idimM1+j+1]);
		
		sum.red += src[idim+j].red;
		sum.blue += src[idim+j].blue;
		sum.green += src[idim+j].green;
		sum.num++;
		sum.red += src[idim+j+1].red;
		sum.blue += src[idim+j+1].blue;
		sum.green += src[idim+j+1].green;
		sum.num++;
		//accumulate_sum(&sum, src[idim+j]);
		//accumulate_sum(&sum, src[idim+j+1]);
		
		sum.red += src[idimP1+j].red;
		sum.blue += src[idimP1+j].blue;
		sum.green += src[idimP1+j].green;
		sum.num++;
		sum.red += src[idimP1+j+1].red;
		sum.blue += src[idimP1+j+1].blue;
		sum.green += src[idimP1+j+1].green;
		sum.num++;
		//accumulate_sum(&sum, src[idimP1+j]);
		//accumulate_sum(&sum, src[idimP1+j+1]);
		
		current_pixel.red = (sum.red/sum.num);
		current_pixel.blue = (sum.blue/sum.num);
		current_pixel.green = (sum.green/sum.num);
		dst[i*dim+j] = current_pixel;
		
		for (j = 1; j < dim-1; j++){		
			//initialize_pixel_sum(&sum);
			sum.red = sum.green = sum.blue = 0;
			sum.num = 0;
			
			sum.red += src[idimM1+j-1].red;
			sum.blue += src[idimM1+j-1].blue;
			sum.green += src[idimM1+j-1].green;
			sum.num++;
			sum.red += src[idimM1+j].red;
			sum.blue += src[idimM1+j].blue;
			sum.green += src[idimM1+j].green;
			sum.num++;
			sum.red += src[idimM1+j+1].red;
			sum.blue += src[idimM1+j+1].blue;
			sum.green += src[idimM1+j+1].green;
			sum.num++;
			//accumulate_sum(&sum, src[idimM1+j-1]);
			//accumulate_sum(&sum, src[idimM1+j]);
			//accumulate_sum(&sum, src[idimM1+j+1]);

			sum.red += src[idim+j-1].red;
			sum.blue += src[idim+j-1].blue;
			sum.green += src[idim+j-1].green;
			sum.num++;
			sum.red += src[idim+j].red;
			sum.blue += src[idim+j].blue;
			sum.green += src[idim+j].green;
			sum.num++;
			sum.red += src[idim+j+1].red;
			sum.blue += src[idim+j+1].blue;
			sum.green += src[idim+j+1].green;
			sum.num++;
			//accumulate_sum(&sum, src[idim+j-1]);
			//accumulate_sum(&sum, src[idim+j]);
			//accumulate_sum(&sum, src[idim+j+1]);
			
			sum.red += src[idimP1+j-1].red;
			sum.blue += src[idimP1+j-1].blue;
			sum.green += src[idimP1+j-1].green;
			sum.num++;
			sum.red += src[idimP1+j].red;
			sum.blue += src[idimP1+j].blue;
			sum.green += src[idimP1+j].green;
			sum.num++;
			sum.red += src[idimP1+j+1].red;
			sum.blue += src[idimP1+j+1].blue;
			sum.green += src[idimP1+j+1].green;
			sum.num++;
			//accumulate_sum(&sum, src[idimP1+j-1]);
			//accumulate_sum(&sum, src[idimP1+j]);
			//accumulate_sum(&sum, src[idimP1+j+1]);
				
			//assign_sum_to_pixel(&current_pixel, sum);
			current_pixel.red = (sum.red/sum.num);
			current_pixel.blue = (sum.blue/sum.num);
			current_pixel.green = (sum.green/sum.num);
			dst[i*dim+j] = current_pixel;
		}
		// last col
		j = dim-1;
		
		sum.red = sum.green = sum.blue = 0;
		sum.num = 0;
		
		sum.red += src[idimM1+j-1].red;
		sum.blue += src[idimM1+j-1].blue;
		sum.green += src[idimM1+j-1].green;
		sum.num++;
		sum.red += src[idimM1+j].red;
		sum.blue += src[idimM1+j].blue;
		sum.green += src[idimM1+j].green;
		sum.num++;
		//accumulate_sum(&sum, src[idimM1+j-1]);
		//accumulate_sum(&sum, src[idimM1+j]);
	
		sum.red += src[idim+j-1].red;
		sum.blue += src[idim+j-1].blue;
		sum.green += src[idim+j-1].green;
		sum.num++;
		sum.red += src[idim+j].red;
		sum.blue += src[idim+j].blue;
		sum.green += src[idim+j].green;
		sum.num++;
		//accumulate_sum(&sum, src[idim+j-1]);
		//accumulate_sum(&sum, src[idim+j]);

		sum.red += src[idimP1+j-1].red;
		sum.blue += src[idimP1+j-1].blue;
		sum.green += src[idimP1+j-1].green;
		sum.num++;
		sum.red += src[idimP1+j].red;
		sum.blue += src[idimP1+j].blue;
		sum.green += src[idimP1+j].green;
		sum.num++;
		//accumulate_sum(&sum, src[idimP1+j-1]);
		//accumulate_sum(&sum, src[idimP1+j]);
		
		current_pixel.red = (sum.red/sum.num);
		current_pixel.blue = (sum.blue/sum.num);
		current_pixel.green = (sum.green/sum.num);
		dst[i*dim+j] = current_pixel;
	}
}

char smooth2_descr[] = "smooth2: avg function implemented within smooth";
void smooth2(int dim, pixel *src, pixel *dst)
{
	int i, j; 
	
		pixel_sum sum;
		pixel current_pixel;

	for (i = 0; i < dim; i++)
		{	
			for (j = 0; j < dim; j++)
			{
				initialize_pixel_sum(&sum);
			if(i==0)
			{	
				if(j==0)
				{
					
					accumulate_sum(&sum, src[array_index(i,j,dim)]);
					accumulate_sum(&sum, src[array_index(i,j+1,dim)]);
					
					accumulate_sum(&sum, src[array_index(i+1,j,dim)]);
					accumulate_sum(&sum, src[array_index(i+1,j+1,dim)]);
				
				}
				else if(j==dim-1)
				{
					accumulate_sum(&sum, src[array_index(i,j-1,dim)]);
					accumulate_sum(&sum, src[array_index(i,j,dim)]);
	
					accumulate_sum(&sum, src[array_index(i+1,j-1,dim)]);
					accumulate_sum(&sum, src[array_index(i+1,j,dim)]);

				}
				else
				{
					accumulate_sum(&sum, src[array_index(i,j-1,dim)]);
					accumulate_sum(&sum, src[array_index(i,j,dim)]);
					accumulate_sum(&sum, src[array_index(i,j+1,dim)]);
					
					accumulate_sum(&sum, src[array_index(i+1,j-1,dim)]);
					accumulate_sum(&sum, src[array_index(i+1,j,dim)]);
					accumulate_sum(&sum, src[array_index(i+1,j+1,dim)]);
				}
			}
			else if(i==dim-1)
			{	
				if(j==0)
				{
					
					accumulate_sum(&sum, src[array_index(i-1,j,dim)]);
					accumulate_sum(&sum, src[array_index(i-1,j+1,dim)]);
					
					accumulate_sum(&sum, src[array_index(i,j,dim)]);
					accumulate_sum(&sum, src[array_index(i,j+1,dim)]);
				
				}
				else if(j==dim-1)
				{
					accumulate_sum(&sum, src[array_index(i-1,j-1,dim)]);
					accumulate_sum(&sum, src[array_index(i-1,j,dim)]);
	
					accumulate_sum(&sum, src[array_index(i,j-1,dim)]);
					accumulate_sum(&sum, src[array_index(i,j,dim)]);

				}
				else
				{
					accumulate_sum(&sum, src[array_index(i-1,j-1,dim)]);
					accumulate_sum(&sum, src[array_index(i-1,j,dim)]);
					accumulate_sum(&sum, src[array_index(i-1,j+1,dim)]);
					
					accumulate_sum(&sum, src[array_index(i,j-1,dim)]);
					accumulate_sum(&sum, src[array_index(i,j,dim)]);
					accumulate_sum(&sum, src[array_index(i,j+1,dim)]);
				}
			}
			else
			{
				if(j==0)
				{
					accumulate_sum(&sum, src[array_index(i-1,j,dim)]);
					accumulate_sum(&sum, src[array_index(i-1,j+1,dim)]);
					
					accumulate_sum(&sum, src[array_index(i,j,dim)]);
					accumulate_sum(&sum, src[array_index(i,j+1,dim)]);
					
					accumulate_sum(&sum, src[array_index(i+1,j,dim)]);
					accumulate_sum(&sum, src[array_index(i+1,j+1,dim)]);
					
				}
				else if(j==dim-1)
				{
					accumulate_sum(&sum, src[array_index(i-1,j-1,dim)]);
					accumulate_sum(&sum, src[array_index(i-1,j,dim)]);
				
					accumulate_sum(&sum, src[array_index(i,j-1,dim)]);
					accumulate_sum(&sum, src[array_index(i,j,dim)]);
		
					accumulate_sum(&sum, src[array_index(i+1,j-1,dim)]);
					accumulate_sum(&sum, src[array_index(i+1,j,dim)]);

				}
				else
				{
					accumulate_sum(&sum, src[array_index(i-1,j-1,dim)]);
					accumulate_sum(&sum, src[array_index(i-1,j,dim)]);
					accumulate_sum(&sum, src[array_index(i-1,j+1,dim)]);
		
					accumulate_sum(&sum, src[array_index(i,j-1,dim)]);
					accumulate_sum(&sum, src[array_index(i,j,dim)]);
					accumulate_sum(&sum, src[array_index(i,j+1,dim)]);
					
					accumulate_sum(&sum, src[array_index(i+1,j-1,dim)]);
					accumulate_sum(&sum, src[array_index(i+1,j,dim)]);
					accumulate_sum(&sum, src[array_index(i+1,j+1,dim)]);
				}
			}
		assign_sum_to_pixel(&current_pixel, sum);
			dst[array_index(i, j, dim)] = current_pixel;
		}
	}
}
char smooth3_descr[] = "smooth3: avg function implemented within smooth & attempted loop unrolling";
void smooth3(int dim, pixel *src, pixel *dst)
{
	int i, j; 
	
		pixel_sum sum;
		pixel current_pixel;

	for (i = 0; i < dim; i++)
		{	
			for (j = 0; j < dim; j+=2)
			{
				initialize_pixel_sum(&sum);
			if(i==0)
			{	
				if(j==0)
				{
					
					accumulate_sum(&sum, src[array_index(i,j,dim)]);
					accumulate_sum(&sum, src[array_index(i,j+1,dim)]);
					
					accumulate_sum(&sum, src[array_index(i+1,j,dim)]);
					accumulate_sum(&sum, src[array_index(i+1,j+1,dim)]);
					
					accumulate_sum(&sum, src[array_index(i,j+1,dim)]);
					accumulate_sum(&sum, src[array_index(i,j+2,dim)]);
					
					accumulate_sum(&sum, src[array_index(i+1,j+1,dim)]);
					accumulate_sum(&sum, src[array_index(i+1,j+2,dim)]);
				
				}
				else if(j==dim-2)
				{
					accumulate_sum(&sum, src[array_index(i,j-1,dim)]);
					accumulate_sum(&sum, src[array_index(i,j,dim)]);
	
					accumulate_sum(&sum, src[array_index(i+1,j-1,dim)]);
					accumulate_sum(&sum, src[array_index(i+1,j,dim)]);

					accumulate_sum(&sum, src[array_index(i,j,dim)]);
					accumulate_sum(&sum, src[array_index(i,j+1,dim)]);
	
					accumulate_sum(&sum, src[array_index(i+1,j,dim)]);
					accumulate_sum(&sum, src[array_index(i+1,j+1,dim)]);
				}
				else
				{
					accumulate_sum(&sum, src[array_index(i,j-1,dim)]);
					accumulate_sum(&sum, src[array_index(i,j,dim)]);
					accumulate_sum(&sum, src[array_index(i,j+1,dim)]);
					
					accumulate_sum(&sum, src[array_index(i+1,j-1,dim)]);
					accumulate_sum(&sum, src[array_index(i+1,j,dim)]);
					accumulate_sum(&sum, src[array_index(i+1,j+1,dim)]);
					
					accumulate_sum(&sum, src[array_index(i,j,dim)]);
					accumulate_sum(&sum, src[array_index(i,j+1,dim)]);
					accumulate_sum(&sum, src[array_index(i,j+2,dim)]);
					
					accumulate_sum(&sum, src[array_index(i+1,j,dim)]);
					accumulate_sum(&sum, src[array_index(i+1,j+1,dim)]);
					accumulate_sum(&sum, src[array_index(i+1,j+2,dim)]);
				}
			}
			else if(i==dim-1)
			{	
				if(j==0)
				{
					
					accumulate_sum(&sum, src[array_index(i-1,j,dim)]);
					accumulate_sum(&sum, src[array_index(i-1,j+1,dim)]);
					
					accumulate_sum(&sum, src[array_index(i,j,dim)]);
					accumulate_sum(&sum, src[array_index(i,j+1,dim)]);
				
					accumulate_sum(&sum, src[array_index(i-1,j+1,dim)]);
					accumulate_sum(&sum, src[array_index(i-1,j+2,dim)]);
					
					accumulate_sum(&sum, src[array_index(i,j+1,dim)]);
					accumulate_sum(&sum, src[array_index(i,j+2,dim)]);
				}
				else if(j==dim-2)
				{
					accumulate_sum(&sum, src[array_index(i-1,j-1,dim)]);
					accumulate_sum(&sum, src[array_index(i-1,j,dim)]);
	
					accumulate_sum(&sum, src[array_index(i,j-1,dim)]);
					accumulate_sum(&sum, src[array_index(i,j,dim)]);

					accumulate_sum(&sum, src[array_index(i-1,j,dim)]);
					accumulate_sum(&sum, src[array_index(i-1,j+1,dim)]);
	
					accumulate_sum(&sum, src[array_index(i,j,dim)]);
					accumulate_sum(&sum, src[array_index(i,j+1,dim)]);
				}
				else
				{
					accumulate_sum(&sum, src[array_index(i-1,j-1,dim)]);
					accumulate_sum(&sum, src[array_index(i-1,j,dim)]);
					accumulate_sum(&sum, src[array_index(i-1,j+1,dim)]);
					
					accumulate_sum(&sum, src[array_index(i,j-1,dim)]);
					accumulate_sum(&sum, src[array_index(i,j,dim)]);
					accumulate_sum(&sum, src[array_index(i,j+1,dim)]);
					
					accumulate_sum(&sum, src[array_index(i-1,j,dim)]);
					accumulate_sum(&sum, src[array_index(i-1,j+1,dim)]);
					accumulate_sum(&sum, src[array_index(i-1,j+2,dim)]);
					
					accumulate_sum(&sum, src[array_index(i,j,dim)]);
					accumulate_sum(&sum, src[array_index(i,j+1,dim)]);
					accumulate_sum(&sum, src[array_index(i,j+2,dim)]);
				}
			}
			else
			{
				if(j==0)
				{
					accumulate_sum(&sum, src[array_index(i-1,j,dim)]);
					accumulate_sum(&sum, src[array_index(i-1,j+1,dim)]);
					
					accumulate_sum(&sum, src[array_index(i,j,dim)]);
					accumulate_sum(&sum, src[array_index(i,j+1,dim)]);
					
					accumulate_sum(&sum, src[array_index(i+1,j,dim)]);
					accumulate_sum(&sum, src[array_index(i+1,j+1,dim)]);
					
					accumulate_sum(&sum, src[array_index(i-1,j+1,dim)]);
					accumulate_sum(&sum, src[array_index(i-1,j+2,dim)]);
					
					accumulate_sum(&sum, src[array_index(i,j+1,dim)]);
					accumulate_sum(&sum, src[array_index(i,j+2,dim)]);
					
					accumulate_sum(&sum, src[array_index(i+1,j+1,dim)]);
					accumulate_sum(&sum, src[array_index(i+1,j+2,dim)]);
				}
				else if(j==dim-2)
				{
					accumulate_sum(&sum, src[array_index(i-1,j-1,dim)]);
					accumulate_sum(&sum, src[array_index(i-1,j,dim)]);
				
					accumulate_sum(&sum, src[array_index(i,j-1,dim)]);
					accumulate_sum(&sum, src[array_index(i,j,dim)]);
		
					accumulate_sum(&sum, src[array_index(i+1,j-1,dim)]);
					accumulate_sum(&sum, src[array_index(i+1,j,dim)]);

					accumulate_sum(&sum, src[array_index(i-1,j,dim)]);
					accumulate_sum(&sum, src[array_index(i-1,j+1,dim)]);
			
					accumulate_sum(&sum, src[array_index(i,j,dim)]);
					accumulate_sum(&sum, src[array_index(i,j+1,dim)]);
		
					accumulate_sum(&sum, src[array_index(i+1,j,dim)]);
					accumulate_sum(&sum, src[array_index(i+1,j+1,dim)]);
				}
				else
				{
					accumulate_sum(&sum, src[array_index(i-1,j-1,dim)]);
					accumulate_sum(&sum, src[array_index(i-1,j,dim)]);
					accumulate_sum(&sum, src[array_index(i-1,j+1,dim)]);
		
					accumulate_sum(&sum, src[array_index(i,j-1,dim)]);
					accumulate_sum(&sum, src[array_index(i,j,dim)]);
					accumulate_sum(&sum, src[array_index(i,j+1,dim)]);
					
					accumulate_sum(&sum, src[array_index(i+1,j-1,dim)]);
					accumulate_sum(&sum, src[array_index(i+1,j,dim)]);
					accumulate_sum(&sum, src[array_index(i+1,j+1,dim)]);
					
					accumulate_sum(&sum, src[array_index(i-1,j,dim)]);
					accumulate_sum(&sum, src[array_index(i-1,j+1,dim)]);
					accumulate_sum(&sum, src[array_index(i-1,j+2,dim)]);
		
					accumulate_sum(&sum, src[array_index(i,j,dim)]);
					accumulate_sum(&sum, src[array_index(i,j+1,dim)]);
					accumulate_sum(&sum, src[array_index(i,j+2,dim)]);
					
					accumulate_sum(&sum, src[array_index(i+1,j,dim)]);
					accumulate_sum(&sum, src[array_index(i+1,j+1,dim)]);
					accumulate_sum(&sum, src[array_index(i+1,j+2,dim)]);
				}
			}
		assign_sum_to_pixel(&current_pixel, sum);
			dst[array_index(i, j, dim)] = current_pixel;
			dst[array_index(i, j+1, dim)] = current_pixel;
		}
	}
}


/*********************************************************************
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_smooth_functions() {
	add_smooth_function(&smooth, smooth_descr);
	//add_smooth_function(&smoothA, smoothA_descr);
	//add_smooth_function(&smoothB, smoothB_descr);
	//add_smooth_function(&smooth2, smooth2_descr);
	//add_smooth_function(&smooth3, smooth3_descr);
	//add_smooth_function(&naive_smooth, naive_smooth_descr);
	/* ... Register additional test functions here */
}




