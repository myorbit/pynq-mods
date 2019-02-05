# PYNQ Mods

This repository contains examples on how to modify or enhance PYNQ.

* [`microblaze_cutom_i2c_demo_ina219`](microblaze_custom_i2c_demo_ina219): A custom I2C master demo using MicroBlaze and evaluating the bytes transferred. This demo shows three different methods to return the length of bytes transferred to/from a I2C slave which is not incorporated with the standard PYNQ library.

* [`slcan_demo`](slcan_demo): A demo showing how to provide SocketCAN with a SLCAN based interface type and automate it. This involves compiling the kernel module `slcan` on the PYNQ-Z1 board, bringing up a SLCAN interface using the Zubax Babel CAN-to-USB adapter and finally reading messages from the CAN bus.
