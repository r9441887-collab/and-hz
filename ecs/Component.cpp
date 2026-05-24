#include "../../include/ecs/Component.hpp"

// ComponentIdCounter::next() is inline static, but we ensure it's instantiated.
// The counter starts at 0 and increments on each REGISTER_COMPONENT call.
