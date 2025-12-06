cmake_minimum_required(VERSION 3.16)
project(RestaurantManagementSystem)

# Настройки C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Критически важные настройки для покрытия кода
if(MSVC)
    # Включить отладочную информацию в Release
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi /Od")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG")
    # Отключить оптимизацию для точного покрытия
    add_compile_options($<$<CONFIG:Release>:/Od>)
endif()

# Автоматическая загрузка GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Основные исходные файлы проекта (БЕЗ main.cpp для библиотеки)
file(GLOB MAIN_SOURCES 
    "lab2_last_version/*.cpp"
)
# Убираем main.cpp из библиотечных файлов
list(FILTER MAIN_SOURCES EXCLUDE REGEX ".*main\\.cpp$")

# Тестовые файлы
file(GLOB TEST_SOURCES "Tests/*.cpp")

# Создаем СТАТИЧЕСКУЮ БИБЛИОТЕКУ из основного кода
add_library(restaurant_lib STATIC ${MAIN_SOURCES})

# Создаем основное приложение ТОЛЬКО с main.cpp
add_executable(restaurant_app "lab2_last_version/main.cpp")
# Линкуем основное приложение с библиотекой
target_link_libraries(restaurant_app restaurant_lib)

# Создаем тестовое приложение
add_executable(restaurant_tests ${TEST_SOURCES})
# Линкуем тесты с библиотекой И GoogleTest
target_link_libraries(restaurant_tests restaurant_lib GTest::gtest GTest::gtest_main)

# Включаем директории с заголовками
target_include_directories(restaurant_lib PUBLIC "lab2_last_version")
target_include_directories(restaurant_tests PRIVATE "lab2_last_version" "Tests")

# Настройки для Visual Studio
if(MSVC)
    target_compile_options(restaurant_app PRIVATE /W4)
    target_compile_options(restaurant_tests PRIVATE /W4)
    target_compile_options(restaurant_lib PRIVATE /W4)
endif()

# Специальная цель для покрытия кода
add_custom_target(coverage
    COMMAND OpenCppCoverage --sources "${CMAKE_SOURCE_DIR}/lab2_last_version" 
            --modules $<TARGET_FILE:restaurant_tests> 
            --export_type=html:coverage_report 
            -- $<TARGET_FILE:restaurant_tests>
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating code coverage report..."
    DEPENDS restaurant_tests
)