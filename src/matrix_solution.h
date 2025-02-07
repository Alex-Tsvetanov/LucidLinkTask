#include <vector>
#include "./utils/cell.h"

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
		                     std::unordered_set<cell>& visited);

		/**
		 * @brief Single-threaded solution to the finding of the number of components of marked cells in a matrix
		 *
		 * @param matrix The matrix with marked and unmarked cells
		 * @return size_t Returns the number of components within the matrix
		 */
		size_t number_of_components(const std::vector<std::vector<bool>>& matrix);
	}  // namespace single_thread
}  // namespace solution

#endif  // MATRIX_SOLUTION_H