KERNEL := kernel
ISO    := kfs.iso
BUILDDIR := build
ISODIR := $(BUILDDIR)/isodir/boot

CMAKE_BUILD_TYPE ?= Release
CMAKE := cmake
CMAKEFLAGS := -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE)

DOCKER_IMAGE := kfs-cross-gcc:1.0.0

.PHONY := iso test docker-build

kernel:
	${CMAKE} . -B${BUILDDIR} $(CMAKEFLAGS)
	${CMAKE} --build ${BUILDDIR} --target kernel --parallel

iso: kernel
	mkdir -p $(ISODIR)/grub
	cp $(BUILDDIR)/src/$(KERNEL) $(ISODIR)/$(KERNEL)
	echo 'set timeout=0' >  $(ISODIR)/grub/grub.cfg
	echo 'set default=0' >> $(ISODIR)/grub/grub.cfg
	echo 'menuentry "KFS-Cailloux" {' >>  $(ISODIR)/grub/grub.cfg
	echo '    multiboot /boot/$(KERNEL)' >> $(ISODIR)/grub/grub.cfg
	echo '}' >> $(ISODIR)/grub/grub.cfg
	grub-mkrescue -o $(BUILDDIR)/$(ISO) -d /usr/lib/grub/i386-pc $(BUILDDIR)/isodir
	@echo "ISO created: $(BUILDDIR)/$(ISO)"

run: docker-build
	qemu-system-i386 $(BUILDDIR)/$(ISO)

test: kernel
	${CMAKE} . -B${BUILDDIR} $(CMAKEFLAGS)
	${CMAKE} --build ${BUILDDIR} --parallel
	ctest --test-dir ${BUILDDIR} --output-on-failure

docker-build:
	docker build -t ${DOCKER_IMAGE} .
	docker run --rm -v $(shell pwd):/build -u $(shell id -u):$(shell id -g) ${DOCKER_IMAGE}