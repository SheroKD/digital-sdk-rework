#pragma once
#include <cstdint>
#include <cstring>

template<typename T, T value>
struct constant_holder_t {
	enum class e_value_holder : T {
		m_value = value
	};
};

#define CONSTANT(value) (static_cast<decltype(value)>(constant_holder_t<decltype(value), value>::e_value_holder::m_value))

namespace hash::fnv1a
{
	constexpr auto m_seed = 0x45C3370D;
	constexpr auto m_prime = 0x1000193;

	__forceinline uint32_t rt(const char* txt) {
		auto hash = m_seed;

		for (auto i = 0u; i < strlen(txt); i++) {
			hash ^= txt[i];
			hash *= m_prime;
		}

		return hash;
	}

	constexpr uint32_t hash_const(const char* szString, const uint32_t uValue = 0x45C3370D) noexcept
	{
		return (szString[0] == '\0') ? uValue : hash_const(&szString[1], (uValue ^ uint32_t(szString[0])) * m_prime);
	}

	constexpr uint32_t ct(const char* txt, uint32_t value = m_seed) noexcept {
		return !*txt ? value : ct(txt + 1, static_cast<unsigned>(1ull * (value ^ static_cast<uint8_t>(*txt)) * m_prime));
	}
}

#define FNV32(txt) CONSTANT(hash::fnv1a::ct(txt))
#define FNV1A_RT(txt) hash::fnv1a::rt(txt)