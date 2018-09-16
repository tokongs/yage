project(yage_editor)

add_executable(yage_editor src/main.cpp)
target_link_libraries(yage_editor yage_core)