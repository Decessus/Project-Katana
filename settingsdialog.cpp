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

#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    setGeometry(
                QStyle::alignedRect(
                    Qt::LeftToRight,
                    Qt::AlignCenter,
                    QSize(450,500),
                    qApp->desktop()->availableGeometry()
                ));
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

int SettingsDialog::init(QMap<QString, QVariant> settings) {
    ApplicationSettings = settings;

    //Grab current settings so they can be reverted to
    OriginalSettings.insert(QString("animations"),ApplicationSettings.value(QString("animations"),true));
    ui->enableAnimations->setChecked(ApplicationSettings.value(QString("animations"),true).toBool());

    OriginalSettings.insert(QString("animations_level"),ApplicationSettings.value(QString("animations_level"),qint8(6)));
    ui->animationsLevel->setValue(ApplicationSettings.value(QString("animations_level"),qint8(6)).toInt());

    OriginalSettings.insert(QString("use_network_proxy"),ApplicationSettings.value(QString("use_network_proxy"),false));
    ui->useProxy->setChecked(ApplicationSettings.value(QString("use_network_proxy"),false).toBool());

    OriginalSettings.insert(QString("network_proxy_user"),ApplicationSettings.value(QString("network_proxy_user"),QString()));
    ui->proxyUser->setText(ApplicationSettings.value(QString("network_proxy_user"),QString()).toString());

    OriginalSettings.insert(QString("network_proxy_address"),ApplicationSettings.value(QString("network_proxy_address"),QString()));
    ui->proxyAddress->setText(ApplicationSettings.value(QString("network_proxy_address"),QString()).toString());

    OriginalSettings.insert(QString("network_proxy_password"),ApplicationSettings.value(QString("network_proxy_password"),QString()));
    ui->proxyPass->setText(ApplicationSettings.value(QString("network_proxy_password"),QString()).toString());

    OriginalSettings.insert(QString("automatic_updates"),ApplicationSettings.value(QString("automatic_updates"),true));
    ui->enableAutoUpdates->setChecked(ApplicationSettings.value(QString("automatic_updates"),true).toBool());

    OriginalSettings.insert(QString("automatic_update_action"),ApplicationSettings.value(QString("auto_update_action"),qint8(3)).toInt());
    ui->autoUpdateAction->setCurrentIndex(ApplicationSettings.value(QString("auto_update_action"),qint8(3)).toInt());
}

void SettingsDialog::on_useProxy_toggled(bool checked)
{
    ui->proxyBox->setEnabled(checked);
}

void SettingsDialog::on_enableAnimations_clicked(bool checked)
{
    on_enableAnimations_toggled(checked);
}

void SettingsDialog::on_animationsLevel_valueChanged(int value)
{
    ApplicationSettings.insert(QString("animations_level"),qint8(value));
}

void SettingsDialog::on_enableAutoUpdates_toggled(bool checked)
{
    if(checked) {
        ui->autoUpdateAction->setEnabled(true);
        ApplicationSettings.insert(QString("automatic_updates"),true);
        ApplicationSettings.insert(QString("automatic_update_action"),qint8(ui->autoUpdateAction->currentIndex()));
    }

    else {
        ui->autoUpdateAction->setEnabled(false);
        ApplicationSettings.insert(QString("automatic_updates"),false);
        ApplicationSettings.insert(QString("automatic_update_action"),qint8(0));
    }
}

void SettingsDialog::on_enableAnimations_toggled(bool checked)
{
    if(checked) {
        ui->animationsLevel->setEnabled(true);
        ApplicationSettings.insert(QString("animations"),true);
        ApplicationSettings.insert(QString("animations_level"),qint8(ui->animationsLevel->value()));
    }

    else {
        ui->animationsLevel->setEnabled(false);
        ApplicationSettings.insert(QString("animations"),false);
    }
}

void SettingsDialog::on_buttonBox_accepted()
{
    emit settingsRefresh();
    this->hide();
}

void SettingsDialog::on_buttonBox_rejected()
{
    QMapIterator<QString,QVariant> iterator(OriginalSettings);
    while(iterator.hasNext()) {
        iterator.next();
        ApplicationSettings.insert(iterator.key(),iterator.value());
    }

    emit settingsRefresh();
    this->hide();
}

void SettingsDialog::on_enableAnimations_stateChanged(int arg1)
{
    on_enableAnimations_toggled(arg1);
}

void SettingsDialog::on_tabWidget_currentChanged(QWidget *arg1)
{
    QSize newSize;
    if(arg1 == ui->generalSettings)
        newSize = QSize(450,500);

    if(arg1 == ui->mediaSettings)
        newSize = QSize(450,500);

    if(arg1 == ui->networkSettings)
        newSize = QSize(450,260);

    QRect startGeometry = this->frameGeometry();

    setGeometry(
                QStyle::alignedRect(
                    Qt::LeftToRight,
                    Qt::AlignCenter,
                    newSize,
                    qApp->desktop()->availableGeometry()
                ));

    if(ApplicationSettings.value(QString("animations")).toBool() && ApplicationSettings.value(QString("animatons_level")).toInt() >= 4) {
        QPropertyAnimation *in = new QPropertyAnimation(this,QByteArray("geometry"));
        in->setStartValue(startGeometry);
        in->setEndValue(this->geometry());
        in->setDuration(250);
        in->start(QAbstractAnimation::DeleteWhenStopped);
    }
}
