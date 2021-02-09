/*  
 * 
 * file: cbpm_file_current_m.c
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
  float retval;

  // Check for proper number of arguments.
  if (nrhs > 0) {
    mexErrMsgTxt("Too many input arguments provided.  Expecting none.");
  }
    
  // Call target library function.
  retval = cbpm_rawfile_cern_current( );

  // Create return array/value
  plhs[0] = mxCreateDoubleScalar(retval);

  return;

}
