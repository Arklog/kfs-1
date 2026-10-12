.. _gdt:

Global Descriptor Table (GDT)
===============
 
The Global Descriptor Table (GDT) is a data
structures used to implement memory segmentation and
privilege-level isolation. Before any protected-mode code can safely
execute, the CPU must be given a valid GDT to consult. Without it, the
processor has no way to know which memory regions exist, who is allowed
to access them, or at what privilege level.

Privilege Levels
----------------

The x86 architecture defines four privilege levels, or **rings**, from
ring 0 (most privileged) to ring 3 (least privileged). Modern operating
systems generally use ring 0 for the kernel and ring 3 for applications,
while rings 1 and 2 are rarely used.

The DPL of a descriptor specifies its associated privilege level. Kernel
code and data segments typically use DPL 0, while user code and data
segments use DPL 3. This allows the processor to distinguish privileged
kernel execution from unprivileged user execution.


Segment Descriptors
-------------------

A **segment descriptor** describes how a memory segment may be used. It
specifies its base address and limit, together with control and access
attributes such as whether the segment contains code or data, whether it
is writable or executable, and whether it is present.


Selectors and Segment Registers
--------------------------------

A **segment selector** identifies a GDT entry and is stored in a segment
register. It contains an index into the descriptor table together with
privilege-related information.

For example, GDT index 1 corresponds to selector ``0x08`` because each
descriptor occupies 8 bytes. ``CS`` selects the current code segment,
while ``DS`` and ``SS`` traditionally select data and stack segments.
``ES``, ``FS``, and ``GS`` can also be used as data segment registers.


GDT Structure
--------------------

.. image:: ./gdt-structure.svg
   :alt: GDT Structure
   :align: center


Useful Resources
-------------------

 - https://www.youtube.com/watch?v=Wh5nPn2U_1w

