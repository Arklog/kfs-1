KERNEL 				:= kernel
ISO    				:= kfs.iso
BUILDDIR 			:= build
DOCKERBUILDDIR 		:= build-docker
ISODIR 				:= $(BUILDDIR)/isodir/boot

CMAKE_BUILD_TYPE	?= Release
CMAKE 				:= cmake
CMAKEFLAGS 			:= -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE) -DTEST=33

DOCKER_MAKEFILE		:= Makefile.docker
DOCKER_MAKE			:= make -f ${DOCKER_MAKEFILE} 				\
								KERNEL=${KERNEL} 				\
								ISO=${ISO} 						\
								BUILDDIR=${DOCKERBUILDDIR}		\
								CMAKEFLAGS="${CMAKEFLAGS}"

DOCKER_IMAGE 		:= kfs-cross-gcc:1.0.0

DOCKER_RUN			:= docker run -v $(shell pwd):/build --user $(shell id -u):$(shell id -g)

.PHONY 				:= all iso test docker-build

all: docker-build ;

run: docker-build
	qemu-system-i386 $(DOCKERBUILDDIR)/$(ISO)

run-bonus: docker-build
	qemu-system-i386 $(DOCKERBUILDDIR)/$(ISO_BONUS)

run-debug: docker-build-debug
	qemu-system-i386 -kernel ${DOCKERBUILDDIR}/isodir/boot/${KERNEL} -S -s -no-reboot

test:
	${CMAKE} . -B${BUILDDIR} $(CMAKEFLAGS)
	${CMAKE} --build ${BUILDDIR} --parallel
	ctest --test-dir ${BUILDDIR} --output-on-failure

docker-build-image:
	mkdir -p ~/.config/containers
	touch ~/.config/containers/nodocker
	docker build -t ${DOCKER_IMAGE} .

docker-build: docker-build-image
	${DOCKER_RUN} ${DOCKER_IMAGE} ${DOCKER_MAKE} iso

docker-build-debug: docker-build-image
	docker run --rm -v $(shell pwd):/build ${DOCKER_IMAGE} ${DOCKER_MAKE} iso
