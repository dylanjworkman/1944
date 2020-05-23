#pragma once

#ifndef KEYFLAGS_H_
#define KEYFLAGS_H_

#include <cstdint>

//
// Recipe 2 - Key states used for player movement
//


// Alias an unsigned int as KeyFlags (so it looks like a new type!) - an int is typically 32 bits, but we'll use uint32_t to be clear!  Each bit will represent a key pressed (1 = pressed, 0 = not pressed).  Since an int is 32 bits, we can track 32 keys!
typedef uint32_t KeyFlags;

// These values declare which bits in KeyFlags are set / unset when a key is pressed / released respecively
enum Keys {

	Up		= 0b00001,
	Down	= 0b00010,
	Left	= 0b00100,
	Right	= 0b01000,
	Fire	= 0b10000
};
#endif