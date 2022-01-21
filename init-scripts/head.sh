#!/bin/bash
# Initialisation script for the head node

# Run common script
./common.sh

# Install packages
apt-get install nfs-server build-essential git

# Set up NFS share
echo "/mnt/shared *(rw,sync,no_subtree_check)" >> /etc/exports
service nfs-kernel-server restart

# Clone HPC repo
sudo -u hpc git clone -b city3112 https://github.com/aid-lo/hpc.git /mnt/shared/hpc

# Compile MPI programs
sudo -u hpc mpicc /mnt/shared/hpc/mpi-src/hello-world.c -o hello-world

# Generate SSH key for HPC user
sudo -u hpc ssh-keygen
sudo -u hpc cat /mnt/shared/.ssh/id_rsa.pub >> /mnt/shared/.ssh/authorized_keys
