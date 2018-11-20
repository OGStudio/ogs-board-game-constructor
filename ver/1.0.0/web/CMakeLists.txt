CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(OGS_BGC_DIR ${CMAKE_SOURCE_DIR}/../../../../ogs-board-game-constructor)

# Include common CMakeLists.txt.
INCLUDE(${CMAKE_SOURCE_DIR}/../CMakeLists.txt)

# Reference sources.
INCLUDE_DIRECTORIES(src)
# Create executable (aka HTML page).
ADD_EXECUTABLE(${BINARY_NAME} src/main.cpp)
# Use C++14, Sol2 requires it.
TARGET_COMPILE_OPTIONS(${BINARY_NAME} PUBLIC "-std=c++14")

SET(IMAGE_LINK_LIBS "osgdb_png")

# Link executable with libraries.
TARGET_LINK_LIBRARIES(
    ${BINARY_NAME}
    ${OGS_BGC_LINK_LIBS}
    ${IMAGE_LINK_LIBS}
    lua
)

# Set special build flags:
# * -O3: make compact binary, critical for web
# * -s USE_SDL=2: provide SDL2
# * -s ALLOW_MEMORY_GROWTH=1: allow total memory used to increase when necessary
# * -s USE_LIBPNG=1: use libpng
# * -s USE_ZLIB=1: use zlib, necessary for libpng
# * -s WASM=0: disable WebAssembly because it's too new
SET(BUILD_FLAGS "-O3 -s USE_SDL=2 -s ALLOW_MEMORY_GROWTH=1 -s USE_LIBPNG=1 -s USE_ZLIB=1 -s WASM=0")
ADD_DEFINITIONS(${BUILD_FLAGS})

# Make Emscripten generate ready-to-open HTML page.
SET(CMAKE_EXECUTABLE_SUFFIX ".html")
# Link with special build flags.
SET_TARGET_PROPERTIES(${BINARY_NAME} PROPERTIES LINK_FLAGS ${BUILD_FLAGS})
