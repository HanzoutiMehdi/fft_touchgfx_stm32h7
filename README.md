# FIR-FFT Project

## Overview
This project demonstrates the implementation of Finite Impulse Response (FIR) filtering and Fast Fourier Transform (FFT) on an STM32 microcontroller using STM32CubeIDE and TouchGFX.

## Toolchain & Tools
- **IDE**: STM32CubeIDE 1.15
- **TouchGFX**: 4.24.0

## Project Description
The project involves generating and processing signals, applying FIR filtering, performing FFT, and visualizing the results on a graphical interface.

### Input Signals
- Software-generated signals using the sine function.
- Static signals described as \(70 \sin(2\pi \times 30)\), corresponding to a 30Hz signal.

### Sampling Time
- **4ms** for signal generation and processing.
- **250Hz** for tasks configuration.

### Output Signal
- Processed using FFT.
- FIR low pass filter applied with a cutoff frequency of 20Hz.

## Software Description
The main code is in `Main.c`, which initializes the MCU and tasks, runs the RTOS, and configures three primary tasks:

### Tasks
1. **TouchGFX_Task**
   - Manages the screen view.
2. **vmainTask**
   - Generates input signal and applies the FIR filter.
3. **fft_task**
   - Produces FFT for both input and output signals.

### Task Configuration
- **Sampling Time**: 250Hz
- Interaction between tasks and screens for signal processing and display.

## FIR Octave Script
The `fir_filtre.m` script generates FIR coefficients using Octave. After executing this script, call the function `stm32f4_fir_coeffs(b)` to generate new FIR coefficients.

## Getting Started

### Prerequisites
- STM32CubeIDE 1.15
- TouchGFX 4.24.0
- Octave (for FIR coefficient generation)

### Installation
1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/FIR-FFT-Project.git
    ```
2. Open the project in STM32CubeIDE.
3. Build and flash the project to your STM32 microcontroller.

### Running the Project
1. Run the Octave script `fir_filtre.m` to generate FIR coefficients.
2. Flash the generated firmware to the STM32 microcontroller.
3. The TouchGFX interface will display the input and output signals along with their FFT results.

## Usage
- The project configures the MCU to generate and process signals.
- The TouchGFX interface provides a visual representation of the input signal, FIR-filtered signal, and their respective FFT results.


## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contact
For any inquiries or feedback, please contact Mehdi Hanzouti.

