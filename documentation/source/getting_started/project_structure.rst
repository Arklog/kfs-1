.. _getting_started_project_structure:

#################
Project Structure
#################


Project Root Structure
======================

.. image:: project_structure.svg

#. Actions run by Github in order to run unit tests or deploy documentation
#. Folder containing our Dockerfiles and scripts
#. Documentation source folder
#. Project sources
    #. The kernel code source files
    #. Some header files, like *stdint.h*
    #. Libraries used by the kernel or drivers
    #. Kernel drivers like vga


Subproject Structure
====================

KFS is decoupled between libraries, drivers and core sources. Each of them if compiled as a standalone librarie before
being linked to the rest of the code. See below for the subproject structure.

.. image:: subproject_structure.svg

#. Library public headers (headers that will be accessible to linked libraries)
#. Library sources and private headers (headers that should stay hidden)
#. Library test suite