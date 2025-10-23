# High-Performance C++ Monte Carlo Option Pricer

![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![License](https://img.shields.io/badge/License-MIT-green)

This project is a high-performance C++ application for pricing European Call and Put options. It leverages modern C++17 features, including multithreading and object-oriented design, to build an efficient and extensible financial modeling tool.

This project was developed to apply advanced C++ programming concepts to a classic quantitative finance problem. The focus is on **performance**, **numerical efficiency**, and **robust software design**—all critical skills in quantitative finance and high-frequency trading (HFT).

---

## ⚡ Key Features

* **Prices European Call & Put options** based on the Geometric Brownian Motion model.
* **Object-Oriented Design:** Fully encapsulated logic using C++ classes, structs, and `enum` types for clarity and extensibility.
* **Numerical Efficiency:** Implements the **Antithetic Variates** technique, a variance reduction method that significantly improves the accuracy and convergence speed of the simulation.
* **High-Performance Parallelization:** Uses the C++ `<thread>` library to parallelize the simulation workload, distributing computations across all available CPU cores for a dramatic speedup.

---

## 📊 Performance Benchmark

A benchmark was conducted to measure the speedup achieved from parallelization. The task was to price an option using 1,000,000 Monte Carlo paths.

| Version | Execution Time |
| :--- | :--- |
| **Single-Threaded** | 0.01187 seconds |
| **Multi-Threaded** | 0.00496 seconds |

### **Achieved Speedup: 2.39x**

This benchmark demonstrates a significant performance gain, showcasing the effectiveness of the multithreaded architecture for computationally intensive financial modeling.

---

## ⚙️ Core Concepts Implemented

* **Financial Modeling:**
    * Geometric Brownian Motion (GBM)
    * European Option Payoff Structures
    * Risk-Neutral Pricing & Discounting
* **Computer Science:**
    * Multithreading & Parallel Computing
    * Object-Oriented Programming (OOP)
    * Numerical Methods (Monte Carlo)
    * Variance Reduction Techniques

---

## 🚀 Getting Started

### Prerequisites

* A C++17 compatible compiler (e.g., g++)
* The POSIX Threads (pthread) library (standard on Linux/macOS, available on Windows via MinGW/MSYS2)

### Compilation

Clone the repository and compile the main file. The `-pthread` flag is required to link the C++ threading library.

```bash
g++ -std=c++17 -pthread main.cpp -o pricer
