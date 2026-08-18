FROM alpine:latest

RUN     apk add --no-cache uv python3 bash make doxygen
RUN     mkdir /build

COPY    entrypoint.sh /entrypoint.sh
RUN     chmod a+x /entrypoint.sh

CMD ["/entrypoint.sh"]
