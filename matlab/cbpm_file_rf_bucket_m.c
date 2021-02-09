/*  
 * 
 * file: cbpm_file_rf_bucket_m.c
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
  if (nrhs > 1) {
    mexErrMsgTxt("Incorrect number of arguments provided.  Expecting one (1).");
  }
    

  /* Second argument, bunch, must be a noncomplex scalar int32. */
  int bunch;
  mrows = mxGetM(prhs[1]);
  ncols = mxGetN(prhs[1]);
  if (mxIsComplex(prhs[1]) || !(mrows == 1 && ncols == 1)) {
    mexErrMsgTxt("Second argument must be a noncomplex scalar integer.");   /* returns to Matlab */
  }
  bunch = (int)mxGetScalar(prhs[1]);


  // Call target library function.
  retval = cbpm_rawfile_rf_bucket(&bunch);

  // Create return array/value
  plhs[0] = mxCreateDoubleScalar(retval);


  return;

}
