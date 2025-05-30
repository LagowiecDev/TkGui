#pragma once
#include "TkGui/TkGui_API.hpp"
#include <array>
#include <vector>
#include <memory>
#include <cstdint>
#include <algorithm>
#include <initializer_list>

namespace TkGui
{
	using float32_t = float;
	using float64_t = double;

	using vertex_t = float32_t;
	using index_t = uint32_t;

	struct TKGUI_API Float32x2_t
	{
	public:
		Float32x2_t(float32_t x, float32_t y) : x(x), y(y) { }
	public:
		float32_t x;
		float32_t y;
	};

	struct TKGUI_API Float32x3_t
	{
	public:
		Float32x3_t(float32_t x, float32_t y, float32_t z) : x(x), y(y), z(z) { }
	public:
		float32_t x;
		float32_t y;
		float32_t z;
	};

	struct TKGUI_API Float32x4_t
	{
	public:
		Float32x4_t(float32_t x, float32_t y, float32_t z, float32_t w) : x(x), y(y), z(z), w(w) { }
	public:
		float32_t x;
		float32_t y;
		float32_t z;
		float32_t w;
	};
}