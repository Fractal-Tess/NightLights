#pragma once
#include <stdint.h>
#include <Arduino.h>

template <typename... Args>
void pprint(const Args &...a);

void print_uint32_t(uint32_t num);
