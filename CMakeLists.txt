# project meta data
project(Skillswitch)
set(main_target "run")

# minimum required cmake version
cmake_minimum_required(VERSION 3.5)

# define source files to be compiled
include(src/CMakeLists.txt)
file(GLOB_RECURSE tmxlite tmxlite/tmxlite/src/*.cpp tmxlite/tmxlite/src/miniz.c)

# add executable and define dependencies
add_executable(${main_target} ${sources} ${tmxlite})

# force C++14 standard and disable custom standard library extensions
set_target_properties(${main_target} PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
)

# add extra warnings to the main target
target_compile_options(${main_target} PRIVATE
	-Wall
	-pedantic
	-Wextra
)

# find system libraries (SFML, Box2d and Lua)
# Ubuntu-specific fix:
set(CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH} /usr/share/SFML/cmake/Modules/)
find_package(SFML 2.3 REQUIRED audio graphics window system)
find_package(Box2D)
find_package(Lua 5.1 REQUIRED)

# include SFML, Box2D, Lua, tmxlite, sol and source directories
target_include_directories(${main_target} PRIVATE
	${SFML_INCLUDE_DIR}
	${BOX2D_INCLUDE_DIR}
	${LUA_INCLUDE_DIR}
	tmxlite/tmxlite/include tmxlite/tmxlite/include/tmxlite/detail tmxlite/SFMLExample/src
	sol2/single/sol
	src
	src/GameStates
)

# link executable to system libraries (SFML, Box2d and Lua)
target_link_libraries(${main_target} ${SFML_LIBRARIES} ${BOX2D_LIBRARIES} ${LUA_LIBRARIES})
