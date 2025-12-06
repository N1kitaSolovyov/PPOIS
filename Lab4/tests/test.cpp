#include "pch.h"
#include "sorts.h"
#include "advanced_graph.h"
#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <deque>
#include <array>
#include <string>
#include <random>

// ==================== ТЕСТЫ ДЛЯ КЛАССА STUDENT ====================



TEST(StudentTest, ComparisonOperators) {
    Student s1(1, "Alice", 4.0);
    Student s2(2, "Bob", 3.5);
    Student s3(1, "Charlie", 4.5);

    EXPECT_TRUE(s1 < s2);
    EXPECT_FALSE(s2 < s1);
    EXPECT_FALSE(s1 < s3); // id одинаковые
}

TEST(StudentTest, CompareByName) {
    Student s1(1, "Alice", 4.0);
    Student s2(2, "Bob", 3.5);
    Student s3(3, "Alice", 4.5);

    Student::CompareByName cmp;
    EXPECT_TRUE(cmp(s1, s2));
    EXPECT_FALSE(cmp(s2, s1));
    EXPECT_FALSE(cmp(s1, s3)); // имена одинаковые
}

TEST(StudentTest, CompareByGrade) {
    Student s1(1, "Alice", 4.0);
    Student s2(2, "Bob", 3.5);
    Student s3(3, "Charlie", 4.0);

    Student::CompareByGrade cmp;
    EXPECT_FALSE(cmp(s1, s2));
    EXPECT_TRUE(cmp(s2, s1));
    EXPECT_FALSE(cmp(s1, s3)); // оценки одинаковые
}

TEST(StudentTest, OutputOperator) {
    Student s(123, "John Doe", 4.75);
    std::ostringstream oss;
    oss << s;
    std::string output = oss.str();
    EXPECT_TRUE(output.find("Student{id:123") != std::string::npos);
    EXPECT_TRUE(output.find("name:\"John Doe\"") != std::string::npos);
    EXPECT_TRUE(output.find("grade:4.75") != std::string::npos);
}

// ==================== ТЕСТЫ ДЛЯ PANCAKE SORT ====================

TEST(PancakeSortTest, EmptyContainer) {
    std::vector<int> empty;
    ASSERT_NO_THROW(pancake_sort(empty));
    EXPECT_TRUE(empty.empty());
}

TEST(PancakeSortTest, SingleElement) {
    std::vector<int> single = { 42 };
    pancake_sort(single);
    EXPECT_EQ(single, std::vector<int>({ 42 }));
}

TEST(PancakeSortTest, AlreadySorted) {
    std::vector<int> sorted = { 1, 2, 3, 4, 5 };
    pancake_sort(sorted);
    EXPECT_EQ(sorted, std::vector<int>({ 1, 2, 3, 4, 5 }));
}

TEST(PancakeSortTest, ReverseSorted) {
    std::vector<int> reverse = { 5, 4, 3, 2, 1 };
    pancake_sort(reverse);
    EXPECT_EQ(reverse, std::vector<int>({ 1, 2, 3, 4, 5 }));
}

TEST(PancakeSortTest, RandomOrder) {
    std::vector<int> random = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3 };
    std::vector<int> expected = { 1, 1, 2, 3, 3, 4, 5, 5, 6, 9 };
    pancake_sort(random);
    EXPECT_EQ(random, expected);
}

TEST(PancakeSortTest, WithCustomComparator) {
    std::vector<int> numbers = { 3, 1, 4, 1, 5 };
    pancake_sort(numbers, std::greater<int>());
    EXPECT_EQ(numbers, std::vector<int>({ 5, 4, 3, 1, 1 }));
}

TEST(PancakeSortTest, AllEqualElements) {
    std::vector<int> numbers(10, 5);
    pancake_sort(numbers);
    EXPECT_EQ(numbers, std::vector<int>(10, 5));
}

TEST(PancakeSortTest, TwoElements) {
    std::vector<int> numbers = { 2, 1 };
    pancake_sort(numbers);
    EXPECT_EQ(numbers, std::vector<int>({ 1, 2 }));

    numbers = { 1, 2 };
    pancake_sort(numbers);
    EXPECT_EQ(numbers, std::vector<int>({ 1, 2 }));
}

TEST(PancakeSortTest, ThreeElements) {
    std::vector<int> numbers = { 3, 1, 2 };
    pancake_sort(numbers);
    EXPECT_EQ(numbers, std::vector<int>({ 1, 2, 3 }));
}

