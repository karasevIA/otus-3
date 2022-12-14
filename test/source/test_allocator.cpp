#include <gtest/gtest.h>

#include <include/my_allocator.hpp>

TEST(Allocator, VectorPushBack) {
	std::vector<int, My::Allocator<int>> vector;

    for (int i = 0; i < 1000; ++i) {
	 	vector.push_back(i);
    }

    int i = 0;
	for (const auto& v : vector) {
	 	EXPECT_EQ(i++, v);
    }
}

TEST(Allocator, CopyObject) {
    std::vector<int, My::Allocator<int>> vector;

    for (int i = 0; i < 1000; ++i) {
	 	vector.push_back(1);
    }

    {
        auto vector1 = vector;
        
        for (const auto& v1 : vector1) {
            EXPECT_EQ(v1, 1);
        }

        for (auto&& v : vector) {
            v = 2;
        }

        for (const auto& v1 : vector1) {
            EXPECT_EQ(1, v1);
        }
    }

	for (const auto& v : vector) {
	 	EXPECT_EQ(2, v);
    }
}
