cmake_minimum_required(VERSION 3.9.2) # Проверка версии CMake.
									# Если версия установленой программы
									# старее указаной, произайдёт аварийный выход.
project(hw1 C)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ------------------------------------------------------------------------------
# system configuration choice
# ------------------------------------------------------------------------------

if ("${TARGET_CPU}" STREQUAL "amd64")
    set (CMAKE_SIZEOF_VOID_P 8)

    set_property (GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS TRUE)
    set_property (GLOBAL PROPERTY FIND_LIBRARY_USE_LIB32_PATHS FALSE)
elseif ("${TARGET_CPU}" STREQUAL "x86")
    set (CMAKE_SIZEOF_VOID_P 4)

    set_property (GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS FALSE)
    set_property (GLOBAL PROPERTY FIND_LIBRARY_USE_LIB32_PATHS TRUE)

    if (GCC)
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
        set (CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -m32")
    endif ()
#else ()
#   message (FATAL_ERROR "Unsupported CPU: ${TARGET_CPU}")
endif ()

# ------------------------------------------------------------------------------
# Valgrind
# ------------------------------------------------------------------------------

set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --leak-check=full")
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --track-fds=yes")
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --trace-children=yes")
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --error-exitcode=1")

# ------------------------------------------------------------------------------
# Main Executable
# ------------------------------------------------------------------------------

add_executable(main hw1.c)		# Создает исполняемый файл с именем main
									# из исходника main.cpp