TEST(PancakeSortTest, WithCArray) {
    int arr[] = { 5, 3, 8, 1, 2 };
    int expected[] = { 1, 2, 3, 5, 8 };

    pancake_sort(arr);

    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST(PancakeSortTest, DifferentContainers) {
    std::deque<int> deque = { 5, 3, 1, 4, 2 };
    pancake_sort(deque);
    EXPECT_EQ(deque, std::deque<int>({ 1, 2, 3, 4, 5 }));

    std::array<int, 5> arr = { 5, 3, 1, 4, 2 };
    pancake_sort(arr);
    EXPECT_EQ(arr, (std::array<int, 5>{1, 2, 3, 4, 5}));
}

TEST(PancakeSortTest, StringSorting) {
    std::vector<std::string> strings = { "zebra", "apple", "banana", "cherry" };
    pancake_sort(strings);
    EXPECT_EQ(strings, std::vector<std::string>({ "apple", "banana", "cherry", "zebra" }));
}

TEST(PancakeSortTest, FloatSorting) {
    std::vector<float> floats = { 3.14f, 1.59f, 2.65f, 3.58f };
    pancake_sort(floats);
    EXPECT_EQ(floats, std::vector<float>({ 1.59f, 2.65f, 3.14f, 3.58f }));
}

TEST(PancakeSortTest, WithLambdaComparator) {
    std::vector<int> numbers = { 3, 1, 4, 1, 5 };
    pancake_sort(numbers, [](int a, int b) { return a > b; });
    EXPECT_EQ(numbers, std::vector<int>({ 5, 4, 3, 1, 1 }));
}

// ==================== ТЕСТЫ ДЛЯ SMOOTHSORT ====================

TEST(SmoothSortTest, EmptyContainer) {
    std::vector<int> empty;
    ASSERT_NO_THROW(smooth_sort(empty));
    EXPECT_TRUE(empty.empty());
}

TEST(SmoothSortTest, SingleElement) {
    std::vector<int> single = { 42 };
    smooth_sort(single);
    EXPECT_EQ(single, std::vector<int>({ 42 }));
}

TEST(SmoothSortTest, AlreadySorted) {
    std::vector<int> sorted = { 1, 2, 3, 4, 5 };
    smooth_sort(sorted);
    EXPECT_EQ(sorted, std::vector<int>({ 1, 2, 3, 4, 5 }));
}

TEST(SmoothSortTest, ReverseSorted) {
    std::vector<int> reverse = { 5, 4, 3, 2, 1 };
    smooth_sort(reverse);
    EXPECT_EQ(reverse, std::vector<int>({ 1, 2, 3, 4, 5 }));
}

TEST(SmoothSortTest, RandomOrder) {
    std::vector<int> random = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3 };
    std::vector<int> expected = { 1, 1, 2, 3, 3, 4, 5, 5, 6, 9 };
    smooth_sort(random);
    EXPECT_EQ(random, expected);
}

TEST(SmoothSortTest, WithCustomComparator) {
    std::vector<int> numbers = { 3, 1, 4, 1, 5 };
    smooth_sort(numbers, std::greater<int>());
    EXPECT_EQ(numbers, std::vector<int>({ 5, 4, 3, 1, 1 }));
}

TEST(SmoothSortTest, AllEqualElements) {
    std::vector<int> numbers(10, 5);
    smooth_sort(numbers);
    EXPECT_EQ(numbers, std::vector<int>(10, 5));
}

TEST(SmoothSortTest, TwoElements) {
    std::vector<int> numbers = { 2, 1 };
    smooth_sort(numbers);
    EXPECT_EQ(numbers, std::vector<int>({ 1, 2 }));

    numbers = { 1, 2 };
    smooth_sort(numbers);
    EXPECT_EQ(numbers, std::vector<int>({ 1, 2 }));
}

TEST(SmoothSortTest, ThreeElements) {
    std::vector<int> numbers = { 3, 1, 2 };
    smooth_sort(numbers);
    EXPECT_EQ(numbers, std::vector<int>({ 1, 2, 3 }));
}

