//
// cbpmfio_scan_line_input.c
//

#include "cbpmfio.h"

int cbpmfio_scan_line_input( FILE *fp, char *format, ... ) {

  char loc_format[CBPMFIO_MAX_FORMAT_LENGTH] = "";
  char line[CBPMFIO_MAX_FILE_LINE_LENGTH] = "";
  char temp[CBPMFIO_MAX_FILE_LINE_LENGTH] = "";
  int chr;
  int label_line;

  int retval;

  // If format string has one or more float specifiers in it, and if any
  // float specifier has a precision specification in it, strip out the precision
  // values before passing to vsscanf below as it prevents the float from being
  // correctly read (results in 0.0) in that function.
  int chidx = 0;
  int chidx2 = 0;

  strcpy(loc_format, format);

  while(format[chidx] != (char)NULL) {
    temp[chidx2] = loc_format[chidx];
    chidx2++;
    chidx++;
    if ( loc_format[chidx] == '%' ) {
      temp[chidx2] = loc_format[chidx];
      chidx2++;
      while (loc_format[chidx] != 's'  &&
	     loc_format[chidx] != 'd'  &&
	     loc_format[chidx] != 'x'  &&
	     loc_format[chidx] != 'f') {
	chidx++;
      }
      temp[chidx2] = loc_format[chidx];
    }
  }

  // Copy the temp format string for local use and replace
  // any string output format identifier with the appropriate
  // string input format identifier characters.
  strcpy( loc_format, cbpmfio_replace_str(temp, "%s", "%[^\n]\n") );

  va_list ap;
  va_start(ap, format);

  while (fgets(line, CBPMFIO_MAX_FILE_LINE_LENGTH, fp) != NULL) {

    //printf("                   %s", line);
    
    strcpy(temp, line);
    cbpmfio_strip(temp);
    if ( temp[0] == '#' || temp[0] == (int)NULL) {
      continue;
    }

    label_line = CBPMFIO_FALSE;

    // Check for beginning of data block.  If found, jump to next line and
    // start reading values.
    if (strncmp(line, CBPMFIO_DATA_BLOCK_START, strlen(CBPMFIO_DATA_BLOCK_START)) == 0) {
      //printf("DATA block start found!    line=[%s", line);
     break;
    }

    // Determine if line contains a value label and
    // note postion where its identifier occurs.
    for ( chr = 0; chr < strlen(line); chr++) {
      if (line[chr] == ':') {
	label_line = CBPMFIO_TRUE;
	break;
      }
    }

    if (label_line) {
      // If line label matches format label, grab the values.
      if (strncmp(line, format, chr) == 0) {
	retval = vsscanf(line, loc_format, ap);
	//printf("label match break --%s", format);
	break;
      }
    } else {
      // If line has no label, but holds some data, grab it all.
      //printf("   DATA line fallthrough...  format = \"%s\"   line=[%s", format, line);
      //printf("DATA line fallthrough... line=[%s", line);
      retval = vsscanf(line, format, ap);
      break;
    }
    

  }

  va_end(ap);
  return CBPMFIO_SUCCESS;
}
