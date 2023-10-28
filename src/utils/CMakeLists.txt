# Make an automatic library - will be static or dynamic based on user setting
add_library(utils utils.cpp ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(utils PUBLIC ../../include)

