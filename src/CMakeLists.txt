# SPDX-FileCopyrightText: 2017 Niels Ole Salscheider <niels_ole@salscheider-online.de>
#
# SPDX-License-Identifier: CC0-1.0

include(GenerateExportHeader)

# extra definitions, only for src/
add_definitions(
    -DQT_NO_CAST_FROM_ASCII
)

set(INSTALL_HEADER_FILES
    # Base
    base/QXmppArchiveIq.h
    base/QXmppBindIq.h
    base/QXmppBitsOfBinaryContentId.h
    base/QXmppBitsOfBinaryData.h
    base/QXmppBitsOfBinaryDataList.h
    base/QXmppBitsOfBinaryIq.h
    base/QXmppBookmarkSet.h
    base/QXmppByteStreamIq.h
    base/QXmppColorGeneration.h
    base/QXmppDataForm.h
    base/QXmppDataFormBase.h
    base/QXmppDiscoveryIq.h
    base/QXmppE2eeMetadata.h
    base/QXmppEncryptedFileSource.h
    base/QXmppElement.h
    base/QXmppEntityTimeIq.h
    base/QXmppError.h
    base/QXmppExtension.h
    base/QXmppExternalService.h
    base/QXmppExternalServiceDiscoveryIq.h
    base/QXmppFallback.h
    base/QXmppFileMetadata.h
    base/QXmppFileShare.h
    base/QXmppFutureUtils_p.h
    base/QXmppGeolocItem.h
    base/QXmppGlobal.h
    base/QXmppHash.h
    base/QXmppHttpFileSource.h
    base/QXmppHttpUploadIq.h
    base/QXmppIbbIq.h
    base/QXmppIq.h
    base/QXmppJingleIq.h
    base/QXmppJingleData.h
    base/QXmppLogger.h
    base/QXmppMamIq.h
    base/QXmppMessage.h
    base/QXmppMessageReaction.h
    base/QXmppMixConfigItem.h
    base/QXmppMixInfoItem.h
    base/QXmppMixInvitation.h
    base/QXmppMixIq.h
    base/QXmppMixIq_p.h
    base/QXmppMixParticipantItem.h
    base/QXmppMucIq.h
    base/QXmppNonza.h
    base/QXmppNonSASLAuth.h
    base/QXmppOutOfBandUrl.h
    base/QXmppPingIq.h
    base/QXmppPresence.h
    base/QXmppPromise.h
    base/QXmppPubSubAffiliation.h
    base/QXmppPubSubEvent.h
    base/QXmppPubSubIq_p.h
    base/QXmppPubSubBaseItem.h
    base/QXmppPubSubMetadata.h
    base/QXmppPubSubNodeConfig.h
    base/QXmppPubSubPublishOptions.h
    base/QXmppPubSubSubscribeOptions.cpp
    base/QXmppPubSubSubscription.h
    base/QXmppPubSubSubAuthorization.h
    base/QXmppPushEnableIq.h
    base/QXmppRegisterIq.h
    base/QXmppResultSet.h
    base/QXmppRosterIq.h
    base/QXmppRpcIq.h
    base/QXmppSasl2UserAgent.h
    base/QXmppSendResult.h
    base/QXmppSocks.h
    base/QXmppStanza.h
    base/QXmppStreamError.h
    base/QXmppStreamFeatures.h
    base/QXmppStun.h
    base/QXmppTask.h
    base/QXmppThumbnail.h
    base/QXmppTrustMessageElement.h
    base/QXmppTrustMessageKeyOwner.h
    base/QXmppTrustMessages.h
    base/QXmppUserTuneItem.h
    base/QXmppUtils.h
    base/QXmppUri.h
    base/QXmppVCardIq.h
    base/QXmppVersionIq.h
    base/compat/QXmppSessionIq.h
    base/compat/QXmppStartTlsPacket.h
    base/compat/QXmppPubSubIq.h
    base/compat/QXmppPubSubItem.h

    # Client
    client/QXmppAccountMigrationManager.h
    client/QXmppArchiveManager.h
    client/QXmppAtmManager.h
    client/QXmppAtmTrustMemoryStorage.h
    client/QXmppAtmTrustStorage.h
    client/QXmppAttentionManager.h
    client/QXmppAuthenticationError.h
    client/QXmppBindError.h
    client/QXmppBlockingManager.h
    client/QXmppBookmarkManager.h
    client/QXmppCallInviteManager.h
    client/QXmppCarbonManager.h
    client/QXmppCarbonManagerV2.h
    client/QXmppClient.h
    client/QXmppClientExtension.h
    client/QXmppConfiguration.h
    client/QXmppCredentials.h
    client/QXmppDiscoveryManager.h
    client/QXmppE2eeExtension.h
    client/QXmppEntityTimeManager.h
    client/QXmppExternalServiceDiscoveryManager.h
    client/QXmppFileSharingManager.h
    client/QXmppFileSharingProvider.h
    client/QXmppHttpFileSharingProvider.h
    client/QXmppHttpUploadManager.h
    client/QXmppInvokable.h
    client/QXmppIqHandling.h
    client/QXmppJingleMessageInitiationManager.h
    client/QXmppMamManager.h
    client/QXmppMessageHandler.h
    client/QXmppMessageReceiptManager.h
    client/QXmppMixManager.h
    client/QXmppMovedManager.h
    client/QXmppMucManager.h
    client/QXmppOutgoingClient.h
    client/QXmppRegistrationManager.h
    client/QXmppPubSubEventHandler.h
    client/QXmppPubSubManager.h
    client/QXmppRemoteMethod.h
    client/QXmppRosterManager.h
    client/QXmppRpcManager.h
    client/QXmppSendStanzaParams.h
    client/QXmppTransferManager.h
    client/QXmppTransferManager_p.h
    client/QXmppTrustLevel.h
    client/QXmppTrustManager.h
    client/QXmppTrustMemoryStorage.h
    client/QXmppTrustSecurityPolicy.h
    client/QXmppTrustStorage.h
    client/QXmppUploadRequestManager.h
    client/QXmppUserTuneManager.h
    client/QXmppUserLocationManager.h
    client/QXmppVCardManager.h
    client/QXmppVersionManager.h

    # Server
    server/QXmppDialback.h
    server/QXmppIncomingClient.h
    server/QXmppIncomingServer.h
    server/QXmppOutgoingServer.h
    server/QXmppPasswordChecker.h
    server/QXmppServer.h
    server/QXmppServerExtension.h
    server/QXmppServerPlugin.h
)

