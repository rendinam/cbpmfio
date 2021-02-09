/*
 cbpmfio_protos.h
*/

#ifndef CBPMFIO_PROTOS_H
#define CBPMFIO_PROTOS_H

#include <stdlib.h>
#include <stdarg.h>

int cbpmfio_rw_file_header(FILE *fp, int fio_mode);
int cbpmfio_rw_cesr_header(FILE *fp, int fio_mode);
int cbpmfio_rw_instrument_header(FILE *fp, int fio_mode);

/* fio_process_fields.c */
int   cbpmfio_file_subdir( int file_idx, char *subdir_string );
FILE *cbpmfio_open_raw_via_index( int file_idx );
int   cbpmfio_scan_line_input( FILE *fp, char *format, ... );
int   cbpmfio_scan_line_output( FILE *fp, char *format, ... );
void  cbpmfio_noop(int dummy, ...);
int   cbpmfio_bunch_patt_output( FILE *fp, char *format, int *address );
int   cbpmfio_bunch_patt_input( FILE *fp, char *format, int *address );
int   cbpmfio_rw_file_section(FILE *fp, int mode, int num_specs, CBPMFIO_FIELD_SPEC *specs);
int   cbpmfio_map_addresses_to_field(CBPMFIO_FIELD_SPEC *specs, int ID, fio_addrs addrs);

/* fio_string_manip */
int   cbpmfio_strip(char *string);
char *cbpmfio_replace_str(char *st, char *orig, char *repl);


int cbpmfio_deref_(int *address, int *array, int *size);
float cbpmfio_compute_pos(int plane, float coeffs[], float TI, float BI, float BO, float TO);

/* Memory management */
int cbpmfio_v3_inst_alloc(int iidx);
int cbpmfio_v3_free_inst_mem(int iidx);


/* API */
int cbpm_read_rawfile(int *file_idx);

int cbpm_rawfile_timestamp_(char *timestamp);

int cbpm_rawfile_num_instruments(void);
int cbpm_rawfile_num_bunches(void);
int cbpm_rawfile_num_turns(void);
int cbpm_rawfile_condx_number(void);
float cbpm_rawfile_cern_current(void);

int cbpm_rawfile_inst_names_(char *name);

int cbpm_rawfile_rf_bucket(int *bunch);
float cbpm_rawfile_pedestal(char *inst_location, int *bunch, int *button);
float cbpm_rawfile_gain_factor(char *inst_location, int *bunch, int *button);
int *cbpm_rawfile_raw_ptr(char *inst_location, int *button);
float *cbpm_rawfile_tbt_ptr(char *inst_location, int *button);
float *cbpm_rawfile_pos_ptr(char *inst_location, int *plane);
int *cbpm_rawfile_phase_ptr(char *inst_location, int *plane);


#endif
