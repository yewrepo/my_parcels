/*******************************************************************************
**
** Copyright (C) 2022 ru.yewrepo.myparcels
**
** This file is part of the Отслеживание посылок Почты России project.
**
** Redistribution and use in source and binary forms,
** with or without modification, are permitted provided
** that the following conditions are met:
**
** * Redistributions of source code must retain the above copyright notice,
**   this list of conditions and the following disclaimer.
** * Redistributions in binary form must reproduce the above copyright notice,
**   this list of conditions and the following disclaimer
**   in the documentation and/or other materials provided with the distribution.
** * Neither the name of the copyright holder nor the names of its contributors
**   may be used to endorse or promote products derived from this software
**   without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
** THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
** FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
** OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS;
** OR BUSINESS INTERRUPTION)
** HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE)
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
** EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
*******************************************************************************/

#include <auroraapp.h>
#include <QtQuick>
#include "vm/CheckBarcodeViewModel.h"
#include "vm/BarcodeListViewModel.h"
#include "requests/RuPochtaRequest.h"
#include "requests/RequestManager.h"
#include "display/TrackNumbersModel.h"
#include "display/TrackNumberData.h"
#include "db/LocalBase.h"
#include "errors/CustomErrorType.h"
#include "Updater.h"
#include "LoadingStateClass.h"
#include "PostServiceClass.h"

int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
    application->setOrganizationName(QStringLiteral("ru.yewrepo"));
    application->setApplicationName(QStringLiteral("myparcels"));
    application->setApplicationVersion(QStringLiteral(APP_VERSION));

    QScopedPointer<QQuickView> view(Aurora::Application::createView());

    qDebug() << "filesDir: " << Aurora::Application::filesDir(false);

    CustomErrorTypeClass::init();

    qRegisterMetaType<PostService>("PostService");
    qmlRegisterUncreatableType<PostServiceClass>("ru.yewrepo.myparcels", 1, 0, "PostService", "Enum type");

    qRegisterMetaType<LoadingStatus>("LoadingStatus");
    qmlRegisterUncreatableType<LoadingStateClass>("ru.yewrepo.myparcels", 1, 0, "LoadingStatus", "Enum type");

    LocalBase *localBase = new LocalBase(view.data());
    Updater *updater = new Updater(localBase, view.data());

    CheckBarcodeViewModel checkBarcodeViewModel{localBase, view.data()};
    view->rootContext()->setContextProperty("checkBarcodeViewModel", &checkBarcodeViewModel);

    BarcodeListViewModel barcodeListViewModel{localBase, updater, view.data()};
    view->rootContext()->setContextProperty("barcodeListViewModel", &barcodeListViewModel);

    QScopedPointer<TrackNumberData> trackNumberData(new TrackNumberData(view.data()));
    view->rootContext()->setContextProperty("trackNumberData", trackNumberData.data());

    QScopedPointer<TrackNumbersModel> trackNumbersModel(new TrackNumbersModel(view.data()));
    view->rootContext()->setContextProperty("trackNumbersModel", trackNumbersModel.data());

    view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/myParcels.qml")));
    view->show();

    qRegisterMetaType<UpdaterResult*>("UpdaterResult*");
    qRegisterMetaType<QList<TrackNumberData*>>("QList<TrackNumberData*>");
    qRegisterMetaType<QList<ParcelDetails*>>("QList<ParcelDetails*>");

    return application->exec();
}
