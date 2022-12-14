#include <gtest/gtest.h>

#include <include/my_container.hpp>

TEST(Container, Create) {
	My::Container<int> cont;

    for (int i = 0; i < 1000; ++i) {
        cont.push_back(i);
    }

    int i = 0;
    for (auto& c : cont) {
        EXPECT_EQ(c, i++);
    }
}
