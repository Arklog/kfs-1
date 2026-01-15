FROM techiekeith/gcc-cross-i686-elf

RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install -y make cmake git g++

RUN mkdir /build
WORKDIR /build

CMD ["make", "iso"]