#
# gccopts.sh	Shell script for configuring MEX-file creation script,
#               mex.  These options were tested with the specified compiler.
#
# usage:        Do not call this file directly; it is sourced by the
#               mex shell script.  Modify only if you don't like the
#               defaults after running mex.  No spaces are allowed
#               around the '=' in the variable assignment.
#
# Note: For the version of system compiler supported with this release,
#       refer to the Supported and Compatible Compiler List at:
#       http://www.mathworks.com/support/compilers/current_release/
#
#
# SELECTION_TAGs occur in template option files and are used by MATLAB
# tools, such as mex and mbuild, to determine the purpose of the contents
# of an option file. These tags are only interpreted when preceded by '#'
# and followed by ':'.
#
#SELECTION_TAG_MEX_OPT: Template Options file for building gcc MEX-files
#
# Copyright 1984-2008 The MathWorks, Inc.
# $Revision: 1.43.4.15 $  $Date: 2008/11/04 19:40:06 $
#----------------------------------------------------------------------------
#
    TMW_ROOT="$MATLAB"
    MFLAGS=''
    if [ "$ENTRYPOINT" = "mexLibrary" ]; then
        MLIBS="-L$TMW_ROOT/bin/$Arch -lmx -lmex -lmat -lmwservices -lut"
    else  
        MLIBS="-L$TMW_ROOT/bin/$Arch -lmx -lmex -lmat"
    fi
    case "$Arch" in
        Undetermined)
#----------------------------------------------------------------------------
# Change this line if you need to specify the location of the MATLAB
# root directory.  The script needs to know where to find utility
# routines so that it can determine the architecture; therefore, this
# assignment needs to be done while the architecture is still
# undetermined.
#----------------------------------------------------------------------------
            MATLAB="$MATLAB"
#
# Determine the location of the GCC libraries
#
	    #GCC_LIBDIR=`gcc -v 2>&1 | awk '/.*Reading specs.*/ {print substr($4,0,length($4)-6)}'`
            ;;
        glnx86)
#----------------------------------------------------------------------------
            RPATH="-Wl,-rpath-link,$TMW_ROOT/bin/$Arch"
            CC='gcc'
            CFLAGS='-std=c99 -D_GNU_SOURCE -fexceptions'
            CFLAGS="$CFLAGS -fPIC -pthread -m32"
            CFLAGS="$CFLAGS -D_FILE_OFFSET_BITS=64" 
            CLIBS="$RPATH $MLIBS -lm -lstdc++"
            COPTIMFLAGS='-O -DNDEBUG'
            CDEBUGFLAGS='-g'
#           
            CXX='g++'
            CXXFLAGS='-std=c99 -D_GNU_SOURCE'
            CXXFLAGS="$CXXFLAGS -D_FILE_OFFSET_BITS=64" 
            CXXFLAGS="$CXXFLAGS -fPIC -pthread"
            CXXLIBS="$RPATH $MLIBS -lm"
            CXXOPTIMFLAGS='-O -DNDEBUG'
            CXXDEBUGFLAGS='-g'
#
#
            FC='g95'
            FFLAGS='-fexceptions'
            FFLAGS="$FFLAGS -fPIC"
            FLIBS="$RPATH $MLIBS -lm"
            FOPTIMFLAGS='-O'
            FDEBUGFLAGS='-g'
#
            LD="$COMPILER"
            LDEXTENSION='.mexglx'
            LDFLAGS="-pthread -shared -m32 -Wl,--version-script,$TMW_ROOT/extern/lib/$Arch/$MAPFILE -Wl,--no-undefined"
            LDOPTIMFLAGS='-O'
            LDDEBUGFLAGS='-g'
#
            POSTLINK_CMDS=':'

#----------------------------------------------------------------------------
            ;;
        glnxa64)
#----------------------------------------------------------------------------
            RPATH="-Wl,-rpath-link,$TMW_ROOT/bin/$Arch"
            # StorageVersion: 1.0
            # CkeyName: GNU C
            # CkeyManufacturer: GNU
            # CkeyLanguage: C
            # CkeyVersion:
            CC='gcc'
            CFLAGS='-std=c99 -D_GNU_SOURCE'
            CFLAGS="$CFLAGS  -fexceptions"
            CFLAGS="$CFLAGS -fPIC -fno-omit-frame-pointer -pthread"
            CLIBS="$RPATH $MLIBS -lm"
            COPTIMFLAGS='-O -DNDEBUG'
            CDEBUGFLAGS='-g'
            CLIBS="$CLIBS -lstdc++"
#
            # C++keyName: GNU C++
            # C++keyManufacturer: GNU
            # C++keyLanguage: C++
            # C++keyVersion: 
            CXX='g++'
            CXXFLAGS='-D_GNU_SOURCE'
            CXXFLAGS="$CXXFLAGS -fPIC -fno-omit-frame-pointer -pthread"
            CXXLIBS="$RPATH $MLIBS -lm"
            CXXOPTIMFLAGS='-O -DNDEBUG'
            CXXDEBUGFLAGS='-g'
#
            # FortrankeyName: g95
            # FortrankeyManufacturer: GNU
            # FortrankeyLanguage: Fortran
            # FortrankeyVersion: 
#
            FC='g95'
            FFLAGS='-fexceptions'
            FFLAGS="$FFLAGS -fPIC -fno-omit-frame-pointer"
            FLIBS="$RPATH $MLIBS -lm"
            FOPTIMFLAGS='-O'
            FDEBUGFLAGS='-g'
#
            LD="$COMPILER"
            LDEXTENSION='.mexa64'
            LDFLAGS="-pthread -shared -Wl,--version-script,$TMW_ROOT/extern/lib/$Arch/$MAPFILE -Wl,--no-undefined"
            LDOPTIMFLAGS='-O'
            LDDEBUGFLAGS='-g'
#
            POSTLINK_CMDS=':'

            ;;
    esac