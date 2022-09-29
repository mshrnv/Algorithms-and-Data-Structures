#include <gtest/gtest.h>
#include <HashTable/HashTable.h>
#include <iostream>

using namespace std;

TEST(HashTable, DefaultConstructor)
{
    HashTable<int> ht;
    ASSERT_EQ(ht.GetCapacity(), 5);
    ASSERT_EQ(ht.GetSize(), 0);
}

TEST(HashTable, ParametersConstructor)
{
    HashTable<int> ht(3);
    ASSERT_EQ(ht.GetCapacity(), 3);
    ASSERT_EQ(ht.GetSize(), 0);
}

TEST(HashTable, InsertNoCollisions)
{
    HashTable<int> ht;

    ht.Insert(7);
    ht.Insert(10);
    ht.Insert(113);

    ht.Print();
}

TEST(HashTable, InsertWithCollisions)
{
    HashTable<int> ht;

    ht.Insert(8);
    ht.Insert(48);
    ht.Insert(13);

    ht.Print();
}

TEST(HashTable, InsertWithRehash)
{
    HashTable<int> ht;

    for (int i = 0; i < 10; ++i) {
        ht.Insert(rand() % 10000);
    }

    ht.Print();
    ASSERT_EQ(ht.GetSize(), 10);
    ASSERT_EQ(ht.GetCapacity(), 20);
}

TEST(HashTable, Remove)
{
    HashTable<int> ht;

    ht.Insert(4);
    ht.Insert(0);
    ht.Insert(2);

    ASSERT_FALSE(ht.Remove(3));
    ASSERT_TRUE(ht.Remove(4));
    ASSERT_TRUE(ht.Remove(2));

    ht.Print();
}

TEST(HashTable, Contains)
{
    HashTable<int> ht;

    ht.Insert(4);
    ht.Insert(0);
    ht.Insert(2);

    ASSERT_FALSE(ht.Contains(3));
    ASSERT_TRUE(ht.Contains(4));
    ASSERT_TRUE(ht.Contains(2));
    ASSERT_TRUE(ht.Contains(0));

    ht.Print();
}

TEST(HashTable, IndexOperator)
{
    HashTable<int> ht;

    ht.Insert(1);
    ht.Insert(3);
    ht.Insert(5);

    ASSERT_EQ(ht[ht.FindIndex(1)], 1);
    ASSERT_EQ(ht[ht.FindIndex(3)], 3);
    ASSERT_EQ(ht[ht.FindIndex(5)], 5);

    ASSERT_EQ(ht.FindIndex(2), -1);
}

TEST(HashTable, BigDataStress)
{
    HashTable<int> ht;

    for (int i = 0; i < 10000; ++i) {
        ht.Insert(rand() % 10000);
    }

    ht.Print();
}