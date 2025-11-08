#include <gtest/gtest.h>
#include <limits>
#include <stdexcept>
#include "pch.h"
#include "LongInt.h"

using namespace std;

class LongIntTest : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    LongInt zero;
    LongInt one{ "1" };
    LongInt minus_one{ "-1" };
    LongInt large_positive{ "12345678901234567890" };
    LongInt large_negative{ "-12345678901234567890" };
    LongInt max_int{ to_string(numeric_limits<int>::max()) };
    LongInt min_int{ to_string(numeric_limits<int>::min()) };
};

TEST_F(LongIntTest, DefaultConstructor) {
    EXPECT_EQ(zero.toString(), "0");
    EXPECT_TRUE(zero.isZero());
}

TEST_F(LongIntTest, StringConstructorPositive) {
    LongInt num{ "12345" };
    EXPECT_EQ(num.toString(), "12345");
}

TEST_F(LongIntTest, StringConstructorNegative) {
    LongInt num{ "-12345" };
    EXPECT_EQ(num.toString(), "-12345");
}

TEST_F(LongIntTest, StringConstructorWithLeadingZeros) {
    LongInt num{ "000123" };
    EXPECT_EQ(num.toString(), "123");
}

TEST_F(LongIntTest, StringConstructorZero) {
    LongInt num{ "0000" };
    EXPECT_EQ(num.toString(), "0");
}

TEST_F(LongIntTest, IntConstructorPositive) {
    LongInt num{ 12345 };
    EXPECT_EQ(num.toString(), "12345");
}

TEST_F(LongIntTest, IntConstructorNegative) {
    LongInt num{ -12345 };
    EXPECT_EQ(num.toString(), "-12345");
}

TEST_F(LongIntTest, IntConstructorZero) {
    LongInt num{ 0 };
    EXPECT_EQ(num.toString(), "0");
}

TEST_F(LongIntTest, CopyConstructor) {
    LongInt original{ "123456789" };
    LongInt copy{ original };
    EXPECT_EQ(copy.toString(), "123456789");
    EXPECT_EQ(original.toString(), "123456789");
}

TEST_F(LongIntTest, AssignmentOperator) {
    LongInt a{ "123" };
    LongInt b{ "456" };
    a = b;
    EXPECT_EQ(a.toString(), "456");
    EXPECT_EQ(b.toString(), "456");
}

TEST_F(LongIntTest, SelfAssignment) {
    LongInt a{ "123" };
    a = a;
    EXPECT_EQ(a.toString(), "123");
}

TEST_F(LongIntTest, EqualityOperator) {
    LongInt a{ "123" };
    LongInt b{ "123" };
    LongInt c{ "456" };
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
    EXPECT_TRUE(zero == zero);
}

TEST_F(LongIntTest, InequalityOperator) {
    LongInt a{ "123" };
    LongInt b{ "456" };
    EXPECT_TRUE(a != b);
    EXPECT_FALSE(a != a);
}

TEST_F(LongIntTest, LessThanOperator) {
    LongInt a{ "123" };
    LongInt b{ "456" };
    LongInt c{ "-100" };
    EXPECT_TRUE(a < b);
    EXPECT_TRUE(c < a);
    EXPECT_TRUE(c < zero);
    EXPECT_FALSE(b < a);
}

TEST_F(LongIntTest, GreaterThanOperator) {
    LongInt a{ "123" };
    LongInt b{ "456" };
    EXPECT_TRUE(b > a);
    EXPECT_FALSE(a > b);
}

TEST_F(LongIntTest, LessThanOrEqualOperator) {
    LongInt a{ "123" };
    LongInt b{ "123" };
    LongInt c{ "456" };
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(a <= c);
    EXPECT_FALSE(c <= a);
}

TEST_F(LongIntTest, GreaterThanOrEqualOperator) {
    LongInt a{ "123" };
    LongInt b{ "123" };
    LongInt c{ "456" };
    EXPECT_TRUE(a >= b);
    EXPECT_TRUE(c >= a);
    EXPECT_FALSE(a >= c);
}

TEST_F(LongIntTest, AdditionPositiveNumbers) {
    LongInt a{ "123" };
    LongInt b{ "456" };
    LongInt result = a + b;
    EXPECT_EQ(result.toString(), "579");
}

TEST_F(LongIntTest, AdditionMixedSign) {
    LongInt a{ "100" };
    LongInt b{ "-50" };
    LongInt result = a + b;
    EXPECT_EQ(result.toString(), "50");
}

