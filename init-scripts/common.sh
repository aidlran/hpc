#!/bin/bash
# Initialisation script for all nodes

# Update packages
apt-get update
apt-get upgrade
apt-get install openssh-server mpich

# Create a user without root privileges to use in cluster
# Their home directory will be the folder where shared storage is mounted
#  so that all nodes can share the SSH key
adduser --home /mnt/shared hpc
