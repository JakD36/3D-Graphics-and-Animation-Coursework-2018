//
// Created by Jack Davidson on 11/08/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_ENUMBITMASK_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_ENUMBITMASK_H

//http://blog.bitwigglers.org/using-enum-classes-as-type-safe-bitmasks/

#include <type_traits>

#define ENABLE_BITMASK_OPERATORS(x)  \
template<>                           \
struct EnableBitMaskOperators<x>     \
{                                    \
    static const bool enable = true; \
};

template<typename Enum>
struct EnableBitMaskOperators
{
    static const bool enable = false;
};

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, bool>::type operator !=(Enum lhs, typename std::underlying_type<Enum>::type rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    return static_cast<underlying>(lhs) != static_cast<underlying>(rhs);
}

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, bool>::type operator ==(Enum lhs, typename std::underlying_type<Enum>::type rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    return static_cast<underlying>(lhs) == static_cast<underlying>(rhs);
}

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, bool>::type operator >(Enum lhs, typename std::underlying_type<Enum>::type rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    return static_cast<underlying>(lhs) > static_cast<underlying>(rhs);
}

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, bool>::type operator <(Enum lhs, typename std::underlying_type<Enum>::type rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    return static_cast<underlying>(lhs) < static_cast<underlying>(rhs);
}

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator &(Enum lhs, Enum rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    return static_cast<Enum> (
            static_cast<underlying>(lhs) &
            static_cast<underlying>(rhs)
    );
}

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator ^(Enum lhs, Enum rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    return static_cast<Enum> (
            static_cast<underlying>(lhs) ^
            static_cast<underlying>(rhs)
    );
}

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator ~(Enum rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    return static_cast<Enum> (
            ~static_cast<underlying>(rhs)
    );
}

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator |(Enum lhs, Enum rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    return static_cast<Enum> (
            static_cast<underlying>(lhs) |
            static_cast<underlying>(rhs)
    );
}

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type&
operator |=(Enum& lhs, Enum rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    lhs = static_cast<Enum> (
            static_cast<underlying>(lhs) | static_cast<underlying>(rhs));
    return lhs;
}

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type&
operator &=(Enum& lhs, Enum rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    lhs = static_cast<Enum> (
            static_cast<underlying>(lhs) & static_cast<underlying>(rhs));
    return lhs;
}

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type&
operator ^=(Enum& lhs, Enum rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    lhs = static_cast<Enum> (
            static_cast<underlying>(lhs) ^ static_cast<underlying>(rhs));
    return lhs;
}

#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_ENUMBITMASK_H
