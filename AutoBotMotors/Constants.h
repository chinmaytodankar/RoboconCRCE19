// Ensures this Header File is only included Once while compiling
#pragma once

// This file Stores all the Constants Involved
// Example Pin Numbers

// Please ensure that all NULL Statements have values

// Writing Pin would expand to this
// For example
// Pin pin;
// and
// byte pin;
// would be the same statements
using Pin = byte;

// FRONT LEFT
Pin constexpr const DIRECTION_FL = 6;
Pin constexpr const PWM_FL       = 7;
// FRONT RIGHT
Pin constexpr const DIRECTION_FR = 8;
Pin constexpr const PWM_FR       = 9;
// BACK LEFT
Pin constexpr const DIRECTION_BL = 10;
Pin constexpr const PWM_BL       = 12;
// BACK RIGHT
Pin constexpr const DIRECTION_BR = 4;
Pin constexpr const PWM_BR       = 5;

//// FRONT LEFT Encoder PINS
// Pin constexpr const ENC_FL_U = 2;
// Pin constexpr const ENC_FL_D = A7;
//// FRONT RIGHT Encoder PINS
// Pin constexpr const ENC_FR_U = 3;
// Pin constexpr const ENC_FR_D = A4;