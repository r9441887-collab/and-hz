#pragma once
#include <cstddef>

using ComponentType = size_t;

template<typename T>
ComponentType componentId() {
    static ComponentType id = counter++();
    return id;
}

struct ComponentIdCounter {
    static ComponentType next() {
        static ComponentType id = 0;
        return id++;
    }
};

#define REGISTER_COMPONENT(Type) \
    template<> inline ComponentType componentId<Type>() { \
        static ComponentType id = ComponentIdCounter::next(); \
        return id; \
    }
