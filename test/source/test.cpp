// grid_test.cpp
#include <gtest/gtest.h>
#include "grid.cpp"

class GridTest : public ::testing::Test {
};

TEST_F(GridTest, LoadGridFromFile) {
    Grid grid;
    grid.loadGridFromFile("../../assets/easy.txt", 0);
    EXPECT_EQ(grid.getCellValue(0, 0), 7); 
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}