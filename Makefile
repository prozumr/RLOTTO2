# compile instructions from: https://github.com/prozumr/RLOTTO2/issues/1
# gcc rlotto.c t_select.c t_add.c t_evaluate.c t_delete.c settings.c t_common.c -o rlotto.exe

CC        = gcc
CFLAGS    = -Wall
BIN       = rlotto.exe
RLOTTOTEX = rlotto-manual.tex
LATEX     = lualatex
LATEXOPT  = --interaction=batchmode -shell-escape

HEADER    = rlotto.h  version.h
CFILES    = rlotto.c  settings.c  t_add.c  t_common.c  t_delete.c \
	        t_evaluate.c  t_select.c
PYTHON    = create_rlotto_tex_file.py
OBJ       = rlotto.o t_select.o t_add.o t_evaluate.o t_delete.o settings.o \
            t_common.o

all: $(OBJ)
	$(CC)  -DMYSTRING='"hello"' $(CFLAGS) -o $(BIN) $(OBJ)

.PHONY: manual
manual:
	cd manual; \
	./create_rlotto_tex_file.py \
		--header  "$(HEADER)"   \
		--csource "$(CFILES)"   \
		--python  "$(PYTHON)"   \
		> $(RLOTTOTEX);                \
	$(LATEX) $(LATEXOPT) $(RLOTTOTEX); \
	$(LATEX) $(LATEXOPT) $(RLOTTOTEX) 

	
.PHONY: clean
clean:
	rm -rf $(BIN) $(OBJ)
	cd manual && rm -rf *.aux *.log *.toc *.out manual/_minted*




