LD = ld 
AS = as 
LFLAGS =


all:	exit_asm hello compare


exit_asm:	exit_asm.o
	$(LD) $(LDFLAGS) -o exit_asm exit_asm.o

exit_asm.o:	exit_asm.s
	$(AS) $(ASFLAGS) -o exit_asm.o exit_asm.s

hello:	hello.o
	$(LD) $(LDFLAGS) -o hello hello.o

hello.o:	hello.s
	$(AS) $(ASFLAGS) -o hello.o hello.s

compare:	compare.o
	$(LD) $(LDFLAGS) -o compare compare.o

compare.o:	compare.s
	$(AS) $(ASFLAGS) -o compare.o compare.s
