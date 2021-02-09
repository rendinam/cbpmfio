/*  
 * 
 * file: cbpm_file_inst_locs_m.c
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
    

  int num_insts = cbpm_rawfile_num_instruments();

  char name[50];
  int namecount = 0;
  char names[95][20];
  // Repeatedly call target library function to load
  // 2D arary of instrument names for use within MATLAB.
  retval = cbpm_rawfile_inst_names_( name );

  /*
  strcpy( names[namecount], name );
  namecount++;
  while ( strcmp(name, "") != 0 ) {
    cbpm_rawfile_inst_names_( name );
    strcpy( names[namecount], name );
    namecount++;
  }
  */
  
/*   char *output; */
  plhs[0] = mxCreateString( name );
/*   output = mxGetPr(plhs[0]); */
/*   int idx = 0; */
/*   while (name[idx] != NULL) { */
/*     *(output+(idx*2)) = name[idx]; */
/*     idx++; */
/*   } */

  return;

}
