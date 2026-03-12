file(GLOB_RECURSE OMP_NPC_NG_CORE_SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

add_library(NPCs SHARED ${OMP_NPC_NG_CORE_SOURCES})

target_link_libraries(NPCs PRIVATE
	OMP-SDK
	OMP-NetCode
)

target_include_directories(NPCs PRIVATE
	${PROJECT_SOURCE_DIR}/libs/cpp-httplib
)

target_compile_definitions(NPCs PRIVATE
	OMP_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
	OMP_VERSION_MINOR=${PROJECT_VERSION_MINOR}
	OMP_VERSION_PATCH=${PROJECT_VERSION_PATCH}
)

set_target_properties(NPCs PROPERTIES
	OUTPUT_NAME NPCs
	PREFIX ""
)

if(MSVC)
	set_target_properties(NPCs PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/components"
	)
else()
	set_target_properties(NPCs PROPERTIES
		LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/components"
	)
endif()
