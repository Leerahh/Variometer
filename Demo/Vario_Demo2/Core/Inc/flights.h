#ifndef FLIGHTS_H
#define FLIGHTS_H

#include <stdint.h>

/* ============================================================
 * FLIGHT SELECTOR — change this one line to switch flights,
 * then rebuild and flash.
 *
 *   0 = flight_demo   (short 60-second fake data)
 *   1 = flight_igc    (real IGC flight, full length)
 * ============================================================ */
#define ACTIVE_FLIGHT  1

/* ----------------------------------------------------------
 * Tuning — adjust per flight if needed.
 * igc_summary.txt gives recommended values for real flights.
 * ---------------------------------------------------------- */
#if ACTIVE_FLIGHT == 0
  #define VARIO_DEADBAND_HPA   0.05f
  #define CLIMB_SCALE_HPA      2.00f
  #define LED1_BLINK_MIN_MS   80u
  #define LED1_BLINK_MAX_MS   800u
  #define LED3_ON_MIN_MS        500u
  #define LED3_ON_MAX_MS        1500u
  #define LED3_OFF_MS           200u

#elif ACTIVE_FLIGHT == 1
  /* Paste values from igc_summary.txt here */
  #define VARIO_DEADBAND_HPA   0.020f
  #define CLIMB_SCALE_HPA      0.50f
  #define LED1_BLINK_MIN_MS   80u
  #define LED1_BLINK_MAX_MS   800u
  #define LED3_ON_MIN_MS        500u
  #define LED3_ON_MAX_MS        1500u
  #define LED3_OFF_MS           200u
#endif

/* ----------------------------------------------------------
 * Flight data type — do not change.
 * ---------------------------------------------------------- */
typedef struct {
    const float    *data;
    uint32_t        length;
} Flight;

/* Forward declarations for each flight */
extern const Flight flight_demo;
extern const Flight flight_igc;

/* The active flight — selected at compile time */
#if   ACTIVE_FLIGHT == 0
  #define CURRENT_FLIGHT  flight_demo
#elif ACTIVE_FLIGHT == 1
  #define CURRENT_FLIGHT  flight_igc
#endif

#endif /* FLIGHTS_H */
