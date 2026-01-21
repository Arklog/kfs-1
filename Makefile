KERNEL := kern.bin
ISO    := kfs.iso
BUILDDIR := build
ISODIR := $(BUILDDIR)/isodir/boot

CMAKE_BUILD_TYPE ?= Debug
CMAKE := cmake
CMAKEFLAGS := -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE)

.PHONY := test

link_kernel: kernel bootloader
	ld -T src/linker.ld -o ${KERNEL} -m elf_i386 -Lbuild/src src/bootloader.o -lkernel

kernel:
	${CMAKE} . -B${BUILDDIR} $(CMAKEFLAGS)
	${CMAKE} --build ${BUILDDIR} --target kernel --parallel

bootloader:
	nasm -f elf32 src/bootloader.s -o src/bootloader.o

iso: link_kernel
	mkdir -p $(ISODIR)/grub
	cp $(KERNEL) $(ISODIR)/$(KERNEL)
	echo 'set timeout=0' >  $(ISODIR)/grub/grub.cfg
	echo 'set default=0' >> $(ISODIR)/grub/grub.cfg
	echo 'menuentry "KFS-Cailloux" {' >>  $(ISODIR)/grub/grub.cfg
	echo '    multiboot /boot/$(KERNEL)' >> $(ISODIR)/grub/grub.cfg
	echo '}' >> $(ISODIR)/grub/grub.cfg
	grub-mkrescue -o $(BUILDDIR)/$(ISO) $(BUILDDIR)/isodir
	echo "ISO created: $(BUILDDIR)/$(ISO)"

run: iso
	qemu-system-i386 $(BUILDDIR)/$(ISO)

test: kernel
	${CMAKE} . -B${BUILDDIR} $(CMAKEFLAGS)
	${CMAKE} --build ${BUILDDIR} --parallel
	ctest --test-dir ${BUILDDIR} --output-on-failure

doc:
	doxygen Doxyfile