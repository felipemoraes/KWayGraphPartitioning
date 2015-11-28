# CmakeLists.txt in src dir

# Adds a library called common from the source files
file(GLOB partition_SRC
    "*.h"
    "*.cc"
)


ADD_LIBRARY( partitionlib ${partition_SRC})
target_link_libraries(partitionlib)



