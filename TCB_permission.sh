# TCB_permission.sh

#lsusb | grep Anchor ## memo #bus, #Device
#ll /dev/bus/usb/(#bus)/(#Device)
#sudo chmod 666 /dev/bus/usb/(#bus)/(#Device)

echo SUBSYSTEM=="usb",ATTR{idVendor}=="0547",ATTR{idProduct}=="1307",MODE="0666" >> /etc/udev/rules.d/71-notice-dev-permissions.rules
echo SUBSYSTEM=="usb",ATTR{idVendor}=="0547",ATTR{idProduct}=="1308",MODE="0666" >> /etc/udev/rules.d/71-notice-dev-permissions.rules
