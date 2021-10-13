#pragma once
#include <stdint.h>

const uint16_t SECOND = 1000;
const uint16_t MINUTE = 60 * SECOND;

const uint16_t QUARTER_HOUR = 15 * MINUTE;
const uint16_t HALF_HOUR = 30 * MINUTE;
const uint16_t FULL_HOUR = 60 * MINUTE;

const uint16_t DEBUG = 5 * SECOND;

const uint32_t DEFAULT_BTN_COOLDOWN = SECOND;
