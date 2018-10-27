cd test
make
cd ../userprog/
make depend
make clean
gmake
echo
echo
echo "Program starts"
echo
echo
./nachos -x ../test/$1
