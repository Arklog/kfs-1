erDiagram:
    Host ||..o{ Docker: run
    Host ||..o{ Tests: compile
    Docker ||..o{ Kernel: compile
    Docker ||..o{ Documentation: compile