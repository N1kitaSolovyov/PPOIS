#pragma once
#ifndef SORTS_H
#define SORTS_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <string>
#include <list>
#include <deque>

// ==================== ÊËÀÑÑ STUDENT ÄËß ÄÅÌÎÍÑÒĞÀÖÈÈ ====================
class Student {
private:
    int id;
    std::string name;
    double grade;

public:
    Student(int i = 0, const std::string& n = "", double g = 0.0)
        : id(i), name(n), grade(g) {
    }

    bool operator<(const Student& other) const { return id < other.id; }

    struct CompareByName {
        bool operator()(const Student& a, const Student& b) const {
            return a.name < b.name;
        }
    };

    struct CompareByGrade {
        bool operator()(const Student& a, const Student& b) const {
            return a.grade < b.grade;
        }
    };

    friend std::ostream& operator<<(std::ostream& os, const Student& s) {
        return os << "Student{id:" << s.id << ", name:\"" << s.name
            << "\", grade:" << s.grade << "}";
    }
};

// ==================== PANCAKE SORT ====================
template<typename Container, typename Comparator = std::less<typename Container::value_type>>
void pancake_sort(Container& container, Comparator comp = Comparator()) {
    using SizeType = typename Container::size_type;
    SizeType size = container.size();
    if (size <= 1) return;

    auto flip = [&container](SizeType end_index) {
        SizeType start = 0;
        while (start < end_index) {
            std::swap(container[start], container[end_index]);
            start++;
            end_index--;
        }
        };

    auto find_max_index = [&container, comp](SizeType end_index) {
        SizeType max_index = 0;
        for (SizeType i = 1; i <= end_index; i++) {
            if (comp(container[max_index], container[i])) {
                max_index = i;
            }
        }
        return max_index;
        };

    for (SizeType current_size = size; current_size > 1; current_size--) {
        SizeType max_index = find_max_index(current_size - 1);

        if (max_index != current_size - 1) {
            if (max_index != 0) flip(max_index);
            flip(current_size - 1);
        }
    }
}

// Ïåğåãğóçêà äëÿ ìàññèâîâ
template<typename T, size_t N, typename Comparator = std::less<T>>
void pancake_sort(T(&array)[N], Comparator comp = Comparator()) {
    std::vector<T> temp(std::begin(array), std::end(array));
    pancake_sort(temp, comp);
    std::copy(temp.begin(), temp.end(), array);
}



template<typename Container, typename Comparator = std::less<typename Container::value_type>>
void smooth_sort(Container& container, Comparator comp = Comparator()) {
    using SizeType = typename Container::size_type;
    SizeType n = container.size();

    if (n <= 1) return;

    auto sift_down = [&](SizeType start, SizeType end) {
        SizeType root = start;

        while (2 * root + 1 <= end) {
            SizeType child = 2 * root + 1;
            SizeType swap_idx = root;

            if (comp(container[swap_idx], container[child])) {
                swap_idx = child;
            }

            if (child + 1 <= end && comp(container[swap_idx], container[child + 1])) {
                swap_idx = child + 1;
            }

            if (swap_idx == root) {
                return;
            }
            else {
                std::swap(container[root], container[swap_idx]);
                root = swap_idx;
            }
        }
        };

    for (SizeType i = (n / 2); i > 0; --i) {
        sift_down(i - 1, n - 1);
    }

    for (SizeType i = n - 1; i > 0; --i) {
        std::swap(container[0], container[i]);
        sift_down(0, i - 1);
    }
}

template<typename T, size_t N, typename Comparator = std::less<T>>
void smooth_sort(T(&array)[N], Comparator comp = Comparator()) {
    std::vector<T> temp(std::begin(array), std::end(array));
    smooth_sort(temp, comp);
    std::copy(temp.begin(), temp.end(), array);
}

#endif 