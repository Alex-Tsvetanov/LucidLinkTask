#include <cstdint>
#include <utility>
#include <list>
#include <unordered_map>
#include <functional>
#include "./types.h"

#ifndef LIST_SOLUTION_H
#define LIST_SOLUTION_H

namespace solution {
	namespace single_thread {
		void visit_component(cell starting_from, const coord_t& total_rows, const coord_t& total_cols,
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
	};
}  // namespace solution

namespace std {
	template <>
	struct hash<solution::cell> {
		size_t operator()(const solution::cell& p) const noexcept {
#ifdef JUST_MILLIONS
			return (static_cast<uint64_t>(p.get_row()) << 32ull) +
			       p.get_col();  // no collisions for up to 32-bit coordinates
#else
			return hash<std::pair<coord_t, coord_t> >(p.get_row(), p.get_col());
#endif
		}
	};
}  // namespace std

namespace solution {
	namespace single_thread {
		void visit_component(cell /*starting from*/ node, const coord_t& total_rows, const coord_t& total_cols,
		                     std::unordered_set<cell>& visited) {
			static constexpr std::array<int32_t, 2> movements[] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
			static constexpr uint8_t neibours = sizeof(movements) / sizeof(movements[0]);
			std::queue<cell> q;
			q.push(node);
			visited.insert(node);
			uint8_t i;
			cell neibour;
			while (!q.empty()) {
				node = q.front();
				q.pop();
				for (i = 0; i < neibours; i++) {
					if (movements[i][0] < 0 && node.get_row() == 0) continue;
					if (movements[i][1] < 0 && node.get_col() == 0) continue;
					if (movements[i][0] + node.get_row() >= total_rows) continue;
					if (movements[i][1] + node.get_col() >= total_cols) continue;
					neibour.row = movements[i][0] + node.get_row();
					neibour.col = movements[i][1] + node.get_col();
					if (visited.contains(neibour)) continue;
					q.push(neibour);
					visited.insert(neibour);
				}
			}
		}

		/**
		 * @brief Single-threaded solution to the finding of the number of components of marked cells in a matrix
		 *
		 * @param marked_cells List of the marked cells with their coordinates
		 * @param total_rows Number of the rows in the matrix
		 * @param total_cols Number of the columns in the matrix
		 * @return size_t Returns the number of components within the matrix
		 */
		size_t number_of_components(const std::list<cell>& marked_cells, const coord_t& total_rows,
		                            const coord_t& total_cols) {
			std::unordered_set<cell> visited;
			size_t answer = 0;
			for (const auto& marked_cell : marked_cells) {
				if (!visited.contains(marked_cell)) {
					visit_component(marked_cell, total_rows, total_cols visited);
					answer++;
				}
			}
			return answer;
		}
	}  // namespace single_thread

}  // namespace solution

#endif  // LIST_SOLUTION_H