# NOTE This is a common CMakeLists.txt to be included by each platform's
# NOTE specific CMakeLists.txt.
# This CMakeLists.txt requires the following variables:
# * OGS_BGC_DIR
# This CMakeLists.txt provides the following variables outside:
# * OSGCPE_DIR
# * OGS_BGC_BINARY_NAME
# * OGS_BGC_LINK_LIBS

PROJECT(OGS_BGC)
SET(BINARY_NAME "ogs-bgc-1.0.0")
SET(PROJECT_DIR ${OGS_BGC_DIR})
SET(OSGCPE_DIR ${PROJECT_DIR}/../openscenegraph-cross-platform-examples)
SET(SOL2_DIR ${PROJECT_DIR}/../sol2)

# Build OpenSceneGraph statically.
INCLUDE(${OSGCPE_DIR}/libs/OpenSceneGraph/CMakeLists.txt)
# Build Lua statically.
INCLUDE(${OSGCPE_DIR}/libs/lua/CMakeLists.txt)
# Reference Sol2 header-only library.
INCLUDE_DIRECTORIES(${SOL2_DIR})

# Reference resources.
INCLUDE_DIRECTORIES(${PROJECT_DIR}/dat)
# Reference embedded scripting API.
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})

# Provide libraries to link with.
SET(
    OGS_BGC_LINK_LIBS
    osgViewer
    osgUtil
    osgDB
    # osgDB plugins start.
    osgdb_osg
    osgdb_serializers_osg
    # osgDB plugins end.
    osgGA
    osg
    OpenThreads
)
