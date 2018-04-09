include_directories("${BASE_INCLUDE_DIR}")

add_executable(rolesvr main.cpp)

find_package(Threads)

target_link_libraries(rolesvr ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(rolesvr ${PROJECT_SOURCE_DIR}/lib/libbase.a)
