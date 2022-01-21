#!/bin/bash
# Initialisation script for worker nodes

# Run common script
./common.sh

# Install packages
apt-get install nfs-client

# Mount shared storage
echo "node01:/mnt/shared /mnt/shared nfs" >> /etc/fstab
mount -a

# Enable SSH server & allow through firewall
systemctl enable --now ssh
ufw allow ssh
ufw enable