TEST(SmoothSortTest, WithCArray) {
    int arr[] = { 5, 3, 8, 1, 2 };
    int expected[] = { 1, 2, 3, 5, 8 };

    smooth_sort(arr);

    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST(SmoothSortTest, DifferentContainers) {
    std::deque<int> deque = { 5, 3, 1, 4, 2 };
    smooth_sort(deque);
    EXPECT_EQ(deque, std::deque<int>({ 1, 2, 3, 4, 5 }));

    std::array<int, 5> arr = { 5, 3, 1, 4, 2 };
    smooth_sort(arr);
    EXPECT_EQ(arr, (std::array<int, 5>{1, 2, 3, 4, 5}));
}

TEST(SmoothSortTest, StringSorting) {
    std::vector<std::string> strings = { "zebra", "apple", "banana", "cherry" };
    smooth_sort(strings);
    EXPECT_EQ(strings, std::vector<std::string>({ "apple", "banana", "cherry", "zebra" }));
}

TEST(SmoothSortTest, FloatSorting) {
    std::vector<float> floats = { 3.14f, 1.59f, 2.65f, 3.58f };
    smooth_sort(floats);
    EXPECT_EQ(floats, std::vector<float>({ 1.59f, 2.65f, 3.14f, 3.58f }));
}

TEST(SmoothSortTest, WithLambdaComparator) {
    std::vector<int> numbers = { 3, 1, 4, 1, 5 };
    smooth_sort(numbers, [](int a, int b) { return a > b; });
    EXPECT_EQ(numbers, std::vector<int>({ 5, 4, 3, 1, 1 }));
}

TEST(SmoothSortTest, NegativeNumbers) {
    std::vector<int> numbers = { -3, -1, -4, -1, -5 };
    smooth_sort(numbers);
    EXPECT_EQ(numbers, std::vector<int>({ -5, -4, -3, -1, -1 }));
}



TEST(SmoothSortTest, LargeDataset) {
    const int SIZE = 1000;
    std::vector<int> large(SIZE);
    std::vector<int> expected(SIZE);

    for (int i = 0; i < SIZE; ++i) {
        large[i] = SIZE - i - 1;  // обратный порядок
        expected[i] = i;          // прямой порядок
    }

    smooth_sort(large);
    EXPECT_EQ(large, expected);
}

TEST(SmoothSortTest, AlreadySortedLarge) {
    const int SIZE = 1000;
    std::vector<int> large(SIZE);
    std::vector<int> expected(SIZE);

    for (int i = 0; i < SIZE; ++i) {
        large[i] = i;
        expected[i] = i;
    }

    smooth_sort(large);
    EXPECT_EQ(large, expected);
}

TEST(SmoothSortTest, DuplicateElements) {
    std::vector<int> numbers = { 5, 2, 8, 2, 5, 1, 8, 1 };
    std::vector<int> expected = { 1, 1, 2, 2, 5, 5, 8, 8 };
    smooth_sort(numbers);
    EXPECT_EQ(numbers, expected);
}

// ==================== ТЕСТЫ ДЛЯ ГРАФА ====================

TEST(GraphTest, DefaultConstructor) {
    AdvancedWirthGraph<int> graph;
    EXPECT_TRUE(graph.empty());
    EXPECT_EQ(graph.size(), 0);
    EXPECT_EQ(graph.vertex_count(), 0);
    EXPECT_EQ(graph.edge_count(), 0);
}

TEST(GraphTest, AddVertex) {
    AdvancedWirthGraph<int> graph;

    graph.add_vertex(1);
    EXPECT_FALSE(graph.empty());
    EXPECT_EQ(graph.size(), 1);
    EXPECT_TRUE(graph.has_vertex(1));
    EXPECT_FALSE(graph.has_vertex(2));

    graph.add_vertex(2);
    EXPECT_EQ(graph.size(), 2);
    EXPECT_TRUE(graph.has_vertex(2));
}

TEST(GraphTest, AddVertexDuplicateThrows) {
    AdvancedWirthGraph<int> graph;
    graph.add_vertex(1);
    EXPECT_THROW(graph.add_vertex(1), GraphException);
}

TEST(GraphTest, AddEdge) {
    AdvancedWirthGraph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);

    graph.add_edge(1, 2);
    EXPECT_EQ(graph.edge_count(), 1);
    EXPECT_TRUE(graph.has_edge(1, 2));
    EXPECT_TRUE(graph.has_edge(2, 1)); // неориентированный граф

    graph.add_edge(2, 3);
    EXPECT_EQ(graph.edge_count(), 2);
    EXPECT_TRUE(graph.has_edge(2, 3));
}

TEST(GraphTest, AddEdgeMissingVertexThrows) {
    AdvancedWirthGraph<int> graph;
    graph.add_vertex(1);
    EXPECT_THROW(graph.add_edge(1, 2), GraphException);
    EXPECT_THROW(graph.add_edge(2, 1), GraphException);
    EXPECT_THROW(graph.add_edge(2, 3), GraphException);
}

TEST(GraphTest, AddEdgeDuplicateThrows) {
    AdvancedWirthGraph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(1, 2);
    EXPECT_THROW(graph.add_edge(1, 2), GraphException);
    EXPECT_THROW(graph.add_edge(2, 1), GraphException);
}

TEST(GraphTest, RemoveVertex) {
    AdvancedWirthGraph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);

    EXPECT_EQ(graph.size(), 3);
    EXPECT_EQ(graph.edge_count(), 2);

    graph.remove_vertex(2);
    EXPECT_EQ(graph.size(), 2);
    EXPECT_EQ(graph.edge_count(), 0); // ребра с вершиной 2 удалены
    EXPECT_FALSE(graph.has_vertex(2));
    EXPECT_TRUE(graph.has_vertex(1));
    EXPECT_TRUE(graph.has_vertex(3));
}

TEST(GraphTest, RemoveVertexThrowsWhenNotFound) {
    AdvancedWirthGraph<int> graph;
    graph.add_vertex(1);
    EXPECT_THROW(graph.remove_vertex(2), GraphException);
}

