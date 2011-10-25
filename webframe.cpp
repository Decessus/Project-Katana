/****************************************************************************
**
** Copyright (C) 2011 Arturion, Inc. and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Arturion, Inc. (info@arturion.com)
** Project Lead: James Dudeck (james@arturion.com)
**
** $QT_BEGIN_LICENSE$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include "webframe.h"

WebFrame::WebFrame(QWidget *parent) :
    QWebView(parent)
{
    connect(this,SIGNAL(loadFinished(bool)),this,SLOT(loadFinishing(bool)));
    connect(this,SIGNAL(loadProgress(int)),this,SLOT(loadProgression(int)));
    connect(this,SIGNAL(loadStarted()),this,SLOT(loadStarting()));
    connect(this,SIGNAL(titleChanged(QString)),this,SLOT(titleUpdate(QString)));
    connect(this,SIGNAL(urlChanged(QUrl)),this,SLOT(urlChanging(QUrl)));

    manager = new QNetworkAccessManager();
    diskCache = new QNetworkDiskCache();

    QString location = QDesktopServices::storageLocation(QDesktopServices::CacheLocation);
    diskCache->setCacheDirectory(location);
    manager->setCache(diskCache);

    this->page()->setNetworkAccessManager(manager);
    this->page()->settings()->setMaximumPagesInCache(25);

    this->settings()->setAttribute(QWebSettings::PluginsEnabled,true);
}

void WebFrame::loadFinishing(bool ok) {
    emit loadFinished(ok,this);
}

void WebFrame::loadStarting() {
    emit loadStarted(this);
}

void WebFrame::loadProgression(int progress) {
    emit loadProgress(progress,this);
}

void WebFrame::titleUpdate(const QString &title) {
    emit titleChanged(title,this);
}

void WebFrame::urlChanging(const QUrl & url) {
    emit urlChanged(url.toString(),this);
}
