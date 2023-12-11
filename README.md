# CSMA/CA Simulation for Wireless Networks

This program simulates the behavior of nodes in a wireless network using the Carrier Sense Multiple Access with Collision Avoidance (CSMA/CA) protocol.

## Description

The simulation environment allows users to configure the number of nodes (N) and a shared communication channel. It implements key aspects of CSMA/CA, such as backoff mechanisms, collision avoidance, and statistics tracking.

## Features

- **Node Configuration:** Users can set up a network with a configurable number of nodes.
- **Channel Management:** Shared communication channel where nodes contend for access.
- **Backoff Mechanism:** Nodes choose random backoff intervals before attempting to transmit data.
- **Collision Detection:** Detects collisions when multiple nodes attempt to transmit simultaneously and implements backoff.
- **Statistics Tracking:** Records statistics including successful transmissions, collisions, and backoff instances.

## Usage

1. **Setup:**
    - Compile the `main.cpp` file using a C++ compiler (e.g., `g++ -o main main.cpp`).
2. **Execution:**
    - Run the compiled executable (`./main`).
    - Enter the number of nodes in the network.
    - Set parameters for backoff intervals, maximum transmission attempts, etc.
3. **Simulation:**
    - The program simulates the behavior of nodes according to CSMA/CA.
    - It displays the status of the channel, nodes attempting transmission, collisions, and backoff attempts in each time slot.
4. **Output:**
    - Provides statistics on successful transmissions, collisions, and backoff instances.

## Example

![csma1](https://github.com/saisanthoshbussa/CSMA-CA-Wireless-Network-Simulation/assets/118352633/f11475d6-b840-4c1d-8a04-80e2726c05fe)

