ODIR :=bin
LDIR :=lib
SDIR :=src

CC    :=g++
LIBS  :=-lconio


INCDIR = $(wildcard $(LDIR)/*)
CFLAGS = $(addprefix -I,$(INCDIR)) -Wall $(LIBS)
DEPS    := $(shell find ${INCDIR} src -type f -name '*.h')
SRCS    := $(shell find ${SDIR} -type f -name '*.c')
VENDORS := $(shell find ${LDIR} -type f -name '*.c')
BINS    := $(SRCS:${SDIR}/%.c=%.o) $(VENDORS:${LDIR}/%.c=%.o)

vpath %.c $(SDIR) $(LDIR)
vpath %.o $(ODIR)
vpath %.h $(INCDIR)

%.o: %.c $(DEPS)
	@echo "Compiling $< to ${ODIR}/$@..."
	@mkdir -p $(ODIR)/$(@D)
	@${CC} -c -o $(ODIR)/$@ $< $(CFLAGS)

game: $(BINS)
	@echo "Compiling $@..."
	@$(CC) -o $@ $(BINS:%.o=${ODIR}/%.o) $(CFLAGS) $(LIBS)

.PHONY: clean list

list:
	@echo INCDIR: ${INCDIR}
	@echo CFLAGS: ${CFLAGS}
	@echo DEPS: in $(INCDIR:%=%/) and src/
	@printf " $(DEPS:%=  %\n)"
	@echo SRC:
	@printf " $(SRCS:%=  %\n)"
	@echo VENDORS:
	@printf " $(VENDORS:%=  %\n)"
	@echo BINS:
	@printf " $(BINS:%=  %\n)"


clean:
	@echo "Cleaning binaries..."
	@rm -f $(ODIR)/*.o