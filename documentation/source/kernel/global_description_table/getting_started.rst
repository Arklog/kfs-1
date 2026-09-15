
.. _getting-started:
 
Getting Started
===============
 
The Global Descriptor Table (GDT) is a data
structures used to implement memory segmentation and
privilege-level isolation. Before any protected-mode code can safely
execute, the CPU must be given a valid GDT to consult. Without it, the
processor has no way to know which memory regions exist, who is allowed
to access them, or at what privilege level.
 
Why the GDT matters
--------------------
 
Each entry in the GDT is called a **segment descriptor**. A descriptor
does not contain data itself; instead, it describes a memory region by
specifying its base address, its size (limit), its access rights, and
the privilege ring (0 to 3) required to use it. When a segment register
such as ``CS`` or ``DS`` is loaded with a *selector*, the CPU uses that
selector as an index into the GDT to fetch the corresponding descriptor
and enforce its rules on every subsequent memory access through that
segment.
 
A minimal kernel GDT
----------------------
 
A typical kernel-level GDT contains at least the following entries:
 
+-------+-----------+------+-----------------------------+
| Index | Selector  | Ring | Purpose                     |
+=======+===========+======+=============================+
| 0     | 0x00      | —    | Mandatory null descriptor   |
+-------+-----------+------+-----------------------------+
| 1     | 0x08      | 0    | Kernel code segment         |
+-------+-----------+------+-----------------------------+
| 2     | 0x10      | 0    | Kernel data segment         |
+-------+-----------+------+-----------------------------+
| 3     | 0x18      | 3    | User code segment           |
+-------+-----------+------+-----------------------------+
| 4     | 0x20      | 3    | User data segment           |
+-------+-----------+------+-----------------------------+
| 5     | 0x28      | —    | Task State Segment          |
|       |           |      |                             |
+-------+-----------+------+-----------------------------+

