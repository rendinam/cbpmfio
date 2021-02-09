//
// fio_string_manip.c
//

#include "cbpmfio.h"

int cbpmfio_strip( char *string ) {

  int i;
  int len;
  int ws_count = 0;

  len = strlen( string );
  if ( string[len] != (int)NULL ) {
    printf("strip() : String argument is NOT null-terminated!\n");
    return 1;
  }


  // String type OK, Get rid of any whitespace at end.
  i = len;
  while( isspace(string[i-1]) ) {
    string[i] = (int)NULL;
    i--;
  }
  string[i] = (int)NULL;



  //---------------------
  i = 0;
  // Get rid of any whitespace at beginning.
  while( isspace(string[i]) != 0 ) {
    ws_count++;
    i++;
  }

  // If any head whitespace was found, bump everything 
  // down towards head of string memory block by amount 
  // determined from head whitespace examination.
  if (ws_count != 0) {
    i = 0;
    while( string[i+ws_count] != (int)NULL ) {
      string[i] = string[i + ws_count];
      i++;
    }
    // Move terminating NULL earlier the number of characters
    // found in the head whitespace count.  Should not move the
    // NULL at this point if no head whitespace was found.
    string[i] = (int)NULL;

  } // endIF head whitespace count

  return len;

}


char *cbpmfio_replace_str(char *st, char *orig, char *repl) {

  static char buffer[4096];
  char *ch;
  if (!(ch = strstr(st, orig)))
    return st;
  strncpy(buffer, st, ch-st);  
  buffer[ch-st] = 0;
  sprintf(buffer+(ch-st), "%s%s", repl, ch+strlen(orig));

  return buffer;

}
