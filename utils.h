#ifndef TP1_IFT630_UTILS_H
#define TP1_IFT630_UTILS_H

#pragma once
#include <cstdint>
#include <limits>
#include <random>

// Crédit Karim Elmougi-Côté
namespace cppUtils {
    template <typename T>
    T random(const T lower_bound, const T upper_bound) noexcept {
        static_assert(std::is_arithmetic<T>::value);
        static_assert(!std::is_same<T, bool>::value);
        auto dist = [lower_bound, upper_bound]() {
            if constexpr (std::is_floating_point<T>::value)
                return std::uniform_real_distribution<T>{lower_bound, upper_bound};
            else
                return std::uniform_int_distribution<T>{lower_bound, upper_bound};
        }();
        static std::random_device r{};
        auto engine = std::default_random_engine{r()};
        return dist(engine);
    }
    template <typename T>
    T random() noexcept {
        return random<T>(std::numeric_limits<T>::min(),
                         std::numeric_limits<T>::max());
    }
    template <>
    bool random<bool>() noexcept {
        return static_cast<bool>(random<uint16_t>(0, 1));
    }
} // namespace cppUtils





#endif //TP1_IFT630_UTILS_H
