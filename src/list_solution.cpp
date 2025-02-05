#include <cstdint>
#include <utility>
#include <list>
#include <unordered_map>
#include <functional>
#include "./cell.h"
#include "./list_solution.h"

namespace solution {
	namespace single_thread {
		/**
		 * @brief Breadth First Search (BFS) implmentation to find the component starting from a node
		 *
		 * @param node Starting node
		 * @param total_rows The number of rows in the matrix
		 * @param total_cols The number of columns in the matrix
		 * @param visited Set of the already visited nodes in the current and previous components
		 */
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
					// Check if not going out-of-range vertically
					if (movements[i][0] < 0 && node.get_row() < -movements[i][0]) continue;
					if (movements[i][0] + node.get_row() >= total_rows) continue;

					// Check if not going out-of-range horizontally
					if (movements[i][1] < 0 && node.get_col() < -movements[i][1]) continue;
					if (movements[i][1] + node.get_col() >= total_cols) continue;

					// Initialize the cell object for the next cell's coordinates
					neibour.row = movements[i][0] + node.get_row();
					neibour.col = movements[i][1] + node.get_col();

					// Check if the next cell is not already visited
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
					visit_component(marked_cell, total_rows, total_cols, visited);
					answer++;
				}
			}
			return answer;
		}
	}  // namespace single_thread

}  // namespace solution

#endif  // LIST_SOLUTION_H