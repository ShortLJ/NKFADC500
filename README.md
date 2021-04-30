# NKFADC500\
GUI program builder for NKFADC500 DAQ system.

Prerequisite: libUSB-devel\
  $ dnf install libusbx-devel ##for CentOS8

Install\
  $ mkdir build && cd build && cmake .. && make\
   then, you can run NKFADCgui on by\
  $ root NKFADC500.c

If failure on TCB, check permission of usb devices. \
  $ sudo sh TCB_permission.sh
