KERNEL 					:= kernel#					Name of the iso to build
ISO    					:= kfs.iso#					Name of the iso to build
BUILDDIR 				:= build#					Non docker build directory (used to run tests on host)
DOCKERBUILDDIR 			:= build-docker#			# Docker build directory (where will docker build the iso)

CMAKE_BUILD_TYPE		?= Release					# CMake build type
CMAKE 					:= cmake					# CMake executable
CMAKEFLAGS 				:= -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE) -DTEST=33

DOCKER_MAKEFILE			:= docker/iso/Makefile
DOCKER_MAKE				:= make -f ${DOCKER_MAKEFILE} 				\
								KERNEL=${KERNEL} 				\
								ISO=${ISO} 						\
								BUILDDIR=${DOCKERBUILDDIR}		\
								CMAKEFLAGS="${CMAKEFLAGS}"

DOCKER_IMAGE_GCC 		:= kfs-cross-gcc:1.0.0		# Name of the cross gcc image
DOCKER_IMAGE_DOC		:= kfs-doc:1.0.0			# Name of the documentation image
DOCKER_IMAGE_MERMAID	:= mermaid:1.0.0

DOCKER_DOCKERFILE_GCC	:= docker/iso				# Docker cross gcc source directory
DOCKER_DOCKERFILE_DOC	:= docker/doc				# Docker documentation source directory
DOCKER_DOCKERFILE_MERMAID	:= docker/mermaid				# Docker documentation source directory

DOCKER_RUN			:= docker run -v $(shell pwd):/build --user $(shell id -u):$(shell id -g)

.PHONY 				:= all iso test docker-build

all: docker-build-iso docker-build-doc
	@echo "##############################################################"
	@echo "Iso constructed at ${DOCKERBUILDDIR}/${ISO}"
	@echo "Documentation available at documentation/build/html/index.html"

run: docker-build-iso
	echo "${DOCKERBUILDDIR}"
	echo "${ISO}"
	$(info ISO=[${ISO}])
	qemu-system-i386 $(DOCKERBUILDDIR)/$(ISO)

run-bonus: docker-build-iso
	qemu-system-i386 $(DOCKERBUILDDIR)/$(ISO_BONUS)

run-debug: docker-build-iso-debug
	qemu-system-i386 -kernel ${DOCKERBUILDDIR}/isodir/boot/${KERNEL} -S -s -no-reboot

test:
	${CMAKE} . -B${BUILDDIR} $(CMAKEFLAGS)
	${CMAKE} --build ${BUILDDIR} --parallel
	ctest --test-dir ${BUILDDIR} --output-on-failure

#####################
# Docker compilation
#####################

docker-build-iso: docker-image-build-gcc
	${DOCKER_RUN} ${DOCKER_IMAGE_GCC} ${DOCKER_MAKE} iso

docker-build-iso-debug: docker-image-build-gcc
	docker run --rm -v $(shell pwd):/build ${DOCKER_IMAGE_GCC} ${DOCKER_MAKE} iso

docker-build-doc: docker-image-build-doc docker-build-mermaid
	${DOCKER_RUN} ${DOCKER_IMAGE_DOC}

docker-build-mermaid: docker-image-build-mermaid
	${DOCKER_RUN} ${DOCKER_IMAGE_MERMAID}

######################
# Docker image build
######################

docker-image-build-all: docker-image-build-gcc docker-image-build-doc ;

docker-image-build-gcc:
	mkdir -p ~/.config/containers
	touch ~/.config/containers/nodocker
	docker build -t ${DOCKER_IMAGE_GCC} ${DOCKER_DOCKERFILE_GCC}

docker-image-build-doc:
	mkdir -p ~/.config/containers
	touch ~/.config/containers/nodocker
	docker build -t ${DOCKER_IMAGE_DOC} ${DOCKER_DOCKERFILE_DOC}

docker-image-build-mermaid:
	mkdir -p ~/.config/containers
	touch ~/.config/containers/nodocker
	docker build -t ${DOCKER_IMAGE_MERMAID} ${DOCKER_DOCKERFILE_MERMAID}

