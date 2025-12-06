cmake_minimum_required(VERSION 3.10)
project(GTestProject)

# Устанавливаем стандарт C++17 (для if constexpr)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Устанавливаем флаг для динамической линковки CRT для Google Test
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Загрузка Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# Добавляем тестовый исполняемый файл
add_executable(my_gtest Tests_for_lab4/test.cpp)

# Включаем пути для заголовочных файлов
target_include_directories(my_gtest PRIVATE 
    .
    Tests_for_lab4  
    lab4_last_version
    ${googletest_SOURCE_DIR}/googletest/include
)

# Для MSVC устанавливаем динамическую линковку CRT
if(MSVC)
    target_compile_options(my_gtest PRIVATE /MDd)
endif()

# Линкуем с Google Test
target_link_libraries(my_gtest PRIVATE gtest gtest_main)

# Включение тестирования
enable_testing()
add_test(NAME AllTests COMMAND my_gtest)

# Покрытие кода (только для GCC/Clang)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    option(ENABLE_COVERAGE "Enable code coverage reporting" ON)
    
    if(ENABLE_COVERAGE)
        message(STATUS "Code coverage enabled for GCC/Clang")
        
        # Флаги для coverage
        target_compile_options(my_gtest PRIVATE
            -fprofile-arcs
            -ftest-coverage
            -O0
            -g
        )
        
        target_link_libraries(my_gtest PRIVATE gcov)
    endif()
endif()