TEST_F(LongIntTest, AdditionBothNegative) {
    LongInt a{ "-100" };
    LongInt b{ "-50" };
    LongInt result = a + b;
    EXPECT_EQ(result.toString(), "-150");
}

TEST_F(LongIntTest, SubtractionPositiveNumbers) {
    LongInt a{ "456" };
    LongInt b{ "123" };
    LongInt result = a - b;
    EXPECT_EQ(result.toString(), "333");
}

TEST_F(LongIntTest, SubtractionNegativeResult) {
    LongInt a{ "100" };
    LongInt b{ "200" };
    LongInt result = a - b;
    EXPECT_EQ(result.toString(), "-100");
}

TEST_F(LongIntTest, SubtractionMixedSign) {
    LongInt a{ "100" };
    LongInt b{ "-50" };
    LongInt result = a - b;
    EXPECT_EQ(result.toString(), "150");
}

TEST_F(LongIntTest, MultiplicationPositiveNumbers) {
    LongInt a{ "12" };
    LongInt b{ "34" };
    LongInt result = a * b;
    EXPECT_EQ(result.toString(), "408");
}

TEST_F(LongIntTest, MultiplicationMixedSign) {
    LongInt a{ "12" };
    LongInt b{ "-34" };
    LongInt result = a * b;
    EXPECT_EQ(result.toString(), "-408");
}

TEST_F(LongIntTest, MultiplicationBothNegative) {
    LongInt a{ "-12" };
    LongInt b{ "-34" };
    LongInt result = a * b;
    EXPECT_EQ(result.toString(), "408");
}

TEST_F(LongIntTest, MultiplicationByZero) {
    LongInt a{ "123456" };
    LongInt result = a * zero;
    EXPECT_EQ(result.toString(), "0");
}

TEST_F(LongIntTest, DivisionPositiveNumbers) {
    LongInt a{ "100" };
    LongInt b{ "25" };
    LongInt result = a / b;
    EXPECT_EQ(result.toString(), "4");
}

TEST_F(LongIntTest, DivisionWithRemainder) {
    LongInt a{ "100" };
    LongInt b{ "30" };
    LongInt result = a / b;
    EXPECT_EQ(result.toString(), "3");
}

TEST_F(LongIntTest, DivisionMixedSign) {
    LongInt a{ "100" };
    LongInt b{ "-25" };
    LongInt result = a / b;
    EXPECT_EQ(result.toString(), "-4");
}

TEST_F(LongIntTest, DivisionByZeroThrows) {
    LongInt a{ "100" };
    EXPECT_THROW(a / zero, invalid_argument);
}

TEST_F(LongIntTest, AdditionAssignment) {
    LongInt a{ "100" };
    LongInt b{ "50" };
    a += b;
    EXPECT_EQ(a.toString(), "150");
}

TEST_F(LongIntTest, SubtractionAssignment) {
    LongInt a{ "100" };
    LongInt b{ "50" };
    a -= b;
    EXPECT_EQ(a.toString(), "50");
}

TEST_F(LongIntTest, MultiplicationAssignment) {
    LongInt a{ "10" };
    LongInt b{ "20" };
    a *= b;
    EXPECT_EQ(a.toString(), "200");
}

TEST_F(LongIntTest, DivisionAssignment) {
    LongInt a{ "100" };
    LongInt b{ "25" };
    a /= b;
    EXPECT_EQ(a.toString(), "4");
}

TEST_F(LongIntTest, PrefixIncrement) {
    LongInt a{ "10" };
    LongInt result = ++a;
    EXPECT_EQ(a.toString(), "11");
    EXPECT_EQ(result.toString(), "11");
}

TEST_F(LongIntTest, PostfixIncrement) {
    LongInt a{ "10" };
    LongInt result = a++;
    EXPECT_EQ(a.toString(), "11");
    EXPECT_EQ(result.toString(), "10");
}

TEST_F(LongIntTest, PrefixDecrement) {
    LongInt a{ "10" };
    LongInt result = --a;
    EXPECT_EQ(a.toString(), "9");
    EXPECT_EQ(result.toString(), "9");
}

TEST_F(LongIntTest, PostfixDecrement) {
    LongInt a{ "10" };
    LongInt result = a--;
    EXPECT_EQ(a.toString(), "9");
    EXPECT_EQ(result.toString(), "10");
}

