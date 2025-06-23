# SPDX-FileCopyrightText: 2022 Linus Jahn <lnj@kaidan.im>
#
# SPDX-License-Identifier: CC0-1.0

include(CMakePackageConfigHelpers)

#add_subdirectory(../../../libomemo-c libomemo-c)
#add_subdirectory(../../../qca qca)

set(OMEMO_CMAKE_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${QXMPPOMEMO_TARGET}")
set(OMEMO_HEADER_DIR "${CMAKE_INSTALL_FULL_INCLUDEDIR}/${QXMPP_TARGET}/Omemo")
set(OMEMO_INSTALL_HEADER_FILES
    QXmppOmemoManager.h
    QXmppOmemoMemoryStorage.h
    QXmppOmemoStorage.h
)
set(OMEMO_SOURCE_FILES
    OmemoCryptoProvider.cpp
    QXmppOmemoData.cpp
    QXmppOmemoManager.cpp
    QXmppOmemoManager_p.cpp
    QXmppOmemoMemoryStorage.cpp
    QXmppOmemoStorage.cpp
)

if(BUILD_SHARED)
    add_library(${QXMPPOMEMO_TARGET} SHARED ${OMEMO_SOURCE_FILES})
else()
    add_library(${QXMPPOMEMO_TARGET} STATIC ${OMEMO_SOURCE_FILES})
endif()


target_link_libraries(${QXMPPOMEMO_TARGET}
    PUBLIC
    ${QXMPP_TARGET}
    Qt${QT_VERSION_MAJOR}::Core
    PRIVATE
)

if (IOS)
    target_link_libraries(${QXMPPOMEMO_TARGET} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../prebuilt-dependencies/ios/qca-qt6.framework"
        "-framework qca-qt6"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../prebuilt-dependencies/ios/libomemo-c.a"
    )
elseif (APPLE)
    if(MACO_TIPAS MATCHES "M1")
        target_link_libraries(${QXMPPOMEMO_TARGET} PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/../../../prebuilt-dependencies/macos_arm/libomemo-c.a"
        )
    elseif(MACO_TIPAS MATCHES "INTELINIS")
        target_link_libraries(${QXMPPOMEMO_TARGET} PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/../../../prebuilt-dependencies/macos_x86/libomemo-c.a"
        )
    endif()
    target_link_libraries(${QXMPPOMEMO_TARGET} PRIVATE
        "-framework qca-qt6"
    )
    include_directories("/Library/Frameworks/qca-qt6.framework/Versions/2/Headers")
    include_directories("/usr/local/include/omemo")
else ()
    target_link_libraries(${QXMPPOMEMO_TARGET} PRIVATE qca-qt6)# qca-cyrus-sasl qca-gnupg qca-logger qca-ossl qca-softstore)
endif()

target_include_directories(${QXMPPOMEMO_TARGET}
    INTERFACE
    ${OMEMO_HEADER_DIR}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${PROJECT_BINARY_DIR}/src
)

generate_export_header(${QXMPPOMEMO_TARGET} BASE_NAME qxmppomemo)

install(
    FILES ${OMEMO_INSTALL_HEADER_FILES} ${CMAKE_CURRENT_BINARY_DIR}/qxmppomemo_export.h
    DESTINATION ${OMEMO_HEADER_DIR}
)

set_target_properties(${QXMPPOMEMO_TARGET} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${SO_VERSION}
    EXPORT_NAME Omemo
)

install(
    TARGETS ${QXMPPOMEMO_TARGET}
    EXPORT QXmppOmemoTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    EXPORT QXmppOmemoTargets
    DESTINATION ${OMEMO_CMAKE_DIR}
    FILE QXmppOmemo.cmake
    NAMESPACE QXmpp::
    COMPONENT Devel
)

# export(
#     TARGETS ${QXMPPOMEMO_TARGET}
#     FILE QXmppOmemo.cmake
# )

configure_package_config_file(
    QXmppOmemoConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${QXMPPOMEMO_TARGET}Config.cmake
    INSTALL_DESTINATION ${OMEMO_CMAKE_DIR}
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${QXMPPOMEMO_TARGET}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/${QXMPPOMEMO_TARGET}Config.cmake
          ${CMAKE_CURRENT_BINARY_DIR}/${QXMPPOMEMO_TARGET}ConfigVersion.cmake
    DESTINATION ${OMEMO_CMAKE_DIR}
    COMPONENT Devel
)
