add_library(OMPNPCNGPawn SHARED
	${PROJECT_SOURCE_DIR}/libs/pawn/source/amx/amx.c
	bridge_runtime.cpp
	component_main.cpp
	npc_natives.cpp
	pawn_natives_main.cpp
)

target_link_libraries(OMPNPCNGPawn PRIVATE
	OMP-SDK
)

target_include_directories(OMPNPCNGPawn PRIVATE
	${PROJECT_SOURCE_DIR}/libs
	${PROJECT_SOURCE_DIR}/libs/pawn/include
	${PROJECT_SOURCE_DIR}/libs/pawn/include/amx
	${PROJECT_SOURCE_DIR}/libs/pawn/source/amx
)

set_target_properties(OMPNPCNGPawn PROPERTIES
	OUTPUT_NAME OMPNPCNGPawn
	PREFIX ""
)

if(MSVC)
	set_target_properties(OMPNPCNGPawn PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/components"
	)
else()
	set_target_properties(OMPNPCNGPawn PROPERTIES
		LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/components"
	)
endif()

target_compile_definitions(OMPNPCNGPawn PRIVATE
	LINUX=1
	OMP_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
	OMP_VERSION_MINOR=${PROJECT_VERSION_MINOR}
	OMP_VERSION_PATCH=${PROJECT_VERSION_PATCH}
)
