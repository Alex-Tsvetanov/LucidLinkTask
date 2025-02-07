#include <cstdint>
#include <utility>
#include <list>
#include <unordered_set>
#include <functional>
#include "./utils/cell.h"

#ifndef LIST_SOLUTION_H
#define LIST_SOLUTION_H

namespace solution {
	namespace single_thread {
		/**
		 * @brief Breadth First Search (BFS) implmentation to find the component starting from a node
		 *
		 * @param node Starting node
		 * @param marked_set Set of all marked nodes
		 * @param total_rows The number of rows in the matrix
		 * @param total_cols The number of columns in the matrix
		 * @param visited Set of the already visited nodes in the current and previous components
		 */
		void visit_component(cell /*starting from*/ node, const std::unordered_set<cell>& marked_set,
		                     const coord_t& total_rows, const coord_t& total_cols, std::unordered_set<cell>& visited);

		/**
		 * @brief Single-threaded solution to the finding of the number of components of marked cells in a matrix
		 *
		 * @param marked_cells List of the marked cells with their coordinates
		 * @param total_rows Number of the rows in the matrix
		 * @param total_cols Number of the columns in the matrix
		 * @return size_t Returns the number of components within the matrix
		 */
		size_t number_of_components(const std::list<cell>& marked_cells, const coord_t& total_rows,
		                            const coord_t& total_cols);
	}  // namespace single_thread

}  // namespace solution

#endif  // LIST_SOLUTION_H