add_library(KLibC INTERFACE)
target_link_libraries(KLibC INTERFACE sharedLibC)
target_include_directories(KLibC INTERFACE include)