TEST(GraphTest, RemoveEdge) {
    AdvancedWirthGraph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);
    graph.add_edge(1, 3);

    EXPECT_EQ(graph.edge_count(), 3);
    graph.remove_edge(1, 2);
    EXPECT_EQ(graph.edge_count(), 2);
    EXPECT_FALSE(graph.has_edge(1, 2));
    EXPECT_FALSE(graph.has_edge(2, 1));
    EXPECT_TRUE(graph.has_edge(2, 3));
    EXPECT_TRUE(graph.has_edge(1, 3));
}

TEST(GraphTest, RemoveEdgeThrowsWhenNotFound) {
    AdvancedWirthGraph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    EXPECT_THROW(graph.remove_edge(1, 2), GraphException);
    graph.add_edge(1, 2);
    EXPECT_THROW(graph.remove_edge(1, 3), GraphException);
    EXPECT_THROW(graph.remove_edge(3, 1), GraphException);
}

TEST(GraphTest, VertexDegree) {
    AdvancedWirthGraph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_vertex(4);

    graph.add_edge(1, 2);
    graph.add_edge(1, 3);
    graph.add_edge(1, 4);

    EXPECT_EQ(graph.vertex_degree(1), 3);
    EXPECT_EQ(graph.vertex_degree(2), 1);
    EXPECT_EQ(graph.vertex_degree(3), 1);
    EXPECT_EQ(graph.vertex_degree(4), 1);

    graph.add_edge(2, 3);
    EXPECT_EQ(graph.vertex_degree(2), 2);
}

TEST(GraphTest, VertexDegreeThrowsWhenNotFound) {
    AdvancedWirthGraph<int> graph;
    graph.add_vertex(1);
    EXPECT_THROW(graph.vertex_degree(2), GraphException);
}

TEST(GraphTest, Clear) {
    AdvancedWirthGraph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(1, 2);

    EXPECT_FALSE(graph.empty());
    EXPECT_EQ(graph.size(), 2);
    EXPECT_EQ(graph.edge_count(), 1);

    graph.clear();
    EXPECT_TRUE(graph.empty());
    EXPECT_EQ(graph.size(), 0);
    EXPECT_EQ(graph.edge_count(), 0);
    EXPECT_FALSE(graph.has_vertex(1));
    EXPECT_FALSE(graph.has_vertex(2));
}

TEST(GraphTest, CopyConstructor) {
    AdvancedWirthGraph<int> graph1;
    graph1.add_vertex(1);
    graph1.add_vertex(2);
    graph1.add_vertex(3);
    graph1.add_edge(1, 2);
    graph1.add_edge(2, 3);

    AdvancedWirthGraph<int> graph2(graph1);

    EXPECT_EQ(graph1.size(), graph2.size());
    EXPECT_EQ(graph1.edge_count(), graph2.edge_count());
    EXPECT_TRUE(graph2.has_vertex(1));
    EXPECT_TRUE(graph2.has_vertex(2));
    EXPECT_TRUE(graph2.has_vertex(3));
    EXPECT_TRUE(graph2.has_edge(1, 2));
    EXPECT_TRUE(graph2.has_edge(2, 3));

    // Проверяем глубокое копирование
    graph2.remove_vertex(3);
    EXPECT_TRUE(graph1.has_vertex(3));
    EXPECT_FALSE(graph2.has_vertex(3));
}

TEST(GraphTest, AssignmentOperator) {
    AdvancedWirthGraph<int> graph1;
    graph1.add_vertex(1);
    graph1.add_vertex(2);
    graph1.add_edge(1, 2);

    AdvancedWirthGraph<int> graph2;
    graph2.add_vertex(3);
    graph2.add_vertex(4);
    graph2.add_edge(3, 4);

    graph2 = graph1;

    EXPECT_EQ(graph1.size(), graph2.size());
    EXPECT_EQ(graph1.edge_count(), graph2.edge_count());
    EXPECT_TRUE(graph2.has_vertex(1));
    EXPECT_TRUE(graph2.has_vertex(2));
    EXPECT_TRUE(graph2.has_edge(1, 2));
    EXPECT_FALSE(graph2.has_vertex(3));
}

TEST(GraphTest, SelfAssignment) {
    AdvancedWirthGraph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(1, 2);

    graph = graph; // самоприсваивание
    EXPECT_EQ(graph.size(), 2);
    EXPECT_EQ(graph.edge_count(), 1);
    EXPECT_TRUE(graph.has_vertex(1));
    EXPECT_TRUE(graph.has_vertex(2));
    EXPECT_TRUE(graph.has_edge(1, 2));
}

TEST(GraphTest, Swap) {
    AdvancedWirthGraph<int> graph1;
    graph1.add_vertex(1);
    graph1.add_vertex(2);
    graph1.add_edge(1, 2);

    AdvancedWirthGraph<int> graph2;
    graph2.add_vertex(3);
    graph2.add_vertex(4);
    graph2.add_vertex(5);
    graph2.add_edge(3, 4);
    graph2.add_edge(4, 5);

    graph1.swap(graph2);

    EXPECT_EQ(graph1.size(), 3);
    EXPECT_EQ(graph1.edge_count(), 2);
    EXPECT_TRUE(graph1.has_vertex(3));
    EXPECT_TRUE(graph1.has_edge(3, 4));

    EXPECT_EQ(graph2.size(), 2);
    EXPECT_EQ(graph2.edge_count(), 1);
    EXPECT_TRUE(graph2.has_vertex(1));
    EXPECT_TRUE(graph2.has_edge(1, 2));
}

