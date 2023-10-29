# Make an automatic library - will be static or dynamic based on user setting
add_library(dm DataManager.cpp data/data.cpp ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(dm PUBLIC ../../include)

