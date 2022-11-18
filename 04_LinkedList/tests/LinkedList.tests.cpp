#include <gtest/gtest.h>
#include "LinkedList/LinkedList.h"
#include <iostream>
#include <algorithm>

using namespace std;

class LinkedListTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        intList = new LinkedList<int>();
        charList = new LinkedList<char>();

        intList->PushBack(11);
        intList->PushBack(3);
        intList->PushBack(19);
        intList->PushBack(-5);
        intList->PushBack(100);

        charList->PushBack('a');
        charList->PushBack('b');
        charList->PushBack('c');
        charList->PushBack('d');
    }

    virtual void TearDown()
    {
        delete intList;
        delete charList;
    }

    LinkedList<int>* intList;
    LinkedList<char>* charList;
};

TEST_F(LinkedListTest, DefaultСonstructor)
{
    LinkedList<int> list = LinkedList<int>();
}

TEST_F(LinkedListTest, CopyConstructor)
{
    LinkedList<int>* list = new LinkedList<int>(*intList);
    ASSERT_TRUE(*list == *intList);
}

TEST_F(LinkedListTest, CopyOperator)
{
    LinkedList<int> list(*intList);
    ASSERT_TRUE(list == *intList);
}

TEST_F(LinkedListTest, EqualityOperator)
{
    LinkedList<int> list;
    list.PushBack(11);
    list.PushBack(3);
    list.PushBack(19);
    list.PushBack(-5);
    ASSERT_FALSE(list == *intList);

    list.PushBack(100);
    ASSERT_TRUE(list == *intList);
}

TEST_F(LinkedListTest, Begin)
{
    ASSERT_EQ(intList->begin()._item->_value, 11);
    ASSERT_EQ(charList->begin()._item->_value, 'a');
}

TEST_F(LinkedListTest, End)
{
    ASSERT_EQ(intList->end()._item->_value, 0);
    ASSERT_EQ(charList->end()._item->_value, '\0');

    ASSERT_EQ(intList->end()._item->_prev->_value, 100);
    ASSERT_EQ(charList->end()._item->_prev->_value, 'd');
}

TEST_F(LinkedListTest, RBegin)
{
    ASSERT_EQ(*intList->rbegin(), 100);
    ASSERT_EQ(charList->rbegin()._item->_value, 'd');
}

TEST_F(LinkedListTest, REnd)
{
    ASSERT_EQ(intList->rend()._item->_value, 0);
    ASSERT_EQ(charList->rend()._item->_value, '\0');

    ASSERT_EQ(intList->rend()._item->_next->_value, 11);
    ASSERT_EQ(charList->rend()._item->_next->_value, 'a');
}

TEST_F(LinkedListTest, IndexOperator)
{
    ASSERT_EQ(intList->operator[](0), 11);
    ASSERT_EQ(intList->operator[](1), 3);
    ASSERT_EQ(intList->operator[](2), 19);
    ASSERT_EQ(intList->operator[](3), -5);
    ASSERT_EQ(intList->operator[](4), 100);

    ASSERT_EQ(charList->operator[](0), 'a');
    ASSERT_EQ(charList->operator[](1), 'b');
    ASSERT_EQ(charList->operator[](2), 'c');
    ASSERT_EQ(charList->operator[](3), 'd');
}

TEST_F(LinkedListTest, GetSize)
{
    ASSERT_EQ(intList->GetSize(), 5);
    ASSERT_EQ(charList->GetSize(), 4);
}

TEST_F(LinkedListTest, IsEmpty)
{
    LinkedList<int> list;
    ASSERT_TRUE(list.IsEmpty());

    list.PushBack(0);
    ASSERT_FALSE(list.IsEmpty());
}

TEST_F(LinkedListTest, PushBackInt)
{
    LinkedList<int> list;
    ASSERT_TRUE(list.IsEmpty());
    ASSERT_EQ(list.GetSize(), 0);

    list.PushBack(15);
    ASSERT_FALSE(list.IsEmpty());
    ASSERT_EQ(list.GetSize(), 1);

    list.PushBack(10000);
    ASSERT_FALSE(list.IsEmpty());
    ASSERT_EQ(list.GetSize(), 2);

    ASSERT_EQ(list.operator[](0), 15);
    ASSERT_EQ(list.operator[](1), 10000);
}

