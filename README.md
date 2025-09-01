# Electrochemistry Simulation & Interface Tools

This repository contains three modular C++ programs designed for simulating and analyzing electrochemical systems. It includes chronoamperometric simulation, impedance spectrum modeling, and a serial-to-TCP interface for hardware integration with Windows-based software.

This code was developed for electrochemical modeling purposes and is suitable for academic projects, prototyping sensor systems, or interfacing low-cost potentiostats.

---

## Contents

| Module           | Description                                                                 |
|------------------|-----------------------------------------------------------------------------|
| `Chronoamperometry.cpp` | Simulates current-time behavior using parameters from CSV input         |
| `Impedance.cpp`         | Computes complex impedance spectra based on Randles circuit model      |
| `Interface.cpp`         | Reads serial impedance data, calculates magnitude/phase, sends via TCP |

---

## 1. Chronoamperometry Simulation

**File:** `Chronoamperometry.cpp`  
**Input:** `electrochemical_data.csv`  
**Output:** `chronoamperometry_data_*.txt`

### Features:
- Uses temperature, diffusion, concentration, and redox potential to compute current
- Outputs a simulated current-time profile
- Adjustable parameters per CSV row

### Usage:
```bash
g++ Chronoamperometry.cpp -o chrono
./chrono



