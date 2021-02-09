//
// cbpmfio_field_specs.h
//

#ifndef CBPMFIO_FIELD_SPECS_H
#define CBPMFIO_FIELD_SPECS_H


#ifndef CBPMFIO_NO_EXTERN

extern CBPMFIO_FIELD_SPEC RDV3_header_specs;
extern int num_RDV3_header_specs;

extern CBPMFIO_FIELD_SPEC RDV3_cesr_specs;
extern int num_RDV3_cesr_specs;

extern CBPMFIO_FIELD_SPEC RDV3_inst_header_specs;
extern int num_RDV3_inst_header_specs;

extern CBPMFIO_FIELD_SPEC RDV3_raw_data_label_specs;
extern int num_RDV3_raw_data_label_specs;

extern CBPMFIO_FIELD_SPEC RDV3_raw_data_spec;


extern RDV3_FILE_HEADER *p_v3_file_header;
extern RDV3_CESR_HEADER *p_v3_cesr_header;
extern RDV3_INST_DATA *p_v3_inst_array;

extern int inst_count_g;

extern int cbpmfio_memory_allocated;


#endif // (ifndef CBPMFIO_NO_EXTERN)


#endif // (ifndef FIO_FIELD_SPECS_H)
