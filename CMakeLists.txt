cmake_minimum_required(VERSION 3.19)

project(omp-npc-ng LANGUAGES C CXX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

function(GroupSourcesByFolder target)
endfunction()

option(OMP_NPC_NG_BOOTSTRAP_ONLY "Configure the scaffold even when vendored open.mp deps are missing." ON)
option(OMP_NPC_NG_BUILD_PAWN_BRIDGE "Build the external Pawn bridge component." OFF)

set(OMP_NPC_NG_DEPS_READY ON)
foreach(_dep
	"libs/omp-sdk/CMakeLists.txt"
	"libs/omp-network/CMakeLists.txt"
	"libs/omp-netcode/CMakeLists.txt")
	if(NOT EXISTS "${PROJECT_SOURCE_DIR}/${_dep}")
		set(OMP_NPC_NG_DEPS_READY OFF)
	endif()
endforeach()

if(OMP_NPC_NG_DEPS_READY)
	add_subdirectory(libs/omp-sdk)
	add_subdirectory(libs/omp-network)
	add_subdirectory(libs/omp-netcode)

	add_subdirectory(src/core)
	if(OMP_NPC_NG_BUILD_PAWN_BRIDGE)
		add_subdirectory(src/pawn_bridge)
	endif()
else()
	if(NOT OMP_NPC_NG_BOOTSTRAP_ONLY)
		message(FATAL_ERROR
			"Missing vendored dependencies. Expected libs/omp-sdk, libs/omp-network and libs/omp-netcode. "
			"See README.md for bootstrap instructions.")
	endif()

	message(WARNING
		"Configuring omp-npc-ng in bootstrap-only mode. "
		"No component binaries will be built until libs/omp-sdk, libs/omp-network and libs/omp-netcode are added.")

	add_custom_target(omp-npc-ng-bootstrap ALL
		COMMENT "omp-npc-ng scaffold configured without vendored open.mp dependencies")
endif()
