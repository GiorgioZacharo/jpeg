SRCS=chenidct.c  decode.c  huffman.c  init.c  jfif_read.c  jpeg2bmp.c  marker.c  testbench.c

ACCEL_NAME = ChenIDct_f2r_vectorBody_s2e_forEnd212
TEST_BIN = $(ACCEL_NAME)
export TRACE_OUTPUT_DIR=$(ACCEL_NAME)
ifndef WORKLOAD
  export WORKLOAD=ChenIDct_f2r_vectorBody_s2e_forEnd212
endif
include ../common/Makefile.common
include ../common/Makefile.tracer

#OBJ = main.o chenidct.o  decode.o  huffman.o  init.o  jfif_read.o  jpeg2bmp.o  marker.o
#TARGET = jpeg

#%.o: $(SRCDIR)/%.c $(SRCDIR)/$(DEPS)
#        $(CC) -c -o $@ $< $(CFLAGS)

#all: $(OBJ)
#        $(CC) -o $(TARGET) $^ $(CFLAGS)
