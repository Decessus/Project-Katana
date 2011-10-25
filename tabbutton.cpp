/****************************************************************************
**
** Copyright (C) 2011 Arturion, Inc. and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Arturion, Inc. (info@arturion.com)
** Project Lead: James Dudeck (james@arturion.com)
**
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

#include "tabbutton.h"

TabButton::TabButton(QWidget *parent) :
    QToolButton(parent)
{
    connect(this,SIGNAL(clicked()),this,SLOT(onTabClicked()));
    this->setFixedSize(120,22);
    this->setText(QString("New Tab"));
    this->setCheckable(true);
    this->setChecked(true);
    QToolButton *closeButton = new QToolButton(this);
    closeButton->setIcon(QIcon(":/icons/close_icon.gif"));
    closeButton->setIconSize(QSize(14,14));
    closeButton->setGeometry(QRect(this->width() - 23,2,14,14));
    closeButton->setStyleSheet(QString("QToolButton:checked, QToolButton:hover {border:none;background:qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.505, fy:0.5, stop:0 rgba(255, 255, 255, 135), stop:1 rgba(255, 255, 255, 0));}"));
    connect(closeButton,SIGNAL(clicked()),this,SLOT(onTabClose()));

    this->setMouseTracking(true);
    //this->setAttribute(Qt::MoveAction);
}

void TabButton::onTabClose() {
    emit closeRequested(this);
}

void TabButton::onTabClicked() {
    emit clicked(this);
}

void TabButton::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        mMoving = true;
        mLastMousePosition = event->pos();
    }
}

void TabButton::mouseMoveEvent(QMouseEvent* event)
{
    if( event->buttons().testFlag(Qt::LeftButton) && mMoving)
    {
        this->raise();
        this->move(QPoint(event->pos().x() - mLastMousePosition.x(),5));

    }
}

void TabButton::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        mMoving = false;
        emit clicked(this);
    }
}

void TabButton::moveTo(QPoint point) {
    this->move(point);
}

void TabButton::setLoading(bool enabled) {
//    if(enabled) {

//        if(!loadingIcon) {
//            loadingIcon = new QLabel();
//            loadingIcon->setAttribute(Qt::WA_TranslucentBackground);
//            loadingIcon->setPixmap(QPixmap(QString(":/icons/loading.gif")));
//            loadingIcon->setFixedSize(QSize(16,16));
//            loadingIcon->move(QPoint(10,5));
//            loadingIcon->setScaledContents(true);
//        }

//        loadingIcon->setVisible(true);
//    }

//    else {
//        loadingIcon->setVisible(false);
//    }
}
