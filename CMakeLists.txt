# CROSS COMPILER SETTING
SET(CMAKE_SYSTEM_NAME Generic)
CMAKE_MINIMUM_REQUIRED (VERSION 3.10.0)

# THE VERSION NUMBER
SET (MCUXPRESSO_CMAKE_FORMAT_MAJOR_VERSION 2)
SET (MCUXPRESSO_CMAKE_FORMAT_MINOR_VERSION 0)

include(ide_overrides.cmake OPTIONAL)

if(CMAKE_SCRIPT_MODE_FILE)
message("${MCUXPRESSO_CMAKE_FORMAT_MAJOR_VERSION}")
return()
endif()


# ENABLE ASM
ENABLE_LANGUAGE(ASM)

SET(CMAKE_STATIC_LIBRARY_PREFIX)
SET(CMAKE_STATIC_LIBRARY_SUFFIX)

SET(CMAKE_EXECUTABLE_LIBRARY_PREFIX)
SET(CMAKE_EXECUTABLE_LIBRARY_SUFFIX)

# CURRENT DIRECTORY
SET(ProjDirPath ${CMAKE_CURRENT_SOURCE_DIR})

SET(EXECUTABLE_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})
SET(LIBRARY_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})


project(prulko_kobusx)

set(MCUX_BUILD_TYPES debug release ddr_debug ddr_release flash_debug flash_release)

set(MCUX_SDK_PROJECT_NAME prulko_kobusx.elf)

if (NOT DEFINED SdkRootDirPath)
SET(SdkRootDirPath ${ProjDirPath}/)
endif()

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

get_filename_component(ParentDirPath "${ProjDirPath}" DIRECTORY)

message("Project Directory Path: ${ProjDirPath}")
message("Path to prulko: ${ProjDirPath}/../prulko")

message("ParentDirPath Directory Path: ${ParentDirPath}")

add_executable(${MCUX_SDK_PROJECT_NAME}
"${ProjDirPath}/board/board.c"
"${ProjDirPath}/board/board.h"
"${ProjDirPath}/board/clock_config.c"
"${ProjDirPath}/board/clock_config.h"
"${ProjDirPath}/board/fsl_iomuxc.h"
"${ProjDirPath}/board/pin_mux.c"
"${ProjDirPath}/board/pin_mux.h"
"${ProjDirPath}/remoteproc/empty_rsc_table.c"
"${ProjDirPath}/source/main.c"
"${ProjDirPath}/source/adc/ads8028.h"
"${ProjDirPath}/source/adc/ads8028.c"
"${ProjDirPath}/source/digitals/digitals.h"
"${ProjDirPath}/source/digitals/digitals.c"
"${ProjDirPath}/source/timer/cycle_timer.h"
"${ProjDirPath}/source/timer/cycle_timer.c"
"${ParentDirPath}/../../../RotateSensor/RotatorV2/workspace/shared/PulseLink/bitcoding.c"
"${ParentDirPath}/../../../RotateSensor/RotatorV2/workspace/shared/PulseLink/bitcoding.h"
"${ParentDirPath}/prulko/hardadclevel.c"
"${ParentDirPath}/prulko/hardadclevel.h"
"${ParentDirPath}/prulko/harddepthlevel.c"
"${ParentDirPath}/prulko/harddepthlevel.h"
"${ParentDirPath}/prulko/hardrpmlevel.c"
"${ParentDirPath}/prulko/hardrpmlevel.h"
"${ParentDirPath}/prulko/hardfrequencylevel.c"
"${ParentDirPath}/prulko/hardfrequencylevel.h"
"${ParentDirPath}/prulko/kobus_pru.h"
"${ParentDirPath}/prulko/prutypes.h"
"${ProjDirPath}/source/frequency/ring_buffer.h"
"${ProjDirPath}/source/frequency/ring_buffer.c"
)

target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PRIVATE
    KOBUS_X
    SDK_DEBUGCONSOLE=2
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
${ProjDirPath}/board
${ProjDirPath}/evkmimx8mp/driver_examples/ecspi/polling_b2b_transfer/master
)


include(${ProjDirPath}/all_lib_device.cmake)

IF(NOT DEFINED TARGET_LINK_SYSTEM_LIBRARIES)
SET(TARGET_LINK_SYSTEM_LIBRARIES "-lm -lc -lgcc -lnosys")
ENDIF()

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE ${TARGET_LINK_SYSTEM_LIBRARIES})

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)

ADD_CUSTOM_COMMAND(TARGET ${MCUX_SDK_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_OBJCOPY}
-Obinary ${EXECUTABLE_OUTPUT_PATH}/${MCUX_SDK_PROJECT_NAME} ${EXECUTABLE_OUTPUT_PATH}/prulko_kobusx.bin)

set_target_properties(${MCUX_SDK_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES "output.map;${EXECUTABLE_OUTPUT_PATH}/prulko_kobusx.bin")

