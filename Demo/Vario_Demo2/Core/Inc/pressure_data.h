#ifndef PRESSURE_DATA_H
#define PRESSURE_DATA_H

#include <stdint.h>

#define PRESSURE_SAMPLES 60   /* 60 seconds at 1 Hz */

extern const float pressure_hPa[PRESSURE_SAMPLES];

#endif
