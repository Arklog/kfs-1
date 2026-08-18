***********
Compilation
***********

Build System
------------

KFS need to be build using a cross compiler. In order to achieve this we use docker, so that the end user do not have
manually build one.

.. image:: build_system.svg


Compiling the kernel
--------------------

Due to the build system compiling is quite easy, you will need:

* GNU Make
* CMake
* A compiler of your choice
* Docker

All
"""

This will compile the kernel, an iso and the documentation

.. code-block:: bash

    make

ISO
"""

This will only build the iso

.. code-block:: bash

    make docker-build-iso

Tests
"""""

This will compile and run the tests

.. code-block:: bash

    make test