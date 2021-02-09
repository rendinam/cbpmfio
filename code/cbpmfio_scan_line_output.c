//
// cbpmfio_scan_line_output.c
//

#include "cbpmfio.h"

int cbpmfio_scan_line_output( FILE *fp, char *format, ... ) {

  int retval;

  void  *p_val;
  int   *p_ival;
  float *p_fval;

  va_list ap;
  va_start(ap, format);


  char  fmt[CBPMFIO_MAX_FORMAT_LENGTH];
  char *token;
  strcpy(fmt, format);
  const char delimiters[] = "%";

  char fmt_token[CBPMFIO_MAX_FORMAT_TOKEN_LENGTH];

  int ch;

  // Determine if the item to print is a string.
  if (strstr(format, "%s") != 0) {

    retval = vfprintf(fp, format, ap);

  // If it's not a string, process it thusly.
  } else {

    ch = 0;
    while ( format[ch] != '\%' && format[ch] != (int)NULL) {
      fprintf(fp, "%c", format[ch]);
      ch++;
    }
    
    // No formatting flags found.  Reset string index.
    if (format[ch] == (int)NULL) {
      ch = 0;
      va_end(ap);
      return CBPMFIO_SUCCESS;
    }

    token = strtok( fmt+ch, delimiters );
    
    p_val = va_arg(ap, int*);
    while (p_val != (int)NULL && token != (int)NULL) {
      
      if ( strchr(token, 'd')) {
	p_ival = (int *)p_val;
	strcpy(fmt_token, "%");
	strcat(fmt_token, token);
	fprintf(fp, fmt_token, *p_ival);
      }
      if (strchr(token, 'f')) {
	p_fval = (float *)p_val;
	strcpy(fmt_token, "%");
	strcat(fmt_token, token);
	fprintf(fp, fmt_token, *p_fval);
      }
      if ( strchr(token, 'x')) {
	p_ival = (int *)p_val;
	strcpy(fmt_token, "%");
	strcat(fmt_token, token);
	fprintf(fp, fmt_token, *p_ival);
      }
      
      token = strtok(NULL, delimiters);
      p_val = va_arg(ap, int*);
      
    } //endWHILE
    
  } //endIF strstr
    
  va_end(ap);
  return CBPMFIO_SUCCESS;
}

