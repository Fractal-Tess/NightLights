#pragma once
#include <stdint.h>

const uint16_t SECOND = 1000;
const uint16_t MINUTE = 60 * SECOND;

const uint32_t QUARTER_HOUR = 15 * (uint32_t)MINUTE;
const uint32_t HALF_HOUR = 30 * (uint32_t)MINUTE;
const uint32_t FULL_HOUR = 60 * (uint32_t)MINUTE;

const uint16_t DEBUG = 5 * SECOND;

const uint32_t UINT32_T_MAXVAl = 4294967295;

const uint16_t DEFAULT_BTN_COOLDOWN = 1 * SECOND;
