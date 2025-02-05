#ifndef TYPES_H
#define TYPES_H

#ifdef COORD_32BIT
using coord_t = uint32_t;
#else
using coord_t = uint64_t;
#endif

namespace solution {
	namespace single_thread {
		void visit_component(cell starting_from, const coord_t& total_rows, const coord_t& total_cols,
		                     std::unordered_set<cell>& visited);
		void visit_component(cell starting_from, const std::vector<std::vector<bool>>& matrix,
		                     std::unordered_set<cell>& visited);
	}  // namespace single_thread

	class cell {
		coord_t row;
		coord_t col;

	public:
		cell(coord_t _row, coord_t _col) : row(_row), col(_col) {}
		cell(std::pair<coord_t, coord_t> coords) : row(coords.first), col(coords.second) {}

		coord_t get_row() const { return row; }
		coord_t get_col() const { return col; }

		friend void single_thread::visit_component(cell starting_from, const coord_t& total_rows,
		                                           const coord_t& total_cols, std::unordered_set<cell>& visited);
		friend void single_thread::visit_component(cell starting_from, const std::vector<std::vector<bool>>& matrix,
		                                           std::unordered_set<cell>& visited);
	};
}  // namespace solution

namespace std {
	template <>
	struct hash<solution::cell> {
		size_t operator()(const solution::cell& p) const noexcept {
#ifdef COORD_32BIT
			return (static_cast<uint64_t>(p.get_row()) << 32ull) +
			       p.get_col();  // no collisions for up to 32-bit coordinates, aka .contains = O(1)
#else
			return hash<std::pair<coord_t, coord_t>>(
			    p.get_row(), p.get_col());  // some collitions for 33+-bit coordinates, aka .contains slightly slower
#endif
		}
	};
}  // namespace std

#endif  // TYPES_H