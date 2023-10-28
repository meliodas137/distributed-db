add_executable(DistributedDB main.cpp)

target_link_libraries(DistributedDB PUBLIC tm)
target_link_libraries(DistributedDB PUBLIC utils)