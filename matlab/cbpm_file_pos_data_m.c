/*  
 * 
 * file: cbpm_file_pos_data_m.c
 * 
 * description:  MATLAB mex gateway function
 *
 */
#include "mex.h"    
#include "cbpmfio.h"

#define OUTPUT_COLUMNS   2

    
void mexFunction(
		 int nlhs, mxArray * plhs[], int nrhs,
		 const mxArray * prhs[]) 
{
  int retval = -1;
  int mrows, ncols;
  int file_idx;

  // Check for proper number of arguments.
  if (nrhs != 1) {
    mexErrMsgTxt("Incorrect number of arguments provided.  Expecting one (1).");
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


  // Call target library function.
  float *ptr;
  float value[1];
  float *data;

  mxClassID  dataClass;
  dataClass = mxSINGLE_CLASS;
  int num_turns = cbpm_rawfile_num_turns();
  int num_bunches = cbpm_rawfile_num_bunches();
  int num_values = num_turns * num_bunches;
  int dimensions[2];
  dimensions[0] = num_values; 
  dimensions[1] = OUTPUT_COLUMNS;
  plhs[0] = mxCreateNumericArray(2, dimensions, dataClass, mxREAL);
  data = (float*)mxGetData(plhs[0]);

  float *output;
  output = mxGetData(plhs[0]);
    
  int val;
  int plane = 0;

  for (plane = 0; plane < OUTPUT_COLUMNS; plane++) {
    ptr = cbpm_rawfile_pos_ptr(inst_name, &plane);
    value[0] = *ptr;
    for (val = 0; val < num_values; val++) {
      data = output++;
      value[0] = *(ptr+val);
      memcpy(data, value, 4);
    }
  }

  return;

}

