# MeltEngine_install.cmake

# Ensure this file is only included, not executed directly
if (NOT DEFINED MELTENGINE_LIB_VERSION)
    message(FATAL_ERROR "Please use the CMake configuration provided in the build directory.")
endif()

# Set installation directories
include(GNUInstallDirs)

# Install the static library
install(TARGETS MeltEngineLib
        EXPORT MeltEngineLibTargets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Install the header files
install(DIRECTORY include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING PATTERN "*.h"
)

# Install the vendors directory (if needed)
install(DIRECTORY vendors/
        DESTINATION ${CMAKE_INSTALL_PREFIX}/vendors
)

# Export the target for use in other projects
install(EXPORT MeltEngineLibTargets
        FILE MeltEngineLibTargets.cmake
        NAMESPACE MeltEngine::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MeltEngine
)

# Create a configuration file for the engine
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/MeltEngineConfig.cmake"
        "include(CMakeFindDependencyMacro)\n"
        "include(GNUInstallDirs)\n"
        "include(CMakeFindPackageHandleStandardArgs)\n\n"
        "find_package_handle_standard_args(MeltEngine DEFAULT_MSG MeltEngineLib)\n\n"
        "set(MeltEngine_LIBRARIES MeltEngineLib)\n"
        "set(MeltEngine_INCLUDE_DIRS \${CMAKE_INSTALL_INCLUDEDIR})\n"
        "mark_as_advanced(MeltEngine_INCLUDE_DIRS)\n"
)

# Install the configuration file
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/MeltEngineConfig.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MeltEngine
)
