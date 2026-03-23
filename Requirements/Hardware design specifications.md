## 1. Overwiew 

This document describes the hardware design specification of a variometer intended for paragliding applications, implemented using microcontrollers from the STM32L4 Series and STM32L4+ Series. The variometer measures changes in atmospheric pressure to determine the rate of climb or descent, providing real-time feedback to the pilot during flight.
The hardware development is based on the guidelines provided in the application note AN4555, which describes the minimum hardware resources required for STM32L4/L4+ microcontroller systems. These recommendations are used to ensure reliable operation, low power consumption, and proper integration of the microcontroller within the embedded system.
The variometer hardware platform integrates several key components, including a barometric pressure sensor, the STM32L4 microcontroller, power management circuitry, and user interface elements such as display and audio indicators. The pressure sensor provides high-resolution atmospheric pressure measurements that are processed by the microcontroller to calculate the vertical speed.
This document focuses on the hardware architecture and design considerations of the system. The different board features that require sensor integration, such as the pressure sensing interface, peower supply connections, and communication interfaces, will be described in detail throughout this Hardware Design Specification.

## 2. System desing

### 2.1 Pressure Sensing Sub-system

#### 2.1.1 Purpose 

The purpose of the Pressure Sensing Sub-system is to measure the ambient atmospheric pressure in order to detect altitude changes. The subsystem provides digital pressure data to the microcontroller through a communication interface, allowing the system to continuously monitor pressure variations and determine the corresponding altitude and vertical speed.Additionally, the processing subsystem manages communication with other subsystems, including the user interface, audio feedback, and optional communication interfaces.

#### 2.1.2 Requirments

DPS310 Digital Pressure Sensor
**Measurement Performance**
- Operation range: Pressure: 300-1200 hPa, Temperature -20 - 60 °C
- Pressure resolution: ≤ 0.01 hPa  (or ≤ 0.08 m)
- Relative accuracy:  ≤ ±0.1 hPa (or ≤ ± 0.8 m)
**Sampling / Timing**:
- Output data rate (ODR)  ≥ 25 Hz
- Measurement mode: Continuous measurement mode required
- Latency: Measurement time ≤ 30 ms in high precision mode
**Interface**
- Communication interface : I²C or SPI
**Power Supply 
- Supply voltage 1.7 V - 3.6 V
- Power consumption: 
	- ≤ 10 µA average during operation
	- Low-power standby mode required

### 2.2 Output sub system

#### 2.2.1 Purpose
The purpose of the Output Sub-system is to provide real-time feedback to the user. This includes acoustic signals indicating vertical motion (climb/sink) and visual feedback via LEDs for debugging and system status indication.
#### 2.2.2 Requirments
SP-2209
**Acoustic Output
- Sound generation: audible tones corresponding to vertical speed
- Audible range approx. 1kHz - 5 kHz
- Signal type : PWM-driven audio signal from MCU
**Electrical Characteristics**
- Compatible with 3.0 V system supply
- Should not exceed system power budget
**Control Requirements 
- Audio control: The output shall be controllable via PWM signal
- Response time: Audio feedback shall reflect vertical speed changes with latency ≤ 100 ms
**Mechanical / Integration**
- Speaker mounting: Speaker shall be securely mounted in enclosure
- Environmental considerations: Output shall remain audible in outdoor conditions (wind, flight noise)

**LED Debug Interface**
- Functionality : LEDs shall indicate system states (e.g. power, sensor activity, error states)
- Control : Individually controllable via GPIO
- Visibility: Clearly visible under daylight conditions
- Power consumption: Minimized using current-limiting resistors and duty cycling


### 2.3. Processing sub-system


#### 2.3.1 Purpose

The purpose of the Audio Sub-system is to provide acoustic feedback to the paraglider pilot indicating the current vertical motion of the aircraft. The subsystem generates audio signals that correspond to the calculated vertical speed, allowing the pilot to receive real-time climb or sink information without continuously monitoring the visual display.

#### 2.3.2 Requirments
Minimum Requirements for STM32
• Clock
	• LSE: X2– 32.768 kHz crystal for the embedded RTC
	• HSE: X1– 8 MHz crystal for the STM32L4 Series microcontroller
• Reset
	• Reset signal is active low
• Boot mode
	• Select boot mode via BOOT0
• SWD interface, debug UART
	• Minimum requirement is SWDIO/SWCLK
	• Further JTAG functions as well as a UART can be handy
• Power supply
	• Depends on peripheral needs
	• A single 3.0V via LDO is a good first approximation
	• Separate stabilization capacitors at all VCC pins (100nF)
### 2.4 power subsystem

#### 2.4.1 Purpose
The purpose of the Power Management Sub-system is to provide a stable and efficient power supply to all components of the variometer system
#### 2.4.2 Requirements
**Functional Requirements**

- The subsystem shall supply stable regulated voltage to all system components.
- The subsystem shall support battery-powered operation.

**Power Requirements**

- The subsystem shall operate with a low power consumption suitable for portable use.
- The subsystem shall support the voltage levels required by the STM32L4/L4+ microcontroller and pressure sensor.

For **STM32L4/L4+ microcontroller**  require a 1.71 V to 3.6 V operatingvoltage supply (VDD). Several independent supplies (VDDA, VDDIO2, VDDUSB, VLCD(b), VDDDSI), can be provided for specific peripherals. 
All the specifications for the supplies are in the application note AN4555 page 7/55. 

For the pressure sensor ...................

#### 2.4.3 Power Architecture

#### 2.4.4 Main Components

####  2.5 Storage subsystem 

#### 2.4.5 Protection and Monitoring

#### 2.4.6 Open Design Decisions

1. select the sensors with beapers maybe 

#### user interface subsystem

 in this subsystem 

modules are hardware and software 
