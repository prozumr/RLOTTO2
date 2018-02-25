# compile instructions from: https://github.com/prozumr/RLOTTO2/issues/1
# gcc rlotto.c t_select.c t_add.c t_evaluate.c t_delete.c settings.c t_common.c -o rlotto.exe


CC      = gcc
CFLAGS  = -Wall
BIN     = rlotto.exe

OBJ = rlotto.o t_select.o t_add.o t_evaluate.o t_delete.o settings.o t_common.o

prog: $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ)

PHONY: clean
clean:
	rm -rf $(BIN) $(OBJ)


