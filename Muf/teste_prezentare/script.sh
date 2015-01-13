#!/bin/bash

# COADA="nehalem"
# COADA="opteron"
COADA="quad"
# SCRIPT_NAME="BHserial_nehalem.sh"
# SCRIPT_NAME="BHserial_opteron.sh"
SCRIPT_NAME="BHserial_quad.sh"
touch $SCRIPT_NAME

chmod 777 $SCRIPT_NAME
echo "#!/bin/bash" > $SCRIPT_NAME
echo "SERIAL_OUTPUT_H=\"../../../build/boyer_horspool\"" >> $SCRIPT_NAME
echo "./\$SERIAL_OUTPUT_H ../../../inputs/test1 >> "$COADA"/serial"  >> $SCRIPT_NAME
echo "./\$SERIAL_OUTPUT_H ../../../inputs/test2 >> "$COADA"/serial"  >> $SCRIPT_NAME
echo "./\$SERIAL_OUTPUT_H ../../../inputs/test3 >> "$COADA"/serial"  >> $SCRIPT_NAME
echo "./\$SERIAL_OUTPUT_H ../../../inputs/test4 >> "$COADA"/serial"  >> $SCRIPT_NAME

cp $SCRIPT_NAME slide2/slide2/

chmod 777 slide2/slide2/$SCRIPT_NAME

# COADA="opteron"
# SCRIPT_NAME="pthreads_opteron.sh"
# FOLDER="1GB"
# TEST="test3"
# touch $SCRIPT_NAME

# chmod 777 $SCRIPT_NAME
# echo "#!/bin/bash" > $SCRIPT_NAME
# echo "OMP_OUTPUT_H=\"../../../build/boyer_horspool_pthreads\"" >> $SCRIPT_NAME
# echo "./\$OMP_OUTPUT_H 1  ../../../inputs/"$TEST" >> "$COADA"/pthreads"  >> $SCRIPT_NAME
# echo "./\$OMP_OUTPUT_H 2  ../../../inputs/"$TEST" >> "$COADA"/pthreads"  >> $SCRIPT_NAME
# echo "./\$OMP_OUTPUT_H 4  ../../../inputs/"$TEST" >> "$COADA"/pthreads"  >> $SCRIPT_NAME
# echo "./\$OMP_OUTPUT_H 6  ../../../inputs/"$TEST" >> "$COADA"/pthreads"  >> $SCRIPT_NAME
# echo "./\$OMP_OUTPUT_H 8  ../../../inputs/"$TEST" >> "$COADA"/pthreads"  >> $SCRIPT_NAME
# echo "./\$OMP_OUTPUT_H 16 ../../../inputs/"$TEST" >> "$COADA"/pthreads"  >> $SCRIPT_NAME

# cp $SCRIPT_NAME slide3/$FOLDER/
# cp $SCRIPT_NAME slide4/$FOLDER/
# cp $SCRIPT_NAME slide5/$FOLDER/

# chmod 777 slide3/$FOLDER/$SCRIPT_NAME
# chmod 777 slide4/$FOLDER/$SCRIPT_NAME
# chmod 777 slide5/$FOLDER/$SCRIPT_NAME


# COADA="nehalem"
# SCRIPT_NAME="mpi_nehalem.sh"
# FOLDER="1GB"
# touch $SCRIPT_NAME

# chmod 777 $SCRIPT_NAME
# echo "#!/bin/bash" > $SCRIPT_NAME
# echo "MPI_OUTPUT_H=\"../../../build/boyer_horspool_mpi\"" >> $SCRIPT_NAME
# echo "mpirun -np 1  ./\$MPI_OUTPUT_H ../../../inputs/test3 >> "$COADA"/mpi"  >> $SCRIPT_NAME
# echo "mpirun -np 2  ./\$MPI_OUTPUT_H ../../../inputs/test3 >> "$COADA"/mpi"  >> $SCRIPT_NAME
# echo "mpirun -np 4  ./\$MPI_OUTPUT_H ../../../inputs/test3 >> "$COADA"/mpi"  >> $SCRIPT_NAME
# echo "mpirun -np 6  ./\$MPI_OUTPUT_H ../../../inputs/test3 >> "$COADA"/mpi"  >> $SCRIPT_NAME
# echo "mpirun -np 8  ./\$MPI_OUTPUT_H ../../../inputs/test3 >> "$COADA"/mpi"  >> $SCRIPT_NAME
# echo "mpirun -np 16 ./\$MPI_OUTPUT_H ../../../inputs/test3 >> "$COADA"/mpi"  >> $SCRIPT_NAME

# cp $SCRIPT_NAME slide3/$FOLDER/
# cp $SCRIPT_NAME slide4/$FOLDER/
# cp $SCRIPT_NAME slide5/$FOLDER/

# chmod 777 slide3/$FOLDER/$SCRIPT_NAME
# chmod 777 slide4/$FOLDER/$SCRIPT_NAME
# chmod 777 slide5/$FOLDER/$SCRIPT_NAME
