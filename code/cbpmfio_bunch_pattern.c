//
// cbpmfio_bunch_pattern.c
//

#include "cbpmfio.h"

// Simplified, single purpose. No va_arg junk.
int cbpmfio_bunch_patt_input( FILE *fp, char *format, int *address ) {

  char loc_format[CBPMFIO_MAX_FORMAT_LENGTH];
  char line[CBPMFIO_MAX_FILE_LINE_LENGTH];
  int  val = 0;
  char sub[50];
  char temp[CBPMFIO_MAX_FILE_LINE_LENGTH];
  int chr;
  int label_line;

  char labsep[5] = ": ";

  // Copy the format string for local use and replace
  // any string output format identifier with the appropriate
  // string collection format identifier.
  strcpy( loc_format, cbpmfio_replace_str(format, "%s", "%[^\n]\n") );

  long reg;

  while (fgets(line, CBPMFIO_MAX_FILE_LINE_LENGTH, fp) != NULL) {

    strcpy(temp, line);
    cbpmfio_strip(temp);
    if ( temp[0] == '#' || temp[0] == (int)NULL) {
      continue;
    }

    label_line = CBPMFIO_FALSE;

    // Determine if line contains a value label
    // and note postion where its identifier occurs.
    for ( chr = 0; chr < strlen(line); chr++) {
      if (line[chr] == ':') {
	label_line = CBPMFIO_TRUE;
	break;
      }
    }

    if (label_line) {
      if (strncmp(line, format, chr) == 0) {
	strcpy( sub, strtok( &(line[chr]), labsep) );
	val = (int)strtol( sub, NULL, 16);
	reg = 40-1;
	*(address+reg) = val;
	for (reg = 40-2; reg >= 0; reg--) {
	  strcpy( sub, strtok( NULL, labsep) );
	  val = (int)strtol( sub, NULL, 16);
	  *(address+reg) = val;
	}
	return CBPMFIO_SUCCESS;
      }
      
    }
    
  } //endWHILE
  
  return CBPMFIO_SUCCESS;

}





int cbpmfio_bunch_patt_output( FILE *fp, char *format, int *address ) {

  int reg;

  fprintf(fp, "%s", format);
  ////FIXME const! for (reg = CBI_MAX_16BIT_PATTERN_REGS-1; reg >= 0; reg--) {
  for (reg = 40-1; reg >= 0; reg--) {
    fprintf(fp, "%X ", *(address+reg));
  }
  fprintf(fp, "\n");

  return CBPMFIO_SUCCESS;
  
}