set(SOURCE_FILES
    # Base
    base/Stream.cpp
    base/QXmppArchiveIq.cpp
    base/QXmppBindIq.cpp
    base/QXmppBitsOfBinaryContentId.cpp
    base/QXmppBitsOfBinaryData.cpp
    base/QXmppBitsOfBinaryIq.cpp
    base/QXmppBookmarkSet.cpp
    base/QXmppByteStreamIq.cpp
    base/QXmppColorGeneration.cpp
    base/QXmppDataForm.cpp
    base/QXmppDataFormBase.cpp
    base/QXmppDiscoveryIq.cpp
    base/QXmppElement.cpp
    base/QXmppEncryptedFileSource.cpp
    base/QXmppEntityTimeIq.cpp
    base/QXmppError.cpp
    base/QXmppExternalServiceDiscoveryIq.cpp
    base/QXmppFileMetadata.cpp
    base/QXmppFileShare.cpp
    base/QXmppGeolocItem.cpp
    base/QXmppGlobal.cpp
    base/QXmppHash.cpp
    base/QXmppHashing.cpp
    base/QXmppHttpFileSource.cpp
    base/QXmppHttpUploadIq.cpp
    base/QXmppIbbIq.cpp
    base/QXmppIq.cpp
    base/QXmppJingleData.cpp
    base/QXmppLogger.cpp
    base/QXmppMamIq.cpp
    base/QXmppMessage.cpp
    base/QXmppMessageReaction.cpp
    base/QXmppMixInvitation.cpp
    base/QXmppMixIq.cpp
    base/QXmppMixItems.cpp
    base/QXmppMucIq.cpp
    base/QXmppNonza.cpp
    base/QXmppNonSASLAuth.cpp
    base/QXmppOutOfBandUrl.cpp
    base/QXmppPacket.cpp
    base/QXmppPingIq.cpp
    base/QXmppPresence.cpp
    base/QXmppPubSubAffiliation.cpp
    base/QXmppPubSubEvent.cpp
    base/QXmppPubSubIq.cpp
    base/QXmppPubSubBaseItem.cpp
    base/QXmppPubSubMetadata.cpp
    base/QXmppPubSubNodeConfig.cpp
    base/QXmppPubSubSubscribeOptions.cpp
    base/QXmppPubSubSubscription.cpp
    base/QXmppPubSubSubAuthorization.cpp
    base/QXmppPushEnableIq.cpp
    base/QXmppRegisterIq.cpp
    base/QXmppResultSet.cpp
    base/QXmppRosterIq.cpp
    base/QXmppRpcIq.cpp
    base/QXmppSasl.cpp
    base/QXmppSocks.cpp
    base/QXmppStanza.cpp
    base/QXmppStreamFeatures.cpp
    base/QXmppStreamInitiationIq.cpp
    base/QXmppStreamManagement.cpp
    base/QXmppStun.cpp
    base/QXmppTask.cpp
    base/QXmppThumbnail.cpp
    base/QXmppTrustMessages.cpp
    base/QXmppUri.cpp
    base/QXmppUserTuneItem.cpp
    base/QXmppUtils.cpp
    base/QXmppVCardIq.cpp
    base/QXmppVersionIq.cpp
    base/compat/removed_api.cpp
    base/hsluv/hsluv.c
    # to trigger MOC
    base/XmppSocket.h

    # Client
    client/QXmppAccountMigrationManager.cpp
    client/QXmppArchiveManager.cpp
    client/QXmppAtmManager.cpp
    client/QXmppAtmTrustMemoryStorage.cpp
    client/QXmppAtmTrustStorage.cpp
    client/QXmppAttentionManager.cpp
    client/QXmppBlockingManager.cpp
    client/QXmppBookmarkManager.cpp
    client/QXmppCallInviteManager.cpp
    client/QXmppCarbonManager.cpp
    client/QXmppCarbonManagerV2.cpp
    client/QXmppClient.cpp
    client/QXmppClientExtension.cpp
    client/QXmppConfiguration.cpp
    client/QXmppDiscoveryManager.cpp
    client/QXmppE2eeExtension.cpp
    client/QXmppEntityTimeManager.cpp
    client/QXmppExternalServiceDiscoveryManager.cpp
    client/QXmppFileSharingManager.cpp
    client/QXmppHttpFileSharingProvider.cpp
    client/QXmppHttpUploadManager.cpp
    client/QXmppInvokable.cpp
    client/QXmppIqHandling.cpp
    client/QXmppJingleMessageInitiationManager.cpp
    client/QXmppMamManager.cpp
    client/QXmppMessageReceiptManager.cpp
    client/QXmppMixManager.cpp
    client/QXmppMovedManager.cpp
    client/QXmppMucManager.cpp
    client/QXmppOutgoingClient.cpp
    client/QXmppRosterManager.cpp
    client/QXmppRegistrationManager.cpp
    client/QXmppPubSubManager.cpp
    client/QXmppRemoteMethod.cpp
    client/QXmppRpcManager.cpp
    client/QXmppSaslManager.cpp
    client/QXmppSendStanzaParams.cpp
    client/QXmppTransferManager.cpp
    client/QXmppTrustManager.cpp
    client/QXmppTrustMemoryStorage.cpp
    client/QXmppTrustStorage.cpp
    client/QXmppUploadRequestManager.cpp
    client/QXmppUserLocationManager.cpp
    client/QXmppUserTuneManager.cpp
    client/QXmppVCardManager.cpp
    client/QXmppVersionManager.cpp
    client/compat/removed_api.cpp

    # Server
    server/QXmppDialback.cpp
    server/QXmppIncomingClient.cpp
    server/QXmppIncomingServer.cpp
    server/QXmppOutgoingServer.cpp
    server/QXmppPasswordChecker.cpp
    server/QXmppServer.cpp
    server/QXmppServerExtension.cpp
    server/QXmppServerPlugin.cpp
)

