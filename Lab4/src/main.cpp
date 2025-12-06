#include "sorts.h"
#include "advanced_graph.h"
#include <iostream>
#include <vector>
#include <string>

// Вспомогательная функция для вывода
template<typename Container>
void print(const std::string& label, const Container& container) {
    std::cout << label << ": ";
    for (const auto& item : container) std::cout << item << " ";
    std::cout << std::endl;
}

// Демонстрация сортировок
void demonstrate_sorts() {
    std::cout << "=== ДЕМОНСТРАЦИЯ СОРТИРОВОК ===" << std::endl;

    // 1. Массивы и векторы встроенных типов
    std::cout << "\n1. Встроенные типы:" << std::endl;

    int arr_int[] = { 5, 2, 8, 1, 9 };
    print("Массив int (до):", arr_int);
    pancake_sort(arr_int);
    print("После pancake_sort:", arr_int);

    std::vector<double> vec_double = { 5.5, 2.2, 8.8, 1.1, 9.9 };
    print("Вектор double (до):", vec_double);
    smooth_sort(vec_double);
    print("После smooth_sort:", vec_double);

    // 2. Строки
    std::cout << "\n2. Строки:" << std::endl;
    std::vector<std::string> words = { "zebra", "apple", "banana", "cherry" };
    print("Строки (до):", words);
    pancake_sort(words);
    print("После сортировки:", words);

    // 3. Пользовательский класс Student
    std::cout << "\n3. Пользовательский класс Student:" << std::endl;

    std::vector<Student> students = {
        Student(3, "Alice", 4.5),
        Student(1, "Bob", 3.8),
        Student(4, "Charlie", 4.2),
        Student(2, "Diana", 4.9)
    };

    std::cout << "До сортировки:" << std::endl;
    for (const auto& s : students) std::cout << "  " << s << std::endl;

    // Сортировка по ID (по умолчанию)
    std::vector<Student> students_by_id = students;
    pancake_sort(students_by_id);
    std::cout << "\nПосле сортировки по ID:" << std::endl;
    for (const auto& s : students_by_id) std::cout << "  " << s << std::endl;

    // Сортировка по имени
    std::vector<Student> students_by_name = students;
    pancake_sort(students_by_name, Student::CompareByName());
    std::cout << "\nПосле сортировки по имени:" << std::endl;
    for (const auto& s : students_by_name) std::cout << "  " << s << std::endl;

    // Сортировка по оценке
    std::vector<Student> students_by_grade = students;
    smooth_sort(students_by_grade, Student::CompareByGrade());
    std::cout << "\nПосле сортировки по оценке:" << std::endl;
    for (const auto& s : students_by_grade) std::cout << "  " << s << std::endl;
}

// Демонстрация графа
void demonstrate_graph() {
    std::cout << "\n\n=== ДЕМОНСТРАЦИЯ ГРАФА ===" << std::endl;

    AdvancedWirthGraph<int> graph;

    // 1. Добавление вершин
    std::cout << "\n1. Добавление вершин:" << std::endl;
    for (int i = 1; i <= 5; i++) {
        graph.add_vertex(i);
    }
    std::cout << "Добавлено вершин: " << graph.size() << std::endl;

    // 2. Добавление ребер
    std::cout << "\n2. Добавление ребер:" << std::endl;
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);
    graph.add_edge(3, 4);
    graph.add_edge(4, 5);
    graph.add_edge(5, 1);
    graph.add_edge(1, 3);

    std::cout << "Граф после добавления ребер:" << std::endl;
    std::cout << graph << std::endl;

    // 3. Проверки
    std::cout << "\n3. Проверки:" << std::endl;
    std::cout << "Есть вершина 3: " << (graph.has_vertex(3) ? "Да" : "Нет") << std::endl;
    std::cout << "Есть ребро 1-2: " << (graph.has_edge(1, 2) ? "Да" : "Нет") << std::endl;
    std::cout << "Есть ребро 2-5: " << (graph.has_edge(2, 5) ? "Да" : "Нет") << std::endl;
    std::cout << "Степень вершины 1: " << graph.vertex_degree(1) << std::endl;

    // 4. Итераторы
    std::cout << "\n4. Итераторы:" << std::endl;
    std::cout << "Все вершины: ";
    for (auto it = graph.vertex_begin(); it != graph.vertex_end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Смежные с 1: ";
    for (auto it = graph.adjacent_begin(1); it != graph.adjacent_end(1); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 5. Удаление
    std::cout << "\n5. Удаление:" << std::endl;
    graph.remove_edge(1, 3);
    std::cout << "После удаления ребра 1-3:" << std::endl;
    std::cout << graph << std::endl;

    graph.remove_vertex(5);
    std::cout << "После удаления вершины 5:" << std::endl;
    std::cout << graph << std::endl;

    // 6. Исключения
    std::cout << "\n6. Обработка исключений:" << std::endl;
    try {
        graph.add_vertex(2); // Уже существует
    }
    catch (const GraphException& e) {
        std::cout << "Поймано исключение: " << e.what() << std::endl;
    }

    // 7. Пользовательский тип для графа
    std::cout << "\n7. Граф с пользовательским типом:" << std::endl;
    AdvancedWirthGraph<std::string> city_graph;
    city_graph.add_vertex("Москва");
    city_graph.add_vertex("СПб");
    city_graph.add_vertex("Казань");

    city_graph.add_edge("Москва", "СПб");
    city_graph.add_edge("Москва", "Казань");

    std::cout << city_graph << std::endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    try {
        std::cout << "Лабораторная работа №4: Обобщенное программирование и STL\n" << std::endl;

        demonstrate_sorts();    // Часть 1: Сортировки
        demonstrate_graph();    // Часть 2: Граф

        std::cout << "\nВсе демонстрации завершены успешно!" << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
