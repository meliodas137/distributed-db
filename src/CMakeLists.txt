# # Make an automatic library - will be static or dynamic based on user setting
# add_library(ddb test.cpp ${HEADER_LIST})

# # We need this directory, and users of our library will need it too
# target_include_directories(ddb PUBLIC ../include)

add_subdirectory(transaction_manager)
add_subdirectory(utils)
add_subdirectory(data_manager)