TEST_F(LinkedListTest, PushBackChar)
{
    LinkedList<char> list;
    ASSERT_TRUE(list.IsEmpty());
    ASSERT_EQ(list.GetSize(), 0);

    list.PushBack('q');
    ASSERT_FALSE(list.IsEmpty());
    ASSERT_EQ(list.GetSize(), 1);

    list.PushBack('w');
    ASSERT_FALSE(list.IsEmpty());
    ASSERT_EQ(list.GetSize(), 2);

    ASSERT_EQ(list.operator[](0), 'q');
    ASSERT_EQ(list.operator[](1), 'w');
}

TEST_F(LinkedListTest, PushFrontInt)
{
    LinkedList<int> list;
    ASSERT_TRUE(list.IsEmpty());
    ASSERT_EQ(list.GetSize(), 0);

    list.PushFront(-33);
    ASSERT_FALSE(list.IsEmpty());
    ASSERT_EQ(list.GetSize(), 1);

    list.PushFront(99);
    ASSERT_FALSE(list.IsEmpty());
    ASSERT_EQ(list.GetSize(), 2);

    ASSERT_EQ(list.operator[](0), 99);
    ASSERT_EQ(list.operator[](1), -33);
}

TEST_F(LinkedListTest, PushFrontChar)
{
    LinkedList<char> list;
    ASSERT_TRUE(list.IsEmpty());
    ASSERT_EQ(list.GetSize(), 0);

    list.PushFront('p');
    ASSERT_FALSE(list.IsEmpty());
    ASSERT_EQ(list.GetSize(), 1);

    list.PushFront('m');
    ASSERT_FALSE(list.IsEmpty());
    ASSERT_EQ(list.GetSize(), 2);

    ASSERT_EQ(list.operator[](0), 'm');
    ASSERT_EQ(list.operator[](1), 'p');
}

TEST_F(LinkedListTest, EraseInt)
{
    ASSERT_EQ(intList->GetSize(), 5);

    intList->Erase(intList->begin());
    ASSERT_EQ(intList->GetSize(), 4);
    ASSERT_EQ(intList->operator[](0), 3);

    intList->Erase(--intList->end());
    ASSERT_EQ(intList->GetSize(), 3);
    ASSERT_EQ(intList->operator[](2), -5);
}

TEST_F(LinkedListTest, EraseChar)
{
    ASSERT_EQ(charList->GetSize(), 4);

    charList->Erase(charList->begin());
    ASSERT_EQ(charList->GetSize(), 3);
    ASSERT_EQ(charList->operator[](0), 'b');

    charList->Erase(--charList->end());
    ASSERT_EQ(charList->GetSize(), 2);
    ASSERT_EQ(charList->operator[](1), 'c');
}

TEST_F(LinkedListTest, RemoveInt)
{
    ASSERT_EQ(intList->GetSize(), 5);

    intList->Remove(19);
    ASSERT_EQ(intList->GetSize(), 4);
    ASSERT_EQ(intList->operator[](2), -5);
}

TEST_F(LinkedListTest, RemoveChar)
{
    ASSERT_EQ(charList->GetSize(), 4);

    charList->Remove('b');
    ASSERT_EQ(charList->GetSize(), 3);
    ASSERT_EQ(charList->operator[](1), 'c');
}

TEST_F(LinkedListTest, Reverse)
{
    LinkedList<int> reversed;
    intList->Reverse();
    reversed = *intList;
    ASSERT_EQ(reversed.GetSize(), intList->GetSize());

    intList->Reverse();
    ASSERT_FALSE(reversed == *intList);

    reversed = *intList;
    ASSERT_EQ(reversed.GetSize(), intList->GetSize());
    ASSERT_TRUE(reversed == *intList);
}

TEST_F(LinkedListTest, Iterator)
{
    auto it = intList->begin();
    for (; it != intList->end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

TEST_F(LinkedListTest, ReverseIteartor)
{
    auto it = intList->rbegin();
    for (; it != intList->rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

TEST_F(LinkedListTest, STD_Algorithm_max_element)
{
    auto it = std::max_element(intList->begin(), intList->end());
    ASSERT_EQ(*it, 100);
}