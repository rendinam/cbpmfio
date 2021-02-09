/*  
 * 
 * file: cbpm_file_condx_m.c
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
  int mrows, ncols;

  // Check for proper number of arguments.
  if (nrhs > 0) {
    mexErrMsgTxt("Too many input arguments provided.  Expecting none.");
  }
    
  // Call target library function.
  retval = cbpm_rawfile_condx_number( );

  // Create return array/value
  plhs[0] = mxCreateDoubleScalar(retval);

  return;

}