TEST(GraphTest, InitializerListConstructor) {
    AdvancedWirthGraph<int> graph({ 1, 2, 3, 4 }, { {1, 2}, {2, 3}, {3, 4} });

    EXPECT_EQ(graph.size(), 4);
    EXPECT_EQ(graph.edge_count(), 3);
    EXPECT_TRUE(graph.has_vertex(1));
    EXPECT_TRUE(graph.has_vertex(2));
    EXPECT_TRUE(graph.has_vertex(3));
    EXPECT_TRUE(graph.has_vertex(4));
    EXPECT_TRUE(graph.has_edge(1, 2));
    EXPECT_TRUE(graph.has_edge(2, 3));
    EXPECT_TRUE(graph.has_edge(3, 4));
}

TEST(GraphTest, ComparisonOperators) {
    AdvancedWirthGraph<int> graph1;
    graph1.add_vertex(1);
    graph1.add_vertex(2);
    graph1.add_edge(1, 2);

    AdvancedWirthGraph<int> graph2;
    graph2.add_vertex(1);
    graph2.add_vertex(2);
    graph2.add_edge(1, 2);

    AdvancedWirthGraph<int> graph3;
    graph3.add_vertex(1);
    graph3.add_vertex(2);
    graph3.add_vertex(3);

    EXPECT_TRUE(graph1 == graph2);
    EXPECT_FALSE(graph1 != graph2);
    EXPECT_FALSE(graph1 == graph3);
    EXPECT_TRUE(graph1 != graph3);
    EXPECT_TRUE(graph3 > graph1);
    EXPECT_TRUE(graph1 < graph3);
    EXPECT_TRUE(graph1 <= graph2);
    EXPECT_TRUE(graph1 >= graph2);
}

TEST(GraphTest, VertexIterator) {
    AdvancedWirthGraph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);

    std::vector<int> vertices;
    for (const auto& v : graph) {
        vertices.push_back(v);
    }

    EXPECT_EQ(vertices.size(), 3);
    EXPECT_TRUE(std::find(vertices.begin(), vertices.end(), 1) != vertices.end());
    EXPECT_TRUE(std::find(vertices.begin(), vertices.end(), 2) != vertices.end());
    EXPECT_TRUE(std::find(vertices.begin(), vertices.end(), 3) != vertices.end());

    auto it = graph.vertex_begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(it, graph.vertex_end());
}

TEST(GraphTest, VertexIteratorDereferenceEndThrows) {
    AdvancedWirthGraph<int> graph;
    graph.add_vertex(1);

    auto it = graph.vertex_begin();
    ++it; // теперь end
    EXPECT_THROW(*it, GraphException);
    EXPECT_THROW(it.operator->(), GraphException);
}

TEST(GraphTest, AdjacentIterator) {
    AdvancedWirthGraph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_vertex(4);

    graph.add_edge(1, 2);
    graph.add_edge(1, 3);
    graph.add_edge(1, 4);
    graph.add_edge(2, 3);

    std::vector<int> adjacent_to_1;
    for (auto it = graph.adjacent_begin(1); it != graph.adjacent_end(1); ++it) {
        adjacent_to_1.push_back(*it);
    }

    EXPECT_EQ(adjacent_to_1.size(), 3);
    EXPECT_TRUE(std::find(adjacent_to_1.begin(), adjacent_to_1.end(), 2) != adjacent_to_1.end());
    EXPECT_TRUE(std::find(adjacent_to_1.begin(), adjacent_to_1.end(), 3) != adjacent_to_1.end());
    EXPECT_TRUE(std::find(adjacent_to_1.begin(), adjacent_to_1.end(), 4) != adjacent_to_1.end());
}

TEST(GraphTest, AdjacentIteratorEmpty) {
    AdvancedWirthGraph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);

    auto it = graph.adjacent_begin(1);
    auto end = graph.adjacent_end(1);
    EXPECT_EQ(it, end);

    graph.add_edge(1, 2);
    it = graph.adjacent_begin(1);
    EXPECT_NE(it, end);
    EXPECT_EQ(*it, 2);
}

TEST(GraphTest, AdjacentIteratorThrowsWhenVertexNotFound) {
    AdvancedWirthGraph<int> graph;
    graph.add_vertex(1);
    EXPECT_THROW(graph.adjacent_begin(2), GraphException);
}

