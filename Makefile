# ==== TOOLS ====

CAS     = nasm
CXX     = g++

# ==== DIRECTORIES ====

SRCDIR  = src
BUILDDIR= build
ISODIR  = $(BUILDDIR)/isodir/boot

# ==== OUTPUT ====

KERNEL  = kern.bin
ISO     = kfs.iso

# ==== FLAGS ====

MAINFLAGS = -m32 \
            -ffreestanding \
            -fno-builtin \
            -fno-exceptions \
            -fno-stack-protector \
            -fno-rtti \
            -nostdlib \
            -nodefaultlibs

# ==== SOURCES ====

CPP_SRC = $(SRCDIR)/main.cpp
ASM_SRC = $(SRCDIR)/bootloader.nasm
LINKER  = $(SRCDIR)/linker.ld

# ==== OBJECTS ====

OBJS = $(BUILDDIR)/main.o \
       $(BUILDDIR)/bootloader.o

# ==== DEFAULT TARGET ====

all: $(BUILDDIR)/$(KERNEL) iso

# ==== RULES ====

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(BUILDDIR)
	$(CXX) $(MAINFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.nasm $(BUILDDIR)
	$(CAS) -f elf32 $< -o $@

$(BUILDDIR)/$(KERNEL): $(OBJS)
	ld -m elf_i386 -T $(LINKER) -o $@ $(OBJS)

# ==== ISO ====

iso: $(BUILDDIR)/$(KERNEL)
	mkdir -p $(ISODIR)/grub
	cp $< $(ISODIR)/$(KERNEL)
	echo 'menuentry "My Kernel" {' >  $(ISODIR)/grub/grub.cfg
	echo '    multiboot /boot/$(KERNEL)' >> $(ISODIR)/grub/grub.cfg
	echo '}' >> $(ISODIR)/grub/grub.cfg
	grub-mkrescue -o $(BUILDDIR)/$(ISO) $(BUILDDIR)/isodir
	echo "ISO created: $(BUILDDIR)/$(ISO)"

# ==== CLEAN ====

clean:
	rm -rf $(BUILDDIR)

.PHONY: all iso clean