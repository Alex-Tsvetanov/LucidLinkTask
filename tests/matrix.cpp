#include "gtest/gtest.h"
#include "matrix_solution.h"

namespace solution {
	namespace single_thread {
		TEST(MatrixComponentTests, EmptyMatrix) {
			std::vector<std::vector<bool>> matrix;
			EXPECT_EQ(number_of_components(matrix), 0);
		}

		TEST(MatrixComponentTests, SingleComponent) {
			std::vector<std::vector<bool>> matrix = {{true, true, false}, {true, true, false}, {false, false, false}};
			EXPECT_EQ(number_of_components(matrix), 1);
		}

		TEST(MatrixComponentTests, MultipleComponents) {
			std::vector<std::vector<bool>> matrix = {{true, true, false}, {false, false, false}, {false, true, true}};
			EXPECT_EQ(number_of_components(matrix), 2);
		}

		TEST(MatrixComponentTests, LargeMatrix) {
			std::vector<std::vector<bool>> matrix(100, std::vector<bool>(100, false));
			for (coord_t i = 0; i < 50; ++i) {
				matrix[i][i] = true;
			}
			EXPECT_EQ(number_of_components(matrix), 50);  // diagonal is not a component
		}

		TEST(MatrixComponentTests, OutOfBounds) {
			std::vector<std::vector<bool>> matrix = {
			    {true, false, false}, {false, false, false}, {false, false, false}};
			number_of_components(matrix);  // Should not throw an error
		}
	}  // namespace single_thread
}  // namespace solution