TEST_F(LongIntTest, ToStringMethod) {
    LongInt a{ "12345" };
    EXPECT_EQ(a.toString(), "12345");
    LongInt b{ "-12345" };
    EXPECT_EQ(b.toString(), "-12345");
}

TEST_F(LongIntTest, IsZeroMethod) {
    EXPECT_TRUE(zero.isZero());
    LongInt a{ "0" };
    EXPECT_TRUE(a.isZero());
    LongInt b{ "1" };
    EXPECT_FALSE(b.isZero());
    LongInt c{ "-1" };
    EXPECT_FALSE(c.isZero());
}

TEST_F(LongIntTest, IntConversion) {
    LongInt a{ "12345" };
    EXPECT_EQ(static_cast<int>(a), 12345);
    LongInt b{ "-12345" };
    EXPECT_EQ(static_cast<int>(b), -12345);
    LongInt c{ 0 };
    EXPECT_EQ(static_cast<int>(c), 0);
}

TEST_F(LongIntTest, IntConversionLargeNumber) {
    LongInt a{ to_string(numeric_limits<int>::max()) };
    EXPECT_EQ(static_cast<int>(a), numeric_limits<int>::max());
}

TEST_F(LongIntTest, OutputStreamOperator) {
    LongInt a{ "12345" };
    ostringstream oss;
    oss << a;
    EXPECT_EQ(oss.str(), "12345");
}

TEST_F(LongIntTest, InputStreamOperator) {
    istringstream iss("12345");
    LongInt a;
    iss >> a;
    EXPECT_EQ(a.toString(), "12345");
}

TEST_F(LongIntTest, AdditionWithInt) {
    LongInt a{ "100" };
    LongInt result = a + 50;
    EXPECT_EQ(result.toString(), "150");
}

TEST_F(LongIntTest, SubtractionWithInt) {
    LongInt a{ "100" };
    LongInt result = a - 50;
    EXPECT_EQ(result.toString(), "50");
}

TEST_F(LongIntTest, MultiplicationWithInt) {
    LongInt a{ "10" };
    LongInt result = a * 5;
    EXPECT_EQ(result.toString(), "50");
}

TEST_F(LongIntTest, DivisionWithInt) {
    LongInt a{ "100" };
    LongInt result = a / 25;
    EXPECT_EQ(result.toString(), "4");
}

TEST_F(LongIntTest, ComparisonWithInt) {
    LongInt a{ "100" };
    EXPECT_TRUE(a == 100);
    EXPECT_TRUE(a > 50);
    EXPECT_TRUE(a < 150);
}

TEST_F(LongIntTest, VeryLargeNumbers) {
    LongInt a{ "123456789012345678901234567890" };
    LongInt b{ "987654321098765432109876543210" };
    LongInt result = a + b;
    EXPECT_EQ(result.toString(), "1111111110111111111011111111100");
}

TEST_F(LongIntTest, AdditionCarryOverflow) {
    LongInt a{ "999" };
    LongInt b{ "1" };
    LongInt result = a + b;
    EXPECT_EQ(result.toString(), "1000");
}

TEST_F(LongIntTest, SubtractionBorrow) {
    LongInt a{ "1000" };
    LongInt b{ "1" };
    LongInt result = a - b;
    EXPECT_EQ(result.toString(), "999");
}

TEST_F(LongIntTest, MultiplicationLarge) {
    LongInt a{ "123456789" };
    LongInt b{ "987654321" };
    LongInt result = a * b;
    EXPECT_EQ(result.toString(), "121932631112635269");
}

TEST_F(LongIntTest, DivisionLarge) {
    LongInt a{ "121932631112635269" };
    LongInt b{ "123456789" };
    LongInt result = a / b;
    EXPECT_EQ(result.toString(), "987654321");
}

TEST_F(LongIntTest, ZeroOperations) {
    LongInt a{ "123" };
    EXPECT_EQ((a + zero).toString(), "123");
    EXPECT_EQ((zero + a).toString(), "123");
    EXPECT_EQ((a - zero).toString(), "123");
    EXPECT_EQ((zero - a).toString(), "-123");
    EXPECT_EQ((a * zero).toString(), "0");
    EXPECT_EQ((zero * a).toString(), "0");
    EXPECT_EQ((zero / a).toString(), "0");
}

TEST_F(LongIntTest, NegativeNumberOperations) {
    LongInt a{ "-100" };
    LongInt b{ "-50" };
    EXPECT_EQ((a + b).toString(), "-150");
    EXPECT_EQ((a - b).toString(), "-50");
    EXPECT_EQ((a * b).toString(), "5000");
    EXPECT_EQ((a / b).toString(), "2");
}

