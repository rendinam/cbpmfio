/*  
 * 
 * file: cbpm_file_gain_factor_m.c
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
  int mrows, ncols;

  // Check for proper number of arguments.
  if (nrhs != 3) {
    mexErrMsgTxt("Wrong number of INPUT arguments.  Expecting three (3).");
  }
    

  /* First argument, inst_name, must be a char array. */
  char *inst_name;
  int buflen;
  int status;
  mrows = mxGetM(prhs[0]);
  ncols = mxGetN(prhs[0]);
  buflen = (mxGetM(prhs[0]) * mxGetN(prhs[0])) + 1;
  inst_name = (unsigned char *) mxCalloc(buflen, sizeof(char));
  status = (int) mxGetString(prhs[0], inst_name, buflen);
  if (status != 0) 
    mexWarnMsgTxt("Not enough space. String is truncated.");


  /* Second argument, bunch, must be a noncomplex scalar int32. */
  int bunch;
  mrows = mxGetM(prhs[1]);
  ncols = mxGetN(prhs[1]);
  if (mxIsComplex(prhs[1]) || !(mrows == 1 && ncols == 1)) {
    /* returns to Matlab */
    mexErrMsgTxt("Second argument must be a noncomplex scalar integer."); 
  }
  bunch = (int)mxGetScalar(prhs[1]);


  /* Third argument, button, must be a noncomplex scalar int32. */
  int button;
  mrows = mxGetM(prhs[2]);  
  ncols = mxGetN(prhs[2]);
  if (!(mrows == 1 && ncols == 1)) {
    /* returns to Matlab */
    mexErrMsgTxt("Third argument must be a noncomplex scalar integer."); 
  }
  button = (int)mxGetScalar(prhs[2]);


  // Call target library function.
  retval = cbpm_rawfile_gain_factor( inst_name, &bunch, &button );
  if (retval == CBPMFIO_FAILURE) {
    // Exit with error
    mexErrMsgTxt("Problem reading CBPM raw data file!");
  }


  // Create return array
  plhs[0] = mxCreateDoubleScalar(retval);


  return;

}
