#!/bin/bash

# Must run under root
if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit 1
fi

# Load Virtual CAN driver
sudo modprobe vcan

# Load CAN Gateway driver
sudo modprobe can-gw

# Initialize Virtual CAN #1
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0

# Initialize Virtual CAN #2
sudo ip link add dev vcan1 type vcan
sudo ip link set up vcan1

# Connect vcan0 => vcan1
sudo cangw -A -s vcan0 -d vcan1 -e

# Connect vcan1 => vcan0
sudo cangw -A -s vcan1 -d vcan0 -e

# Making sure we can link the shared object
if [ -z "$LD_LIBRARY_PATH" ]
then
  export LD_LIBRARY_PATH=/usr/local/lib
fi

echo "Done! Run this to list all available network adapters:"
echo "ip link"
