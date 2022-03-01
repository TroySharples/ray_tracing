#pragma once

namespace unstd
{
	template <typename _T>
	size_t unsigned_max() { return std::pow(2, 8 * sizeof(_T)) - 1; }
}