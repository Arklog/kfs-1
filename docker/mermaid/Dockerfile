FROM minlag/mermaid-cli:latest

USER root
RUN apk add --no-cache bash
USER mermaidcli

ENV HOME=/usr/mermaidcli

COPY entrypoint.sh /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]
CMD ["/entrypoint.sh"]