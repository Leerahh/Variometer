#include "flights.h"

/* 60-second demo profile — designed to show gradual speed changes.
 * Each entry = 1 second. Negative delta = climb, positive = descent.
 *
 * Baseline: 950.0 hPa (~540 m altitude)
 *
 * Phases:
 *  0- 4s  stable     (~0.00 hPa/s)
 *  5-14s  slow→fast climb  (-0.1 to -1.8 hPa/s ramping)
 * 15-19s  peak climb        (-2.0 hPa/s)
 * 20-24s  fast→slow climb  (-1.8 to -0.1 hPa/s ramping down)
 * 25-29s  stable glide     (~0.00 hPa/s)
 * 30-39s  slow→fast descent (+0.1 to +1.8 hPa/s ramping)
 * 40-44s  peak descent      (+2.0 hPa/s)
 * 45-49s  fast→slow descent (+1.8 to +0.1 hPa/s ramping down)
 * 50-59s  stable landing   (~0.00 hPa/s) — then loops
 */
const float _data_demo[] = {
    /* 0-4: stable */
    950.00f, 950.01f, 949.99f, 950.00f, 950.01f,

    /* 5-14: climb ramp-up (-0.1, -0.3, -0.5, -0.8, -1.1, -1.4, -1.6, -1.7, -1.8, -1.9) */
    949.90f, 949.60f, 949.10f, 948.30f, 947.20f,
    945.80f, 944.20f, 942.50f, 940.70f, 938.80f,

    /* 15-19: peak climb (-2.0 hPa/s) */
    936.80f, 934.80f, 932.80f, 930.80f, 928.80f,

    /* 20-24: climb ramp-down (-1.9, -1.8, -1.6, -1.4, -1.1) */
    926.90f, 925.10f, 923.50f, 922.10f, 921.00f,

    /* 25-29: stable glide */
    921.00f, 921.02f, 920.99f, 921.01f, 921.00f,

    /* 30-39: descent ramp-up (+0.1, +0.3, +0.5, +0.8, +1.1, +1.4, +1.6, +1.7, +1.8, +1.9) */
    921.10f, 921.40f, 921.90f, 922.70f, 923.80f,
    925.20f, 926.80f, 928.50f, 930.30f, 932.20f,

    /* 40-44: peak descent (+2.0 hPa/s) */
    934.20f, 936.20f, 938.20f, 940.20f, 942.20f,

    /* 45-49: descent ramp-down (+1.9, +1.8, +1.6, +1.4, +1.1) */
    944.10f, 945.90f, 947.50f, 948.90f, 950.00f,

    /* 50-59: stable landing */
    950.00f, 950.01f, 949.99f, 950.00f, 950.01f,
    950.00f, 949.99f, 950.01f, 950.00f, 950.00f
};

const Flight flight_demo = {
    .data   = _data_demo,
    .length = sizeof(_data_demo) / sizeof(_data_demo[0])
};
