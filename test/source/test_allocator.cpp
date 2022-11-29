#include <gtest/gtest.h>

#include <include/my_allocator.hpp>


TEST(Allocator, VectorPushBack) {
	std::vector<int, My::Allocator<int>> vector;

    for (int i = 0; i < 10; ++i) {
	 	vector.push_back(i);
    }

    int i = 0;
	for (const auto& v : vector) {
	 	EXPECT_EQ(i++, v);
    }
}