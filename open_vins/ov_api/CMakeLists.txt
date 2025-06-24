cmake_minimum_required(VERSION 3.3)
project(ov_api)

# Header-only wrapper so we just install the header
install(DIRECTORY include/
        DESTINATION include/ov_api
        FILES_MATCHING PATTERN "*.hpp")
