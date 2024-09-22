# Fusion Vision

## Overview

The Vision application is a sophisticated device management system designed to interface with Kinect v2 sensors using the `libfreenect2` library. This application offers functionalities such as listing available devices, opening specific devices, and selecting devices for use. It incorporates a logging system to facilitate debugging and provide informative output throughout the device management process.

## Features

- **Device Management**: Automatically detect, list, and manage Kinect devices.
- **Singleton Design Pattern**: Ensures a single instance of the `DeviceManager`.
- **Configurable Logging**: Adjustable logging levels for better debugging and monitoring.
- **Error Handling**: Robust status reporting for operations.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Architecture](#architecture)
- [File Descriptions](#file-descriptions)
- [Classes and Functions](#classes-and-functions)
- [Logging Levels](#logging-levels)
- [Error Handling](#error-handling)
- [Testing](#testing)
- [Contributing](#contributing)
- [License](#license)

## Installation

### Prerequisites

Ensure you have the following installed:

- CMake
- libfreenect2
- A C++ compiler (e.g., g++, clang)

### Steps

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/yourusername/vision.git
   cd vision
   ```

2. **Install Dependencies**:

   Follow the installation instructions for `libfreenect2` on your system.

3. **Build the Project**:

   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

4. **Run the Application**:

   ```bash
   ./vision
   ```

## Usage

Upon execution, the Vision application will automatically enumerate connected Kinect devices and log their information to the console. An example output would be:

```
[Info] [Vision] Console Logger initialized.
[Info] [Vision] Listing Devices
[Info] [Vision] Device 0: SERIAL_NUMBER_1
[Info] [Vision] Device 1: SERIAL_NUMBER_2
[Info] [Vision] Vision Finished.
```

## Architecture

The Vision application consists of several key components:

- **Device Management**: Manages the lifecycle and interactions with Kinect devices.
- **Logging System**: Logs important events and statuses to the console.
- **Status Reporting**: Provides feedback on the outcomes of operations.

### Diagram

```plaintext
+------------------+          +-------------------+
|                  |          |                   |
|  DeviceManager   |<-------->|   ConsoleLogger   |
|                  |          |                   |
+------------------+          +-------------------+
        |
        v
+------------------+
|                  |
|   Kinect Device  |
|                  |
+------------------+
```

## File Descriptions

- **config.h**: Contains configuration settings and application constants.
- **device.h**: Defines the `Device` struct for holding device attributes.
- **device_manager.h**: Declares the `DeviceManager` class for device management.
- **console_logger.h**: Defines the `ConsoleLogger` class for logging.
- **logger.h**: Abstract base class for logging utilities.
- **status.h**: Contains definitions for operation statuses and result handling.
- **main.cpp**: The entry point of the application, orchestrating the device management workflow.

## Classes and Functions

### `DeviceManager`

Handles the detection and management of Kinect devices.

#### Key Functions

- **`static DeviceManager* getInstance()`**
    - Returns the singleton instance of the `DeviceManager`.

- **`Result listDevices(const std::vector<Device>& devices) const`**
    - Lists and logs all available devices.

- **`Result openDevices(const std::vector<Device>& devices)`**
    - Opens specified devices for usage (implementation pending).

- **`Result selectDevices(const std::vector<int>& ids)`**
    - Selects devices by their IDs and logs their serial numbers.

### `ConsoleLogger`

Implements logging functionalities to the console.

#### Key Functions

- **`static ConsoleLogger* getInstance()`**
    - Returns the singleton instance of the `ConsoleLogger`.

- **`void log(Level level, const std::string& message)`**
    - Logs messages at the specified logging level.

### `Logger`

Abstract class defining the logging interface.

#### Key Functions

- **`virtual void log(Level level, const std::string &message) = 0`**
    - Abstract logging method to be implemented by derived classes.

### `Status`

An enumeration for operation statuses:

- **Success**
- **Error**
- **InvalidParam**
- **NotFound**

## Logging Levels

The application supports several logging levels to control output verbosity:

- **None**: No logging.
- **Error**: Logs error messages.
- **Warning**: Logs warnings.
- **Info**: Logs general information.
- **Debug**: Logs detailed debug information.

## Error Handling

The application implements a structured error handling mechanism using the `Result` struct, which includes status codes and messages to aid in troubleshooting.

## Testing

Unit tests are included for critical components of the application. To run the tests, use:

```bash
make test
```

Ensure your environment is set up correctly to support testing.

## Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository.
2. Create a new branch for your feature or bugfix.
3. Submit a pull request with a clear description of your changes.
