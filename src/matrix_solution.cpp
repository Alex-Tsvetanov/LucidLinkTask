#include <vector>
#include "./cell.h"
#include "./spin_lock.h"

#ifndef MATRIX_SOLUTION_H
#define MATRIX_SOLUTION_H

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
					if (movements[i][0] + node.get_row() >= matrix.size()) continue;
					neibour.row = movements[i][0] + node.get_row();

					// Check if not going out-of-range horizontally
					if (movements[i][1] < 0 && node.get_col() < -movements[i][1]) continue;
					if (movements[i][1] + node.get_col() >= matrix[neibour.get_row()].size()) continue;
					neibour.col = movements[i][1] + node.get_col();

					// Check if the next cell is marked
					if (!matrix[neibour.get_row()][neibour.get_col()]) continue;

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
		size_t number_of_components(const std::list<cell>& marked_cells, const std::vector<std::vector<bool>>& matrix) {
			std::unordered_set<cell> visited;
			size_t answer = 0;
			for (const auto& marked_cell : marked_cells) {
				if (!visited.contains(marked_cell)) {
					visit_component(marked_cell, matrix, visited);
					answer++;
				}
			}
			return answer;
		}
	}  // namespace single_thread

	namespace multi_thread {
		/**
		 * @brief Breadth First Search (BFS) implmentation to find the component starting from a node
		 *
		 * @param node Starting node
		 * @param matrix The matrix with marked and unmarked cells
		 * @param visited Set of the already visited nodes in the current and previous components
		 * @return size_t Number of found components
		 */
		void visit_component(cell /*starting from*/ node, const std::vector<std::vector<bool>>& matrix,
		                     std::unordered_set<cell>& visited, spin_lock& is_visited_in_use) {
			static constexpr std::array<int32_t, 2> movements[] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
			static constexpr uint8_t neibours = sizeof(movements) / sizeof(movements[0]);
			std::queue<cell> q;
			q.push(node);
			is_visited_in_use.lock();
			if (!visited.contains(node)) return;
			visited.insert(node);
			is_visited_in_use.unlock();
			uint8_t i;
			cell neibour;
			while (!q.empty()) {
				node = q.front();
				q.pop();
				for (i = 0; i < neibours; i++) {
					// Check if not going out-of-range vertically
					if (movements[i][0] < 0 && node.get_row() < -movements[i][0]) continue;
					if (movements[i][0] + node.get_row() >= matrix.size()) continue;
					neibour.row = movements[i][0] + node.get_row();

					// Check if not going out-of-range horizontally
					if (movements[i][1] < 0 && node.get_col() < -movements[i][1]) continue;
					if (movements[i][1] + node.get_col() >= matrix[neibour.get_row()].size()) continue;
					neibour.col = movements[i][1] + node.get_col();

					// Check if the next cell is marked
					if (!matrix[neibour.get_row()][neibour.get_col()]) continue;

					is_visited_in_use.lock();
					// Check if the next cell is not already visited
					if (visited.contains(neibour)) continue;

					q.push(neibour);
					visited.insert(neibour);
					is_visited_in_use.unlock();
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
		size_t number_of_components(const std::list<cell>& marked_cells, const std::vector<std::vector<bool>>& matrix) {
			std::unordered_set<cell> visited;
			std::atomic<bool>& is_visited_in_use = false;
			size_t answer = 0;
			for (const auto& marked_cell : marked_cells) {
				while (is_visited_in_use)
					if (!visited.contains(marked_cell)) {
						visit_component(marked_cell, matrix, visited);
						answer++;
					}
			}
			return answer;
		}
	}  // namespace multi_thread

}  // namespace solution

#endif  // MATRIX_SOLUTION_H