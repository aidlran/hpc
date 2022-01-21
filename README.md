This repository branch contains resources for my HPC module coursework.

# Cluster Setup

1. Deploy Ubuntu instances and connect them to the network/internet.  
   I used LXC containers via Proxmox VE.  
   The head node should be called "node01".


2. Add all IP address & hostnames to `/etc/hosts` of every instance.


3. Copy `init-scripts` to each instance.


4. Depending on the role of the node, run either the `head.sh` or `worker.sh`
script from the `init-scripts` folder as root. Both scripts will run `common.sh`,
so make sure it's also present in the same folder.


5. All nodes will have a user `hpc` that all share a storage space on the head
node as a home directory. Use this environment to build and run parallel programs.
