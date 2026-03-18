## 1. Overwiew 

This document describes the hardware design specification of a variometer intended for paragliding applications, implemented using microcontrollers from the STM32L4 Series and STM32L4+ Series. The variometer measures changes in atmospheric pressure to determine the rate of climb or descent, providing real-time feedback to the pilot during flight.
The hardware development is based on the guidelines provided in the application note AN4555, which describes the minimum hardware resources required for STM32L4/L4+ microcontroller systems. These recommendations are used to ensure reliable operation, low power consumption, and proper integration of the microcontroller within the embedded system.
The variometer hardware platform integrates several key components, including a barometric pressure sensor, the STM32L4 microcontroller, power management circuitry, and user interface elements such as display and audio indicators. The pressure sensor provides high-resolution atmospheric pressure measurements that are processed by the microcontroller to calculate the vertical speed.
This document focuses on the hardware architecture and design considerations of the system. The different board features that require sensor integration, such as the pressure sensing interface, peower supply connections, and communication interfaces, will be described in detail throughout this Hardware Design Specification.

## 2. System desing

### 2.1 Presuare Sensing Sub-system

#### 2.1.1 Purpose 

The purpose of the Pressure Sensing Sub-system is to measure the ambient atmospheric pressure in order to detect altitude changes. The subsystem provides digital pressure data to the microcontroller through a communication interface, allowing the system to continuously monitor pressure variations and determine the corresponding altitude and vertical speed.Additionally, the processing subsystem manages communication with other subsystems, including the user interface, audio feedback, and optional communication interfaces.

#### 2.1.2 Requirments

### 2.2 Audio sub system

#### 2.2.1 Purpose

The purpose of the Processing Sub-system is to acquire, process, and interpret the sensor data required for the operation of the variometer.
#### 2.2.2 Requirments

### 2.3. Processing sub-system


#### 2.3.1 Purpose

The purpose of the Audio Sub-system is to provide acoustic feedback to the paraglider pilot indicating the current vertical motion of the aircraft. The subsystem generates audio signals that correspond to the calculated vertical speed, allowing the pilot to receive real-time climb or sink information without continuously monitoring the visual display.

#### 2.3.2 Requirments


### powee subsystem

### data logger subsystem 

1. select the sensors with beapers maybe 

#### uswe interface subsystem

lds in this subsystem 

modules are hardware and sortware 