if(WITH_GSTREAMER)
    set(SOURCE_FILES
    ${SOURCE_FILES}
    #modified addind call manager here
    client/QXmppCall.cpp
    client/QXmppCallManager.cpp
    client/QXmppCallStream.cpp
    )

    set(INSTALL_HEADER_FILES
    ${INSTALL_HEADER_FILES}
    # modified adding callmanager here
    client/QXmppCall.h
    client/QXmppCallManager.h
    client/QXmppCallStream.h
    )
endif()


if(BUILD_SHARED)
    add_library(${QXMPP_TARGET} SHARED ${SOURCE_FILES})
else()
    add_library(${QXMPP_TARGET} STATIC ${SOURCE_FILES})
endif()

set_target_properties(${QXMPP_TARGET} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${SO_VERSION}
    EXPORT_NAME QXmpp
)

target_include_directories(${QXMPP_TARGET}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/base>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/client>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/server>
    $<INSTALL_INTERFACE:include/${QXMPP_TARGET}>
    PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(${QXMPP_TARGET}
    PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Xml
)

if(WITH_GSTREAMER)

    # set(INSTALL_HEADER_FILES
    #     ${INSTALL_HEADER_FILES}
    #     client/QXmppCall.h
    #     client/QXmppCallManager.h
    #     client/QXmppCallStream.h
    # )

    # target_sources(${QXMPP_TARGET}
    #     PUBLIC
    #     client/QXmppCall.cpp
    #     client/QXmppCallManager.cpp
    #     client/QXmppCallStream.cpp
    # )

    if (IOS)
        target_link_libraries(${QXMPP_TARGET} PRIVATE
            /Users/romas/Library/Developer/GStreamer/iPhone.sdk/GStreamer.framework
            "-framework GStreamer"
            iconv
        )
        include_directories("/Users/romas/Library/Developer/GStreamer/iPhone.sdk/GStreamer.framework/Versions/1.0/Headers")
    elseif (APPLE)
        target_link_libraries(${QXMPP_TARGET} PRIVATE
            /Library/Frameworks/GStreamer.framework
            "-framework GStreamer"
            iconv
        )
        include_directories("/Library/Frameworks/GStreamer.framework/Versions/1.0/Headers")
    else ()
        find_package(GStreamer REQUIRED)
        find_package(GLIB2 REQUIRED)
        find_package(GObject REQUIRED)


        target_link_libraries(${QXMPP_TARGET}
            PRIVATE
            ${GLIB2_LIBRARIES}
            ${GOBJECT_LIBRARIES}
            ${GSTREAMER_LIBRARY}
        )

        target_include_directories(${QXMPP_TARGET}
            PRIVATE
            ${GLIB2_INCLUDE_DIR}
            ${GOBJECT_INCLUDE_DIR}
            ${GSTREAMER_INCLUDE_DIRS}
        )
    endif()


endif()

if(BUILD_OMEMO)
    # required to be used in QXmppMessage
    target_sources(${QXMPP_TARGET} PRIVATE base/QXmppOmemoDataBase.cpp)
endif()

if(WITH_QCA)
    target_sources(${QXMPP_TARGET} PRIVATE client/QXmppEncryptedFileSharingProvider.cpp client/QXmppFileEncryption.cpp client/QcaInitializer.cpp)
    set(INSTALL_HEADER_FILES ${INSTALL_HEADER_FILES} client/QXmppEncryptedFileSharingProvider.h)

    if (IOS)
        target_link_libraries(${QXMPP_TARGET} PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/../../prebuilt-dependencies/ios/libqca-qt6.a"
        )
        #TODO normal includes
        include_directories("/usr/local/include/omemo")
        include_directories("/Library/Frameworks/qca-qt6.framework/Version/2.0/Headers")
    elseif (APPLE)
        target_link_libraries(${QXMPP_TARGET} PRIVATE
            "-framework qca-qt6"
        )
        include_directories("/usr/local/include/omemo")
        include_directories("/Library/Frameworks/qca-qt6.framework/Version/2.0/Headers")
    else ()
        target_link_libraries(${QXMPP_TARGET} PRIVATE qca-qt6)# qca-cyrus-sasl qca-gnupg qca-logger qca-ossl qca-softstore)
    endif()

    # target_include_directories(${QXMPP_TARGET} PRIVATE
    #     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    #     $<INSTALL_INTERFACE:include>
    # )
endif()

# qxmpp_export.h generation
if(BUILD_SHARED)
    set(QXMPP_BUILD_SHARED true)
else()
    set(QXMPP_BUILD_SHARED false)
endif()

set(QXMPP_CUSTOM_EXPORT_CONTENT "
#define QXMPP_BUILD_SHARED ${QXMPP_BUILD_SHARED}
#define QXMPP_VERSION_MAJOR ${PROJECT_VERSION_MAJOR}
#define QXMPP_VERSION_MINOR ${PROJECT_VERSION_MINOR}
#define QXMPP_VERSION_PATCH ${PROJECT_VERSION_PATCH}
")

generate_export_header(${QXMPP_TARGET}
    BASE_NAME qxmpp
    CUSTOM_CONTENT_FROM_VARIABLE QXMPP_CUSTOM_EXPORT_CONTENT
)

install(
    TARGETS ${QXMPP_TARGET}
    EXPORT QXmppTarget
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    EXPORT QXmppTarget
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${QXMPP_TARGET}"
    FILE QXmpp.cmake
    NAMESPACE QXmpp::
    COMPONENT Devel
)

# export(
#     TARGETS ${QXMPP_TARGET}
#     FILE QXmpp.cmake
# )

install(
    FILES ${INSTALL_HEADER_FILES} ${CMAKE_CURRENT_BINARY_DIR}/qxmpp_export.h
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${QXMPP_TARGET}"
)

# submodules
if(BUILD_OMEMO)
    add_subdirectory(omemo)
endif()
