CMAKE				:= cmake
ISODIR 				:= $(BUILDDIR)/isodir/boot

kernel: check-env
	${CMAKE} . -B${BUILDDIR} $(CMAKEFLAGS)
	${CMAKE} --build ${BUILDDIR} --target $(KERNEL) --parallel

iso: kernel
	mkdir -p $(ISODIR)/grub
	cp $(BUILDDIR)/src/$(KERNEL) $(ISODIR)/$(KERNEL)
	echo 'set timeout=0' >  $(ISODIR)/grub/grub.cfg
	echo 'set default=0' >> $(ISODIR)/grub/grub.cfg
	echo 'menuentry "KFS-Cailloux" {' >>  $(ISODIR)/grub/grub.cfg
	echo '    multiboot /boot/$(KERNEL)' >> $(ISODIR)/grub/grub.cfg
	echo '}' >> $(ISODIR)/grub/grub.cfg
	grub-mkrescue -o $(BUILDDIR)/$(ISO) --compress=xz -d /usr/lib/grub/i386-pc $(BUILDDIR)/isodir
	@echo "ISO created: $(BUILDDIR)/$(ISO)"

check-env:
	test -n "${BUILDDIR}"
	test -n "${ISODIR}"
	test -n "${ISO}"
	test -n "${KERNEL}"
	test -n "${CMAKEFLAGS}"
	test -n "${CMAKE}"