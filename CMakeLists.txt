# general project settings
cmake_minimum_required(VERSION 3.12)
project(BranchAndBoundSmart CXX)

############### ARCHITECTURE-RELATED VARIABLES ###############
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(MACOSX TRUE)
endif()

# control variables
set(COMMAND_ARG "main")

################ PRE-PACKAGE SEARCH VARIABLES SETUP ################
# general variables
set(CMAKE_OSX_ARCHITECTURES "x86_64") # For m1 mac
set(CMAKE_CXX_STANDARD 20)
set(PROJECT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(HOME_INC_DIR ${PROJECT_PATH}/include)
add_compile_options(-Wall)

# Torch related variables
set(TORCH_PREFIX_PATH "./libtorch")
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}" "${TORCH_PREFIX_PATH}")

# NumPy related variables
if(MACOSX)
  set(PYTHON_NUMPY_INCLUDE_DIR "/opt/homebrew/Caskroom/miniforge/base/envs/ML/lib/python3.9/site-packages/numpy/core/include")
endif()

# Google Test related variables
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/af29db7ec28d6df1c7f0f745186884091e602e07.zip
)
FetchContent_MakeAvailable(googletest)

# pybind11 related variables
set(PYBIND_PREFIX_PATH "./extern/pybind11")

######################  PACKAGE DEPENDENCIES  ########################

### 

################# POST-PACKAGE SEARCH VARIABLES SETUP ###############
# Package specific configuration
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")
include_directories(${TORCH_INCLUDE_DIRS})

# setting include root path
include_directories(${HOME_INC_DIR})

# subdirectories
add_subdirectory(include)
add_subdirectory(${PYBIND_PREFIX_PATH}) # for pybind11

###########################################################################
# executables
if(COMMAND_ARG STREQUAL "main")
    add_executable(main src/main.cpp)
elseif (COMMAND_ARG STREQUAL "test")
    add_executable(main src/net.cpp)
endif()

target_link_libraries(
    main    # target 
    "${TORCH_LIBRARIES}" # Torch
    "${Python3_LIBRARIES}" # Python3
    problemNode searchGraph problemParser searchMod pruneMod branchMod Labeler types PlainLabeler # Base
    oneRjSumCj_engine oneRjSumCjNode oneRjSumCjBranch oneRjSumCjPrune oneRjSumCjSearch # OneRjSumCj
    LowerBound PriorityQueue JobWithReleaseDate # Util
)

add_executable(load src/load.cpp)
target_link_libraries(
    load    # target 
    "${TORCH_LIBRARIES}" # Torch
    "${Python3_LIBRARIES}" # Python3
    problemNode searchGraph problemParser searchMod pruneMod branchMod Labeler types PlainLabeler # Base
    oneRjSumCj_engine oneRjSumCjNode oneRjSumCjBranch oneRjSumCjPrune oneRjSumCjSearch # OneRjSumCj
    LowerBound PriorityQueue JobWithReleaseDate # Util
)

# pybind11_add_module(bbgym pybind/base.cpp)
add_library(bbgym MODULE pybind/base.cpp)
target_link_libraries(
  bbgym   # target
  PRIVATE
  pybind11::module # pybind11
  "${Python3_LIBRARIES}" # Python3
  problemNode searchGraph problemParser searchMod pruneMod branchMod Labeler types PlainLabeler # Base
  oneRjSumCj_engine oneRjSumCjNode oneRjSumCjBranch oneRjSumCjPrune oneRjSumCjSearch # OneRjSumCj
  LowerBound PriorityQueue JobWithReleaseDate # Util
)
IF( APPLE )
SET_TARGET_PROPERTIES( bbgym
  PROPERTIES
    LINK_FLAGS "-undefined dynamic_lookup"
    SUFFIX     ".so"
)
ENDIF()
pybind11_extension(bbgym)
pybind11_strip(bbgym)

set_target_properties(bbgym PROPERTIES CXX_VISIBILITY_PRESET "hidden"
                                         CUDA_VISIBILITY_PRESET "hidden")



######################  SELF-DEFINED COMMANDS  ########################
# cmake run
add_custom_target(run
    ./main
    DEPENDS main
    WORKING_DIRECTORY ${PROJECT_PATH}/build
)

add_custom_target(cls
    rm -f *.so && rm -f  *.out && rm -f  load && rm -f  main
    WORKING_DIRECTORY ${PROJECT_PATH}/build
)
