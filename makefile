#
# this makefile will compile and and all source
# found in the ~/develop/encodeInput directory.  
# 
# 
# =======================================================
#               
# =======================================================
# FINAL BINARY Target
./bin/encodeInput : ./obj/main.o ./obj/encryption.o ./obj/parse.o
	cc ./obj/main.o ./obj/encryption.o ./obj/parse.o -o ./bin/encodeInput
#
# =======================================================
#                     Dependencies
# =======================================================                     
./obj/main.o : ./src/main.c ./inc/encodeInput.h
	cc -c  ./src/main.c -o ./obj/main.o

./obj/encryption.o : ./src/encryption.c ./inc/encodeInput.h
	cc -c  ./src/encryption.c -o ./obj/encryption.o

./obj/parse.o : ./src/parse.c ./inc/encodeInput.h
	cc -c ./src/parse.c -o ./obj/parse.o	

#
# =======================================================
# Other Targets
# =======================================================                     
all : ./bin/encodeInput

clean :
	rm -f ./bin/*
	rm -f ./obj/*.o
	rm -f ./inc/*.h~
	rm -f ./src/*.c~
