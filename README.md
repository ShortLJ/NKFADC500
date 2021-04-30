# NKFADC500\
GUI program builder for NKFADC500 DAQ system.

Prerequisite: libUSB-devel\
  $ dnf install libusbx-devel ##for CentOS8

Install\
  $ mkdir build && cd build && cmake .. && make\
   then, you can run NKFADCgui on by\
  $ root NKFADC500.c

If failure on TCB, check permission of usb devices.\
  $ lsusb | grep Anchor ## memo #bus, #Device\
  $ ll /dev/bus/usb/(#bus)/(#Device)\
  $ sudo chmod 666 /dev/bus/usb/(#bus)/(#Device)\
Or add rules of device permision permanently. \
  $ sudo echo SUBSYSTEM=="usb",ATTR{idVendor}=="0547",ATTR{idProduct}=="1307",MODE="0666" >> /etc/udev/rules.d/71-notice-dev-permissions.rules\
  $ sudo echo SUBSYSTEM=="usb",ATTR{idVendor}=="0547",ATTR{idProduct}=="1308",MODE="0666" >> /etc/udev/rules.d/71-notice-dev-permissions.rules

