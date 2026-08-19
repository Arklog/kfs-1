KERNEL 				:= kernel
KERNEL_BONUS		:= kernel_bonus
ISO    				:= kfs.iso
ISO_BONUS  			:= kfs_bonus.iso
BUILDDIR 			:= build
DOCKERBUILDDIR 		:= build-docker
ISODIR 				:= $(BUILDDIR)/isodir/boot

CMAKE_BUILD_TYPE	?= Release
CMAKE 				:= cmake
CMAKEFLAGS 			:= -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE)

DOCKER_IMAGE 		:= kfs-cross-gcc:1.0.0

.PHONY 				:= all iso test docker-build

all: docker-build ;

kernel:
	${CMAKE} . -B${BUILDDIR} $(CMAKEFLAGS)
	${CMAKE} --build ${BUILDDIR} --target $(KERNEL) --parallel
	${CMAKE} --build ${BUILDDIR} --target $(KERNEL_BONUS) --parallel

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
	cp $(BUILDDIR)/src/$(KERNEL_BONUS) $(ISODIR)/$(KERNEL_BONUS)
	echo 'set timeout=0' >  $(ISODIR)/grub/grub.cfg
	echo 'set default=0' >> $(ISODIR)/grub/grub.cfg
	echo 'menuentry "KFS-Cailloux" {' >>  $(ISODIR)/grub/grub.cfg
	echo '    multiboot /boot/$(KERNEL_BONUS)' >> $(ISODIR)/grub/grub.cfg
	echo '}' >> $(ISODIR)/grub/grub.cfg
	grub-mkrescue -o $(BUILDDIR)/$(ISO_BONUS) --compress=xz -d /usr/lib/grub/i386-pc $(BUILDDIR)/isodir
	@echo "ISO created: $(BUILDDIR)/$(ISO_BONUS)"

run: docker-build
	qemu-system-i386 $(DOCKERBUILDDIR)/$(ISO)

run-bonus: docker-build
	qemu-system-i386 $(DOCKERBUILDDIR)/$(ISO_BONUS)

run-debug: docker-build-debug
	qemu-system-i386 -kernel ${DOCKERBUILDDIR}/isodir/boot/${KERNEL} -S -s -no-reboot

test: kernel
	${CMAKE} . -B${BUILDDIR} $(CMAKEFLAGS)
	${CMAKE} --build ${BUILDDIR} --parallel
	ctest --test-dir ${BUILDDIR} --output-on-failure

docker-build-image:
	mkdir -p ~/.config/containers
	touch ~/.config/containers/nodocker
	docker build -t ${DOCKER_IMAGE} .

docker-build: docker-build-image
	docker run --rm -v $(shell pwd):/build:Z ${DOCKER_IMAGE} make BUILDDIR=${DOCKERBUILDDIR} iso

docker-build-debug: docker-build-image
	docker run --rm -v $(shell pwd):/build:Z ${DOCKER_IMAGE} make CMAKE_BUILD_TYPE=Debug BUILDDIR=${DOCKERBUILDDIR} iso
