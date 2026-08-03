# Performance Profiling and Optimization using GPROF and PERF

## Overview

This project analyzes the performance of **Bubble Sort** and **Quick Sort** on approximately **18,250 randomly generated temperature records**. The application is profiled using **GPROF** to identify execution hotspots and **PERF** to collect hardware performance metrics. Compiler optimizations (`-O0`, `-O2`, and `-O3`) are also evaluated to study their impact on execution time and CPU performance.

## Features

- Generates ~18,250 random temperature values.
- Implements and compares Bubble Sort and Quick Sort.
- Measures execution time of both algorithms.
- Profiles the application using **GPROF**.
- Collects CPU performance statistics using **PERF**.
- Evaluates the impact of compiler optimizations (`-O0`, `-O2`, `-O3`).