TEST(GraphTest, OutputOperator) {
    AdvancedWirthGraph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);

    std::ostringstream oss;
    oss << graph;
    std::string output = oss.str();

    EXPECT_TRUE(output.find("Vertices: 3") != std::string::npos ||
        output.find("Vertices: 3,") != std::string::npos);
    EXPECT_TRUE(output.find("1 2 3") != std::string::npos);
    EXPECT_TRUE(output.find("(1-2)") != std::string::npos ||
        output.find("1-2") != std::string::npos);
    EXPECT_TRUE(output.find("(2-3)") != std::string::npos ||
        output.find("2-3") != std::string::npos);
}

TEST(GraphTest, StringVertices) {
    AdvancedWirthGraph<std::string> graph;
    graph.add_vertex("Moscow");
    graph.add_vertex("SPb");
    graph.add_vertex("Kazan");

    graph.add_edge("Moscow", "SPb");
    graph.add_edge("Moscow", "Kazan");

    EXPECT_EQ(graph.size(), 3);
    EXPECT_EQ(graph.edge_count(), 2);
    EXPECT_TRUE(graph.has_vertex("Moscow"));
    EXPECT_TRUE(graph.has_edge("Moscow", "SPb"));
    EXPECT_TRUE(graph.has_edge("SPb", "Moscow"));
    EXPECT_EQ(graph.vertex_degree("Moscow"), 2);
    EXPECT_EQ(graph.vertex_degree("SPb"), 1);
}

TEST(GraphTest, ComplexOperations) {
    AdvancedWirthGraph<int> graph;

    // Добавляем много вершин
    for (int i = 1; i <= 10; ++i) {
        graph.add_vertex(i);
    }

    // Создаем полный граф K5 среди первых 5 вершин
    for (int i = 1; i <= 5; ++i) {
        for (int j = i + 1; j <= 5; ++j) {
            graph.add_edge(i, j);
        }
    }

    EXPECT_EQ(graph.size(), 10);
    EXPECT_EQ(graph.edge_count(), 10); // C(5,2) = 10 ребер в K5

    // Проверяем степени
    for (int i = 1; i <= 5; ++i) {
        EXPECT_EQ(graph.vertex_degree(i), 4);
    }
    for (int i = 6; i <= 10; ++i) {
        EXPECT_EQ(graph.vertex_degree(i), 0);
    }

    // Удаляем вершину из клики
    graph.remove_vertex(1);
    EXPECT_EQ(graph.size(), 9);
    EXPECT_EQ(graph.edge_count(), 6); // C(4,2) = 6 ребер в K4

    for (int i = 2; i <= 5; ++i) {
        EXPECT_FALSE(graph.has_edge(1, i));
        EXPECT_EQ(graph.vertex_degree(i), 3);
    }
}

TEST(GraphTest, TypeTraitsSpecialization) {
    AdvancedWirthGraph<std::string> graph;
    graph.add_vertex("Test");
    EXPECT_NO_THROW(graph.has_vertex("Test"));

    AdvancedWirthGraph<int> intGraph;
    intGraph.add_vertex(42);
    EXPECT_NO_THROW(intGraph.has_vertex(42));
}

TEST(GraphTest, StressTest) {
    AdvancedWirthGraph<int> graph;
    const int N = 100;

    for (int i = 0; i < N; ++i) {
        graph.add_vertex(i);
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 1; j <= 5 && i + j < N; ++j) {
            graph.add_edge(i, i + j);
        }
    }

    EXPECT_EQ(graph.size(), N);

    for (int i = 0; i < N; i += 2) {
        graph.remove_vertex(i);
    }

    EXPECT_EQ(graph.size(), N / 2);

    for (int i = 1; i < N; i += 2) {
        EXPECT_TRUE(graph.has_vertex(i));
    }
}



TEST(GraphTest, EmptyGraphIterators) {
    AdvancedWirthGraph<int> graph;
    EXPECT_EQ(graph.vertex_begin(), graph.vertex_end());
    EXPECT_EQ(graph.cvertex_begin(), graph.cvertex_end());
}

TEST(GraphTest, ConstVertexIterator) {
    AdvancedWirthGraph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(1, 2);

    const auto& const_graph = graph;
    std::vector<int> vertices;
    for (auto it = const_graph.vertex_begin(); it != const_graph.vertex_end(); ++it) {
        vertices.push_back(*it);
    }
    EXPECT_EQ(vertices.size(), 2);
}

TEST(GraphTest, MaxSize) {
    AdvancedWirthGraph<int> graph;
    EXPECT_GT(graph.max_size(), 0);
}

TEST(GraphTest, EdgeCases) {
    AdvancedWirthGraph<int> graph;
    graph.add_vertex(1);
    EXPECT_EQ(graph.vertex_degree(1), 0);

    graph.add_vertex(2);
    graph.add_edge(1, 2);
    EXPECT_EQ(graph.vertex_degree(1), 1);
    EXPECT_EQ(graph.vertex_degree(2), 1);
}

