#include "matrix_solution.h"
#include <queue>

namespace solution {
	namespace single_thread {
		/**
		 * @brief Breadth First Search (BFS) implmentation to find the component starting from a node
		 *
		 * @param node Starting node
		 * @param matrix The matrix with marked and unmarked cells
		 * @param visited Set of the already visited nodes in the current and previous components
		 */
		void visit_component(cell /*starting from*/ node, const std::vector<std::vector<bool>>& matrix,
		                     std::unordered_set<cell>& visited) {
			static constexpr int32_t movements[][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
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
					if (movements[i][0] < 0 && node.row < -movements[i][0]) continue;
					if (movements[i][0] + node.row >= matrix.size()) continue;
					neibour.row = movements[i][0] + node.row;

					// Check if not going out-of-range horizontally
					if (movements[i][1] < 0 && node.col < -movements[i][1]) continue;
					if (movements[i][1] + node.col >= matrix[neibour.row].size()) continue;
					neibour.col = movements[i][1] + node.col;

					// Check if the next cell is marked
					if (!matrix[neibour.row][neibour.col]) continue;

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
		 * @param matrix The matrix with marked and unmarked cells
		 * @return size_t Returns the number of components within the matrix
		 */
		size_t number_of_components(const std::vector<std::vector<bool>>& matrix) {
			std::unordered_set<cell> visited;
			size_t answer = 0, row, col;
			cell current;
			for (row = 0; row < matrix.size(); row++) {
				for (col = 0; col < matrix[row].size(); col++) {
					if (!matrix[row][col]) continue;
					current.row = row;
					current.col = col;
					if (!visited.contains(current)) {
						visit_component(current, matrix, visited);
						answer++;
					}
				}
			}
			return answer;
		}
	}  // namespace single_thread
}  // namespace solution