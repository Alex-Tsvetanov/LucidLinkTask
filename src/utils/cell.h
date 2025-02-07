#include <cstdint>
#include <unordered_set>
#include <vector>

#ifndef TYPES_H
#define TYPES_H

#ifdef COORD_32BIT
using coord_t = uint32_t;
#else
using coord_t = uint64_t;
#endif

namespace solution {
	class cell {
	public:
		coord_t row;
		coord_t col;

		cell() : row(0), col(0) {}
		cell(coord_t _row, coord_t _col) : row(_row), col(_col) {}
		cell(std::pair<coord_t, coord_t> coords) : row(coords.first), col(coords.second) {}

		bool operator==(const cell& other) const { return row == other.row && col == other.col; }
	};
}  // namespace solution

namespace std {
	template <>
	struct hash<solution::cell> {
		size_t operator()(const solution::cell& p) const noexcept {
#ifdef COORD_32BIT
			return (static_cast<uint64_t>(p.row) << 32ull) +
			       p.col;  // no collisions for up to 32-bit coordinates, aka .contains = O(1)
#else
			return p.row ^ (p.col << 1);  // some collitions for 33+-bit coordinates, aka .contains slightly slower
#endif
		}
	};
}  // namespace std

#endif  // TYPES_H