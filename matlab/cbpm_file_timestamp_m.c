/*  
 * 
 * file: cbpm_file_timestamp_m.c
 * 
 * description:  MATLAB mex gateway function
 *
 */
#include "mex.h"
#include "cbpmfio.h"

void mexFunction(
		 int nlhs, mxArray * plhs[], int nrhs,
		 const mxArray * prhs[]) 
{
  int retval = -1;

  // Check for proper number of arguments.
  if (nrhs > 0) {
    mexErrMsgTxt("Too many input arguments provided.  Expecting none.");
  }
    

  char timestamp[50];
  // Call target library function.
  retval = cbpm_rawfile_timestamp_( timestamp );

  // Create return array/value
  plhs[0] = mxCreateString( timestamp );

  return;

}
