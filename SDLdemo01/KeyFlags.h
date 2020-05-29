#pragma once

#ifndef KEYFLAGS_H_
#define KEYFLAGS_H_

#include <cstdint>

//32-bit keyflags
typedef uint32_t KeyFlags;

enum Keys {

	Up		= 0b00001,
	Down	= 0b00010,
	Left	= 0b00100,
	Right	= 0b01000,
	Fire	= 0b10000
};
#endif