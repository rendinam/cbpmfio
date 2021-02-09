function [] =  cbpmFileInputDemoExtended( )

    addpath([getenv('ACC_RELEASE_DIR') '/cbpmfio/matlab']); load_CBPM_input();

    TEST_FILE_IDX  =   4080;

    file_idx = TEST_FILE_IDX;

  fprintf('\nAttempting to open RAW DATA file %d from central CESR datafile location...\n', file_idx);

  status = cbpm_read_rawfile_m( file_idx );
  if (status ~= 0) 
    fprintf( 'Error opening file for reading... exiting.\n');
    return
  end
  
  button  = 0;
  button0 = 0;
  button1 = 1;
  button2 = 2;
  button3 = 3;

  fprintf('Testing cbpm_file_timestamp_:\n');
  timestamp2 = cbpm_file_timestamp_m(  );
  fprintf('  timestamp = %s\n', timestamp2 );


  num_instruments = cbpm_file_num_insts_m();
  fprintf('Testing cbpm_file_num_instruments_:\n');
  fprintf('  num_instruments = %d\n', num_instruments );

  
  fprintf('Testing cbpm_file_num_bunches_:\n');
  fprintf('  num_bunches     = %d\n', cbpm_file_num_bunches_m() );


  fprintf('Testing cbpm_file_num_turns_:\n');
  fprintf('  num_turns       = %d\n', cbpm_file_num_turns_m() );


  fprintf('Testing cbpm_file_condx_number_:\n');
  fprintf('  CONDX number    = %d\n', cbpm_file_condx_m() );
  
  names{1} = '';
  namecount = 1;
  name = cbpm_file_inst_locs_m(  );
  while ( strcmp(name, '') == 0 ) 
    names{namecount} = name ;
    namecount = namecount + 1;
    name = cbpm_file_inst_locs_m(  )
  end

  for count = 1:num_instruments

    location = names{count} ;
    fprintf('\n\nLocation = %s\n', location);

    button0 = 0;
    bunch = 0;
    fprintf('PED: %f   %f   %f   %f\n', ...
	   cbpm_file_pedestal_m(location, bunch, button0), ...
	   cbpm_file_pedestal_m(location, bunch, button1), ...
	   cbpm_file_pedestal_m(location, bunch, button2), ...
	   cbpm_file_pedestal_m(location, bunch, button3) ...
	   );
   
    fprintf('Gain factor: %f   %f   %f   %f\n', ...
	   cbpm_file_gain_factor_m(location, bunch, button0), ...
	   cbpm_file_gain_factor_m(location, bunch, button1), ...
	   cbpm_file_gain_factor_m(location, bunch, button2), ...
	   cbpm_file_gain_factor_m(location, bunch, button3) ...
	   );   

    idata = cbpm_file_raw_data_m( location  );
    fprintf('raw : %d %d %d %d \n', idata);

    fdata = cbpm_file_tbt_data_m( location);
    fprintf('TBT: %f %f %f %f \n', fdata );

    pos = cbpm_file_pos_data_m( location);%, dim, fdata );
    fprintf('X pos:  %f, Y pos:  %f\n', pos );

    phase = cbpm_file_shaker_phase_m( location);%, dim, idata );
    fprintf('Phase word: %x %x\n', phase );

  end
  
  file_idx = 4079;
  fprintf('\nAttempting to open RAW DATA file %d from central CESR datafile location...\n', file_idx);

  status = cbpm_read_rawfile_m( file_idx );
  if (status ~= 0) 
    printf( 'Error opening file for reading... exiting.\n');
    return;
  end
  
  fprintf('Demo complete.');
  
end
