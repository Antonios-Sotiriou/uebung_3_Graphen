cmake_minimum_required (VERSION 3.20)

# Aktivieren Sie Hot Reload für MSVC-Compiler, sofern unterstützt.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (find_path)

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_executable (find_path "source/main.cpp" "source/graph.cpp" "source/printStructs.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET find_path PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(find_path PUBLIC "${PROJECT_SOURCE_DIR}/")

set(PROJECT_SOURCE_DIR "${PROJECT_SOURCE_DIR}")
set(PROJECT_DATA_DIR "${PROJECT_SOURCE_DIR}/data_files/")
configure_file("main.h.in" "${PROJECT_SOURCE_DIR}/headers/cmake_variables.h")

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.