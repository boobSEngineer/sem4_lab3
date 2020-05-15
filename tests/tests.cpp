#include "gtest/gtest.h"
#include "../rb_map.h"
#include "../array.h"

// array tests
TEST(Array, MassiveAddAndClearTest) {
    Array<std::string> array;
    const int size = 10000;
    for (int i = 0; i < size; i++) {
        array.add("test_string");
    }
    ASSERT_EQ(array.length(), size);
    for (int i = 0; i < size; i++) {
        ASSERT_EQ(array[i], "test_string");
    }
    array.clear();
    ASSERT_EQ(array.length(), 0);
}

// keep some tests for maps
TEST (Map, InsertionTest) {
    RbMap<int, int> map;
    map.insert(1, 2);
    map.insert(1, 3);
    map.insert(2, 4);
    map.insert(3, 10);
    ASSERT_EQ(map.get_length(), 3);
    ASSERT_EQ(map.get_length(), map.get_keys().get_length());
    ASSERT_EQ(map.get_length(), map.get_values().get_length());
}

TEST(Map, InsertAndClearTest) {
    RbMap<int, int> map;
    map.insert(1, 2);
    map.insert(1, 3);
    map.insert(2, 4);
    map.insert(3, 10);
    map.clear();
    ASSERT_EQ(map.get_length(), 0);
    ASSERT_EQ(map.get_length(), map.get_keys().get_length());
    ASSERT_EQ(map.get_length(), map.get_values().get_length());
}
