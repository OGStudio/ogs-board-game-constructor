CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Include common CMakeLists.txt.
INCLUDE(${CMAKE_SOURCE_DIR}/../CMakeLists.txt)

# Reference sources.
INCLUDE_DIRECTORIES(src)
# Create executable.
ADD_EXECUTABLE(${BINARY_NAME} src/main.cpp)
# Use C++14, Sol2 requires it.
TARGET_COMPILE_OPTIONS(${BINARY_NAME} PUBLIC "-std=c++14")

# Use ImageIO for macOS.
IF (${OSG_PLATFORM} STREQUAL "macos")
    SET(IMAGE_LINK_LIBS "osgdb_imageio")
# Use libpng for Linux and Windows.
ELSE ()
    SET(IMAGE_LINK_LIBS "osgdb_png" "png")
ENDIF ()

# Link executable with libraries.
TARGET_LINK_LIBRARIES(
    ${BINARY_NAME}
    ${OGS_BGC_LINK_LIBS}
    ${IMAGE_LINK_LIBS}
    lua
)