TEST_F(LongIntTest, VeryLargeAddition) {
    LongInt a{ "999999999999999999999999999999" };
    LongInt b{ "1" };
    LongInt result = a + b;
    EXPECT_EQ(result.toString(), "1000000000000000000000000000000");
}

TEST_F(LongIntTest, VeryLargeSubtraction) {
    LongInt a{ "1000000000000000000000000000000" };
    LongInt b{ "1" };
    LongInt result = a - b;
    EXPECT_EQ(result.toString(), "999999999999999999999999999999");
}


TEST_F(LongIntTest, VeryLargeDivision) {
    LongInt a{ "1219326311370217952237463801118995278900" };
    LongInt b{ "12345678901234567890" };
    LongInt result = a / b;
    EXPECT_EQ(result.toString(), "98765432109876543210");
}

TEST_F(LongIntTest, LargeNumberComparisons) {
    LongInt a{ "123456789012345678901234567890" };
    LongInt b{ "123456789012345678901234567891" };
    LongInt c{ "123456789012345678901234567890" };

    EXPECT_TRUE(a < b);
    EXPECT_TRUE(b > a);
    EXPECT_TRUE(a == c);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(b >= a);
    EXPECT_TRUE(a <= c);
    EXPECT_TRUE(a >= c);
}

TEST_F(LongIntTest, LargeNegativeOperations) {
    LongInt a{ "-123456789012345678901234567890" };
    LongInt b{ "-123456789012345678901234567891" };
    LongInt c{ "123456789012345678901234567890" };

    EXPECT_TRUE(a > b);
    EXPECT_TRUE(b < a);
    EXPECT_TRUE(a + c == zero);
    EXPECT_TRUE(a - c == LongInt{ "-246913578024691357802469135780" });
}

TEST_F(LongIntTest, LargeNumberIncrementDecrement) {
    LongInt a{ "999999999999999999999999999999" };
    ++a;
    EXPECT_EQ(a.toString(), "1000000000000000000000000000000");
    --a;
    EXPECT_EQ(a.toString(), "999999999999999999999999999999");

    LongInt b = a++;
    EXPECT_EQ(b.toString(), "999999999999999999999999999999");
    EXPECT_EQ(a.toString(), "1000000000000000000000000000000");

    LongInt c = a--;
    EXPECT_EQ(c.toString(), "1000000000000000000000000000000");
    EXPECT_EQ(a.toString(), "999999999999999999999999999999");
}

TEST_F(LongIntTest, LargeNumberCompoundAssignments) {
    LongInt a{ "1000000000000000000000000000000" };
    LongInt b{ "500000000000000000000000000000" };

    a += b;
    EXPECT_EQ(a.toString(), "1500000000000000000000000000000");

    a -= b;
    EXPECT_EQ(a.toString(), "1000000000000000000000000000000");

    a *= LongInt{ "2" };
    EXPECT_EQ(a.toString(), "2000000000000000000000000000000");

    a /= LongInt{ "2" };
    EXPECT_EQ(a.toString(), "1000000000000000000000000000000");
}

TEST_F(LongIntTest, ExtremelyLargeNumbers) {
    string huge1 = "1" + string(100, '0');
    string huge2 = "5" + string(100, '0');

    LongInt a{ huge1 };
    LongInt b{ huge2 };

    EXPECT_EQ((a + b).toString(), "6" + string(100, '0'));
    EXPECT_EQ((b - a).toString(), "4" + string(100, '0'));
    EXPECT_EQ((a * LongInt{ "2" }).toString(), "2" + string(100, '0'));
    EXPECT_EQ((b / LongInt{ "5" }).toString(), "1" + string(100, '0'));
}

TEST_F(LongIntTest, LargeNumberEdgeCases) {
    LongInt max_val{ "9999999999999999999999999999999999999999" };
    LongInt min_val{ "-9999999999999999999999999999999999999999" };
    LongInt one{ "1" };

    EXPECT_EQ((max_val + one).toString(), "10000000000000000000000000000000000000000");
    EXPECT_EQ((min_val - one).toString(), "-10000000000000000000000000000000000000000");

    LongInt zero;
    EXPECT_EQ((max_val * zero).toString(), "0");
    EXPECT_EQ((min_val * zero).toString(), "0");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}