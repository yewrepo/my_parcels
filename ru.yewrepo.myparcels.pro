TARGET = ru.yewrepo.myparcels

DEFINES += APP_VERSION='\\"$$VERSION\\"'

QT += sql svg concurrent

CONFIG += \
    auroraapp

PKGCONFIG += \

SOURCES += \
    src/UpdaterResult.cpp \
    src/object/global/GlobalCainiaoItem.cpp \
    src/object/global/GlobalTrackingItem.cpp \
    src/requests/GlobalCainiaoRequest.cpp \
    src/requests/RequestManager.cpp \
    src/vm/CheckBarcodeViewModel.cpp \
    src/vm/BarcodeListViewModel.cpp \
    src/requests/RuPochtaRequest.cpp \
    src/requests/CainiaoRequest.cpp \
    src/object/pochta/PochtaTrackingItem.cpp \
    src/object/pochta/PochtaItem.cpp \
    src/object/cainiao/CainiaoTrackingItem.cpp \
    src/object/cainiao/CainiaoItem.cpp \
    src/object/PostData.cpp \
    src/main.cpp \
    src/display/TrackNumbersModel.cpp \
    src/display/TrackNumberData.cpp \
    src/display/ParcelHistoryItem.cpp \
    src/display/ParcelDetails.cpp \
    src/display/ItemConverter.cpp \
    src/db/LocalBase.cpp \
    src/errors/CustomError.cpp \
    src/UpdaterWorker.cpp \
    src/Updater.cpp

HEADERS += \
    src/UpdaterResult.h \
    src/errors/CustomErrorType.h \
    src/object/global/GlobalCainiaoItem.h \
    src/object/global/GlobalTrackingItem.h \
    src/requests/GlobalCainiaoRequest.h \
    src/requests/RequestManager.h \
    src/vm/PostServiceListItem.h \
    src/vm/CheckBarcodeViewModel.h \
    src/vm/BarcodeListViewModel.h \
    src/requests/RuPochtaRequest.h \
    src/requests/CainiaoRequest.h \
    src/object/pochta/PochtaTrackingItem.h \
    src/object/pochta/PochtaItem.h \
    src/object/cainiao/CainiaoTrackingItem.h \
    src/object/cainiao/CainiaoItem.h \
    src/object/PostData.h \
    src/display/TrackNumbersModel.h \
    src/display/TrackNumberData.h \
    src/display/ParcelHistoryItem.h \
    src/display/ParcelDetails.h \
    src/display/ItemConverter.h \
    src/db/LocalBase.h \
    src/errors/CustomError.h \
    src/UpdaterWorker.h \
    src/Updater.h \
    src/PostServiceClass.h \
    src/LoadingStateClass.h

DISTFILES += \
    qml/pages/ChangeParcelName.qml \
    qml/pages/TrackNumberCheck.qml \
    qml/views/PochtaRuDetailsView.qml \
    qml/views/TrackingHistoryView.qml \
    rpm/ru.yewrepo.myparcels.spec \
    README.md \

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

TRANSLATIONS += \
    translations/ru.yewrepo.myparcels.ts \
    translations/ru.yewrepo.myparcels-ru.ts \
