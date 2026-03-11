
## 2. Overview

### 2.1 Background

Paragliding instrumentation is critical for pilots to navigate vertical air movements (thermals and sink). The safety and duration of flight depend on the pilot’s ability to maximize lift while avoiding hazardous areas of rapid descent. This device, a variometer, provides the necessary sensing and feedback to enable effective thermal soaring.

### 2.2 Key Objectives and Benefits

The primary objective is to provide precise detection of vertical motion through barometric sensing and immediate pilot notification.

- **Situational Awareness:** Provides pilots with immediate environmental data.
- **Flight Optimization:** Pilots can instantly react to audio feedback to stay within thermals.
- **Safety Improvement:** Immediate alerts for rapid sink rates enable proactive safety maneuvers.

### 2.3 Main Functions and Interfaces

The device functions by sensing ambient barometric pressure, calculating vertical velocity and acceleration, and generating pitch-modulated audio. Interfaces include a physical power control for the pilot and a digital interface for data and code management via GitHub.

## 3. Operational Requirements

### 3.1 Functions

The device helps pilots detect thermal lift by continuously processing barometric pressure and providing instantaneous audio feedback, allowing hands-free centering of thermals.

- Vertical Velocity (CRITICAL): Convert ambient pressure to vertical velocity.
    
-  Calculation (CRITICAL): Compute vertical velocity and acceleration from pressure changes.
    
- Start-up: Initialize sensors and audio within 3 s.
    
- Shutdown: Safely terminate processes and stop power.
    
- Performance (CRITICAL): Audio latency ≤100 ms.
    
-  Sampling: Pressure ≥10 Hz.
    
-  Failure (CRITICAL): Continuous error tone on sensor failure.
    
- Error Management (CRITICAL): Ignore spikes >2.0 hPa in 10 ms.
    

### 3.2 Data

- Valid Ranges: Pressure 300–1100 hPa; vertical speed ±15 m/s.

    
- Access Speed (CRITICAL): Calculations ≤20 ms.
    
- Archive (Optional): Record peak climb/sink rates per cycle.
    

### 3.3 Interfaces

- User: Audio feedback via variable-pitch tones; input via power control.
    
- Equipment: Pressure sensor communicates digitally with processor.
    
- Audio Driver: Processor drives speaker with variable-frequency tones.
    

### 3.4 Environment
    
- Conditions: Operable up to 5,000 m, -20°C to +50°C, high UV exposure.
    
- Risks: Mitigate humidity, wind noise, and rapid pressure fluctuations.
    

### 4.2 Compatibility

- Source Control: Compatible with GitHub.
    

### 4.3 Availability

-  Battery: ≥20 h continuous operation.
    

### 4.4 Procedural Constraints

- Pilot Skill: Operable hands-free during active flight.
    

### 5.3 Testing

- Testing: Simulate rapid pressure changes and stress-test speaker at max volume.