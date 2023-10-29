# Make an automatic library - will be static or dynamic based on user setting
add_library(tm TransactionManager.cpp operation/operation.cpp transaction/transaction.cpp graph/Graph.cpp ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(tm PUBLIC ../../include)

target_link_libraries(tm PRIVATE dm)