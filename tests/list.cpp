#include <gtest/gtest.h>
#include <list_solution.h>

namespace solution {
	namespace single_thread {
		TEST(ListComponentTests, EmptyGrid) {
			std::list<cell> marked_cells;
			coord_t total_rows = 5;
			coord_t total_cols = 5;
			EXPECT_EQ(number_of_components(marked_cells, total_rows, total_cols), 0);
		}

		TEST(ListComponentTests, SingleComponent) {
			std::list<cell> marked_cells = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
			coord_t total_rows = 5;
			coord_t total_cols = 5;
			EXPECT_EQ(number_of_components(marked_cells, total_rows, total_cols), 1);
		}

		TEST(ListComponentTests, MultipleComponents) {
			std::list<cell> marked_cells = {{0, 0}, {0, 1}, {2, 2}, {2, 3}};
			coord_t total_rows = 5;
			coord_t total_cols = 5;
			EXPECT_EQ(number_of_components(marked_cells, total_rows, total_cols), 2);
		}

		TEST(ListComponentTests, LargeGrid) {
			std::list<cell> marked_cells;
			coord_t total_rows = 100;
			coord_t total_cols = 100;
			for (coord_t i = 0; i < 50; ++i) {
				marked_cells.push_back({i, i});
			}
			EXPECT_EQ(number_of_components(marked_cells, total_rows, total_cols), 50);
		}

		TEST(ListComponentTests, OutOfBounds) {
			std::list<cell> marked_cells = {{0, 0}, {5, 0}};  // Invalid row
			coord_t total_rows = 5;
			coord_t total_cols = 5;
			// Your function should handle out-of-bounds gracefully.  This test checks that it doesn't crash.
			// You might want to add more specific checks depending on how you want to handle out of bounds.
			number_of_components(marked_cells, total_rows, total_cols);  // Should not throw an error
		}
	}  // namespace single_thread
}  // namespace solution
