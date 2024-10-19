#include "pch.h"

// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
// #include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// Unit test to verify that reserve increases capacity without changing the size
TEST_F(CollectionTest, ReserveIncreasesCapacityWithoutChangingSize)
{
    add_entries(5);  // Adding 5 elements to the collection

    // Store current capacity before reserving new space
    auto old_capacity = collection->capacity();  
    collection->reserve(10);  // Reserve space for 10 elements
    EXPECT_GT(collection->capacity(), old_capacity);  // Ensure capacity increased
    EXPECT_EQ(collection->size(), 5);  // Ensure size remains the same (5 elements)
}

// Unit test to verify that accessing out-of-bounds throws std::out_of_range exception
TEST_F(CollectionTest, AccessOutOfBoundsThrowsException)
{
    add_entries(1);  // Add a single entry to the collection

    // Access index 5 (out of bounds), expect exception
    EXPECT_THROW(collection->at(5), std::out_of_range);  

    // Access negative index, expect exception
    EXPECT_THROW(collection->at(-1), std::out_of_range); 
}

// Unit test to verify that duplicate values can be added to the collection
TEST_F(CollectionTest, CanAddDuplicateValues)
{
    collection->push_back(42);  // Add the value 42
    collection->push_back(42);  // Add the value 42 again (duplicate)
    ASSERT_EQ(collection->size(), 2);  // Ensure collection size is 2
    EXPECT_EQ(collection->at(0), 42);  // First element should be 42
    EXPECT_EQ(collection->at(1), 42);  // Second element should be 42 (duplicate)
}

// Unit test to verify that accessing an empty collection 
//  throws std::out_of_range exception
TEST_F(CollectionTest, AccessEmptyCollectionThrowsException)
{
    ASSERT_TRUE(collection->empty());  // Ensure the collection is empty

    // Try accessing element 0, expect exception
    EXPECT_THROW(collection->at(0), std::out_of_range);  
}