TEST(GraphTest, MultipleOperations) {
    AdvancedWirthGraph<int> graph;

    // Добавляем и удаляем несколько раз
    graph.add_vertex(1);
    graph.remove_vertex(1);
    EXPECT_TRUE(graph.empty());

    graph.add_vertex(1);
    EXPECT_EQ(graph.size(), 1);
}

// ==================== ИНТЕГРАЦИОННЫЕ ТЕСТЫ ====================

TEST(IntegrationTest, SortGraphVertices) {
    AdvancedWirthGraph<int> graph;
    graph.add_vertex(5);
    graph.add_vertex(1);
    graph.add_vertex(3);
    graph.add_vertex(2);
    graph.add_vertex(4);

    std::vector<int> vertices;
    for (const auto& v : graph) {
        vertices.push_back(v);
    }

    pancake_sort(vertices);
    std::vector<int> expected = { 1, 2, 3, 4, 5 };
    EXPECT_EQ(vertices, expected);

    smooth_sort(vertices, std::greater<int>());
    expected = { 5, 4, 3, 2, 1 };
    EXPECT_EQ(vertices, expected);
}



// ==================== ТЕСТЫ НА ПОГРАНИЧНЫЕ СЛУЧАИ ====================

TEST(EdgeCaseTest, GraphWithSingleVertexAndNoEdges) {
    AdvancedWirthGraph<int> graph;
    graph.add_vertex(1);

    EXPECT_EQ(graph.size(), 1);
    EXPECT_EQ(graph.edge_count(), 0);
    EXPECT_EQ(graph.vertex_degree(1), 0);

    auto it = graph.adjacent_begin(1);
    auto end = graph.adjacent_end(1);
    EXPECT_EQ(it, end);
}

TEST(EdgeCaseTest, AddAndRemoveSameVertexMultipleTimes) {
    AdvancedWirthGraph<int> graph;

    graph.add_vertex(1);
    graph.remove_vertex(1);
    EXPECT_TRUE(graph.empty());

    EXPECT_NO_THROW(graph.add_vertex(1));
    EXPECT_EQ(graph.size(), 1);
}

TEST(EdgeCaseTest, GraphIsolationThenConnect) {
    AdvancedWirthGraph<int> graph;

    for (int i = 1; i <= 5; ++i) {
        graph.add_vertex(i);
    }

    EXPECT_EQ(graph.edge_count(), 0);

    for (int i = 1; i < 5; ++i) {
        graph.add_edge(i, i + 1);
    }

    EXPECT_EQ(graph.edge_count(), 4);
    EXPECT_EQ(graph.vertex_degree(1), 1);
    EXPECT_EQ(graph.vertex_degree(2), 2);
    EXPECT_EQ(graph.vertex_degree(3), 2);
    EXPECT_EQ(graph.vertex_degree(4), 2);
    EXPECT_EQ(graph.vertex_degree(5), 1);
}

TEST(EdgeCaseTest, RemoveVertexWithAllEdges) {
    AdvancedWirthGraph<int> graph;

    for (int i = 1; i <= 4; ++i) {
        graph.add_vertex(i);
    }

    // Полный граф K4
    for (int i = 1; i <= 4; ++i) {
        for (int j = i + 1; j <= 4; ++j) {
            graph.add_edge(i, j);
        }
    }

    EXPECT_EQ(graph.edge_count(), 6);
    graph.remove_vertex(1);
    EXPECT_EQ(graph.edge_count(), 3); // C(3,2) = 3
    EXPECT_EQ(graph.size(), 3);
}


TEST(EdgeCaseTest, ExceptionSafety) {
    AdvancedWirthGraph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(1, 2);

    try {
        graph.add_edge(1, 2);
        FAIL() << "Expected GraphException";
    }
    catch (const GraphException&) {
    }

    EXPECT_EQ(graph.size(), 2);
    EXPECT_EQ(graph.edge_count(), 1);
    EXPECT_TRUE(graph.has_edge(1, 2));

    try {
        graph.add_edge(1, 3);
        FAIL() << "Expected GraphException";
    }
    catch (const GraphException&) {
    }

    EXPECT_EQ(graph.size(), 2);
    EXPECT_EQ(graph.edge_count(), 1);
}

// ==================== ДОПОЛНИТЕЛЬНЫЕ ТЕСТЫ ДЛЯ ПОКРЫТИЯ ====================

TEST(CoverageTest, PancakeSortEdgeCases) {
    // Тест для покрытия всех ветвей pancake_sort
    std::vector<int> empty;
    pancake_sort(empty);

    std::vector<int> single = { 1 };
    pancake_sort(single);

    std::vector<int> two_reverse = { 2, 1 };
    pancake_sort(two_reverse);

    std::vector<int> two_sorted = { 1, 2 };
    pancake_sort(two_sorted);

    // Тест с max_index == current_size - 1 (не нужно делать flip)
    std::vector<int> already_sorted = { 1, 2, 3, 4, 5 };
    pancake_sort(already_sorted);

    // Тест с max_index == 0 (нужен только один flip)
    std::vector<int> max_first = { 5, 1, 2, 3, 4 };
    pancake_sort(max_first);
}

