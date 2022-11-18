#include <gtest/gtest.h>
#include <SubStringSearch/SubStringSearch.h>

using namespace std;

TEST(RabinKarp, True)
{
    ASSERT_EQ(RabinKarpSearch("qwertyuiop", "qwe"), 0);
    ASSERT_EQ(RabinKarpSearch("qwertyuiop", "tyu"), 4);
    ASSERT_EQ(RabinKarpSearch("qwertyuiop", "iop"), 7);
    ASSERT_EQ(RabinKarpSearch("qwertyuiop", "q"), 0);
    ASSERT_EQ(RabinKarpSearch("qwertyuiop", "p"), 9);
    ASSERT_EQ(RabinKarpSearch("qwertyuiop", "qwertyuiop"), 0);
}

TEST(RabinKarp, False)
{
    ASSERT_EQ(RabinKarpSearch("qwertyuiop", "a"), -1);
    ASSERT_EQ(RabinKarpSearch("qwertyuiop", "fdsd"), -1);
}

TEST(KnuthMorrisPratt, True)
{
    ASSERT_EQ(KnuthMorrisPrattSearch("qwertyuiop", "qwe"), 0);
    ASSERT_EQ(KnuthMorrisPrattSearch("qwertyuiop", "tyu"), 4);
    ASSERT_EQ(KnuthMorrisPrattSearch("qwertyuiop", "iop"), 7);
    ASSERT_EQ(KnuthMorrisPrattSearch("qwertyuiop", "q"), 0);
    ASSERT_EQ(KnuthMorrisPrattSearch("qwertyuiop", "p"), 9);
    ASSERT_EQ(KnuthMorrisPrattSearch("qwertyuiop", "qwertyuiop"), 0);
}

TEST(KnuthMorrisPratt, False)
{
    ASSERT_EQ(KnuthMorrisPrattSearch("qwertyuiop", "a"), -1);
    ASSERT_EQ(KnuthMorrisPrattSearch("qwertyuiop", "fdsd"), -1);
}

TEST(BoyerMoore, True)
{
    ASSERT_EQ(BoyerMooreSearch("qwertyuiop", "qwe"), 0);
    ASSERT_EQ(BoyerMooreSearch("qwertyuiop", "tyu"), 4);
    ASSERT_EQ(BoyerMooreSearch("qwertyuiop", "iop"), 7);
    ASSERT_EQ(BoyerMooreSearch("qwertyuiop", "q"), 0);
    ASSERT_EQ(BoyerMooreSearch("qwertyuiop", "p"), 9);
    ASSERT_EQ(BoyerMooreSearch("qwertyuiop", "qwertyuiop"), 0);
}

TEST(BoyerMoore, False)
{
    ASSERT_EQ(BoyerMooreSearch("qwertyuiop", "a"), -1);
    ASSERT_EQ(BoyerMooreSearch("qwertyuiop", "fdsd"), -1);
}