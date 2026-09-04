*************
Documentation
*************

This document describes the documentation for the project. It provides information about how to document the project, either for code documentation or this documentation itself. It also describes how to build the documentation and how to contribute to it.

Shinx
=====

This documentation is built using Sphinx, a documentation generator. 
It is written in `reStructuredText <https://www.sphinx-doc.org/en/master/usage/restructuredtext/basics.html>`_ and can be built into various formats, including HTML and PDF.

Building the documentation
--------------------------

.. code-block:: bash
    :caption: Build the documentation

    make docker-build-doc

The documentation will be available at :file:`documentation/build/html/index.html`


Mermaid
=======

Mermaid is a tool that allows to create diagrams and visualizations using text 
and code. It is used in this documentation to create diagrams and visualizations.

.. note::
    See `Mermaid <https://mermaid-js.github.io/mermaid/#/>`_ for more information about Mermaid.


Building charts
---------------

Mermaid charts presents in :file:`documentation/source` will be automatically built when building the documentation. 

You may alternatively call the following make target to build the charts only:

.. code-block:: bash
    :caption: Build the charts

    make docker-build-mermaid

.. note::

    By adding ``%% transparent`` in a mermaid file the diagram will be generated with a transparent background.
    This is not a native feature of Mermaid, but a *hack* implemented in the build process. See :file:`docker/mermaid/entrypoint.sh` for more information.

Code documentation
==================

The code must be documented using `Doxygen <https://www.doxygen.nl/index.html>`_.

See :ref:`getting_started_general_guidelines` for more information about code documentation.