TEST(CoverageTest, SmoothSortEdgeCases) {
    // Тест для покрытия всех ветвей smooth_sort
    std::vector<int> empty;
    smooth_sort(empty);

    std::vector<int> single = { 1 };
    smooth_sort(single);

    // Тест с кучей, где нужно просеивать вниз
    std::vector<int> heap_case = { 3, 1, 4, 1, 5, 9, 2, 6 };
    smooth_sort(heap_case);

    // Тест с уже отсортированной кучей
    std::vector<int> sorted = { 1, 2, 3, 4, 5 };
    smooth_sort(sorted);

    // Тест с обратно отсортированным массивом
    std::vector<int> reversed = { 5, 4, 3, 2, 1 };
    smooth_sort(reversed);
}

TEST(CoverageTest, GraphIteratorCoverage) {
    AdvancedWirthGraph<int> graph;

    // Тест итераторов на пустом графе
    EXPECT_EQ(graph.begin(), graph.end());
    EXPECT_EQ(graph.cvertex_begin(), graph.cvertex_end());

    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(1, 2);

    // Тест префиксного и постфиксного декремента
    auto it = graph.vertex_begin();
    ++it;
    auto it2 = it--;
    EXPECT_EQ(*it2, 2);
    EXPECT_EQ(*it, 1);

    // Тест константных итераторов
    const auto& const_graph = graph;
    auto cit = const_graph.vertex_begin();
    EXPECT_EQ(*cit, 1);
    ++cit;
    EXPECT_EQ(*cit, 2);
}

TEST(CoverageTest, GraphEdgeCases) {
    AdvancedWirthGraph<int> graph;

    // Добавление вершины, которая уже есть (должно бросить исключение)
    graph.add_vertex(1);
    EXPECT_THROW(graph.add_vertex(1), GraphException);

    // Удаление несуществующей вершины
    EXPECT_THROW(graph.remove_vertex(2), GraphException);

    // Добавление ребра к несуществующей вершине
    EXPECT_THROW(graph.add_edge(1, 2), GraphException);

    // Удаление несуществующего ребра
    graph.add_vertex(2);
    EXPECT_THROW(graph.remove_edge(1, 2), GraphException);

    // Получение степени несуществующей вершины
    EXPECT_THROW(graph.vertex_degree(3), GraphException);
}

// ==================== ТЕСТЫ С РАЗНЫМИ ТИПАМИ ДАННЫХ ====================

TEST(TypeTest, DifferentDataTypes) {
    // Тест с различными типами данных для сортировок

    // char
    std::vector<char> chars = { 'z', 'a', 'm', 'b' };
    pancake_sort(chars);
    EXPECT_EQ(chars, std::vector<char>({ 'a', 'b', 'm', 'z' }));

    // unsigned int
    std::vector<unsigned int> uints = { 5, 3, 8, 1 };
    smooth_sort(uints);
    EXPECT_EQ(uints, std::vector<unsigned int>({ 1, 3, 5, 8 }));

    // long long
    std::vector<long long> longs = { 1000, 500, 2000, 100 };
    pancake_sort(longs);
    EXPECT_EQ(longs, std::vector<long long>({ 100, 500, 1000, 2000 }));
}

// ==================== ТЕСТЫ НА УСТОЙЧИВОСТЬ ====================

TEST(RobustnessTest, PancakeSortStability) {
    // Pancake sort не является стабильной сортировкой, но проверяем корректность
    std::vector<std::pair<int, int>> pairs = {
        {2, 1}, {1, 2}, {2, 3}, {1, 1}, {2, 2}
    };

    // Сортируем только по first
    auto comp = [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.first < b.first;
        };

    pancake_sort(pairs, comp);

    // Проверяем, что first отсортированы
    for (size_t i = 1; i < pairs.size(); ++i) {
        EXPECT_LE(pairs[i - 1].first, pairs[i].first);
    }
}

TEST(RobustnessTest, SmoothSortStability) {
    // Smooth sort не является стабильной сортировкой
    std::vector<std::pair<int, int>> pairs = {
        {2, 1}, {1, 2}, {2, 3}, {1, 1}, {2, 2}
    };

    auto comp = [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.first < b.first;
        };

    smooth_sort(pairs, comp);

    for (size_t i = 1; i < pairs.size(); ++i) {
        EXPECT_LE(pairs[i - 1].first, pairs[i].first);
    }
}

// ==================== ГЛАВНАЯ ФУНКЦИЯ ТЕСТОВ ====================

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);


    int result = RUN_ALL_TESTS();

    if (result == 0) {
        std::cout << "\n✅ Все тесты пройдены успешно!" << std::endl;
    }
    else {
        std::cout << "\n❌ Некоторые тесты не пройдены" << std::endl;
    }

    return result;
}