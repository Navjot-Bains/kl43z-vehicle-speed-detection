# KL43Z Vehicle Speed Detection System

**An embedded vehicle speed detection and monitoring system** developed using the NXP KL43Z microcontroller. The project simulates a vehicle passing between two detection points, measures its travel time over a known distance, calculates its speed, and compares the result against an adjustable speed limit.

The system combines sensor interfacing, GPIO interrupts, hardware timers, analog input, LED indicators, and serial communication with Linux-based data handling.

## About the Project

The project explores the development of a small-scale vehicle speed monitoring prototype using an embedded microcontroller.

Two sensors are positioned a fixed distance apart to represent two points along a road. When an object passes the first sensor, the microcontroller starts a timer. When it reaches the second sensor, the timer stops. The elapsed time and known distance are then used to calculate the object's speed.

A potentiometer provides an adjustable speed limit, while an LED is intended to indicate when the measured speed exceeds that limit. Vehicle information will also be transmitted to a Linux system for display and record keeping.

## System Features

The following functionality is planned for the system:

| Feature | Description | Technology |
| --- | --- | --- |
| Sensor Detection | Detect an object passing two fixed detection points | IR sensors, GPIO |
| Interrupt Handling | Respond to sensor events through interrupt service routines | GPIO interrupts |
| Speed Measurement | Measure elapsed time between sensor activations | Hardware timers |
| Adjustable Speed Limit | Read a configurable speed threshold | Potentiometer, ADC |
| Overspeed Warning | Activate a red LED when the measured speed exceeds the limit | GPIO, LED |
| Serial Communication | Transmit vehicle information to a Linux system | UART |
| Vehicle Data Logging | Display and record vehicle ID, speed, speed limit, and applicable fine | Linux, Bash |

## System Operation

The intended operating sequence is:

```text
       Sensor 1 Detection
               |
               v
          Start Timer
               |
               v
     Object Travels Known Distance
               |
               v
       Sensor 2 Detection
               |
               v
           Stop Timer
               |
               v
         Calculate Speed
               |
               v
      Compare Speed Limit
               |
          +----+----+
          |         |
          v         v
       Within    Overspeed
        Limit     Detected
          |         |
          v         v
       Normal    Activate
       Status    Red LED
          |         |
          +----+----+
               |
               v
       Transmit Vehicle Data
               |
               v
       Linux Data Processing
               |
               v
        Display and Log Record
```

## Technologies and Tools

| Category | Technologies |
| --- | --- |
| Microcontroller | NXP KL43Z |
| Programming Languages | C, Bash |
| Embedded Development | MCUXpresso IDE |
| Hardware Interfaces | GPIO, ADC, UART |
| Timing | Hardware timers, interrupts |
| Operating System | Linux |
| Version Control | Git, GitHub |

## Hardware Components

The prototype is designed around the NXP KL43Z development board and is expected to use:

- KL43Z microcontroller development board
- Two vehicle-detection sensors
- Potentiometer for speed-limit adjustment
- Red LED for overspeed indication
- Breadboard, resistors, and jumper wires
- USB connection for development and serial communication

## Firmware Development

The microcontroller firmware is written in C and developed using MCUXpresso IDE.

The application is being organized into separate source modules as functionality is introduced. This allows individual hardware interfaces and system components to be developed and maintained independently while contributing to one integrated application.

## Linux Data Handling

The planned Linux-side component will receive vehicle information transmitted by the KL43Z over UART.

A Bash script will be used to process incoming records, display vehicle information, calculate applicable fines based on a defined policy, and append the results to a text-based or CSV log.

## Project Structure

The repository contains the MCUXpresso firmware project and its required microcontroller support files. Additional Linux scripts and documentation will be incorporated as development progresses.

```text
kl43z-vehicle-speed-detection/
|
|-- board/                 Board support files
|-- CMSIS/                 ARM CMSIS support
|-- component/             SDK components
|-- device/                KL43Z device support
|-- drivers/               Peripheral drivers
|-- source/                Application and support source files
|-- startup/               Startup and initialization files
|-- utilities/             Utility and debug support files
|
|-- .cproject              MCUXpresso project configuration
|-- .project               Eclipse project configuration
|-- README.md              Project documentation
|-- .gitignore             Git exclusion rules
```

## Development Status

This project is currently under development. Implementation is progressing through the individual system components, beginning with sensor detection and GPIO interrupts, followed by timer-based speed measurement, ADC input, and UART communication.

The final firmware and Linux-side functionality will be integrated and tested as development continues.

## License

Project licensing and redistribution permissions for bundled third-party SDK components will be reviewed before public release.
