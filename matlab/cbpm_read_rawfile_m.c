/*  
 * 
 * file: fio_read_rawfile_m.c
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
  int retval = 111;
  int mrows, ncols;
  int file_idx;

  // Check for proper number of arguments.
  if (nrhs != 1) {
    mexErrMsgTxt("Wrong number of INPUT arguments.  Expecting one (1).");
  }
    
  mrows = mxGetM(prhs[0]);
  ncols = mxGetN(prhs[0]);

  file_idx = (int) mxGetScalar(prhs[0]);

  // Call target library function.
  retval = cbpm_read_rawfile(&file_idx);
  if (retval == 1) {
    mexErrMsgTxt("Problem reading CBPM raw data file!");
  } 


  // Return value
  plhs[0] = mxCreateDoubleScalar(retval);

  return;

}
