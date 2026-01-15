FROM debian:stable-slim
LABEL authors="pierre"

ARG TOOLCHAIN_DIR="/toolchain"
ARG BUILD_DIR="/build"

ARG GMP_URL="https://ftp.gnu.org/gnu/gmp/gmp-6.3.0.tar.xz"
ARG GMP_ARCHIVE="gmp-6.3.0.tar.xz"
ARG GMP_DIR="gmp-6.3.0"
ARG MPC_URL="https://ftp.gnu.org/gnu/mpc/mpc-1.3.1.tar.gz"
ARG MPC_ARCHIVE="mpc-1.3.1.tar.gz"
ARG MPC_DIR="mpc-1.3.1"
ARG MPFR_URL="https://ftp.gnu.org/gnu/mpfr/mpfr-4.2.2.tar.xz"
ARG MPFR_ARCHIVE="mpfr-4.2.2.tar.xz"
ARG MPFR_DIR="mpfr-4.2.2"
ARG GCC_URL="https://ftp.gnu.org/gnu/gcc/gcc-15.2.0/gcc-15.2.0.tar.xz"
ARG GCC_ARCHIVE="gcc-15.2.0.tar.xz"
ARG GCC_DIR="gcc-15.2.0"

RUN apt update
RUN apt install -y cmake \
                        make \
                        wget \
                        g++ \
                        gcc \
                        bison \
                        flex \
                        texinfo \
                        libisl-dev \
                        file \
                        xz-utils
RUN rm -rf /var/lib/apt/lists/*

RUN mkdir -p ${BUILD_DIR}
RUN wget ${GCC_URL} -O ${BUILD_DIR}/${GCC_ARCHIVE}
RUN wget ${GMP_URL} -O ${BUILD_DIR}/${GMP_ARCHIVE}
RUN wget ${MPFR_URL} -O ${BUILD_DIR}/${MPFR_ARCHIVE}
RUN wget ${MPC_URL} -O ${BUILD_DIR}/${MPC_ARCHIVE}

WORKDIR ${BUILD_DIR}
RUN tar xf ${GCC_ARCHIVE}
RUN tar xf ${GMP_ARCHIVE} && mv ${GMP_DIR} ${GCC_DIR}/gmp
RUN tar xf ${MPFR_ARCHIVE} && mv ${MPFR_DIR} ${GCC_DIR}/mpfr
RUN tar xf ${MPC_ARCHIVE} && mv ${MPC_DIR} ${GCC_DIR}/mpc

WORKDIR ${BUILD_DIR}/${GCC_DIR}
RUN mkdir build
WORKDIR build
RUN ../configure --target=i686-elf                              \
                     --prefix=${TOOLCHAIN_DIR}                      \
                     --disable-nls \
                     --enable-languages=c,c++ \
                     --without-headers \
                     --disable-hosted-libstdcxx
RUN make -j$(nproc) all-gcc
RUN make -j$(nproc) install-gcc
ENV PATH="${TOOLCHAIN_DIR}/bin:${PATH}"
RUN make -j$(nproc) all-target-libgcc
#RUN make -j$(nproc) install-target-libgcc
##RUN make -j$(nproc) all-target-libstdc++-v3
#RUN make -j$(nproc) install-target-libstdc++-v3
#ENTRYPOINT ["top", "-b"]

