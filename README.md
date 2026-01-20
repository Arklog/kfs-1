KFS-1 is the first module of a 10 Projects series.

The code documentation is available [here](https://arklog.github.io/kfs-1/).

# Overview

This project introduces the fundamentals of operating system development. The goal is to build a minimal kernel from scratch, focusing on low-level concepts such as bootloading, basic hardware interaction or kernel-screen interface. Through this project, we have developed a deeper understanding of how an operating system works.

# TODO KFS-1

 - [x] a kernel bootable via GRUB.
 - [x] Asm multi-boot.
 - [x] basic kernel libraries:
   - string
   - vga
   - container
   - port
 - [x] kernel-screen interface to display things.
 - [x] write 42 on the screen.

# TODO KFS-1 BONUS

- [x] Add scroll and cursor support to your I/O interface.
- [x] Add colors support to your I/O interface.
- [x] Add helpers like printf / printk in order to print information / debug easily.
- [x] Handle keyboard entries and print them.
- [ ] Handle different screens, and keyboard shortcuts to switch easily between then.


