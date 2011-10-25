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

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>

#include <QPropertyAnimation>
#include <QDesktopWidget>

namespace Ui {
    class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

    virtual int init(QMap<QString,QVariant> settings);
    QMap<QString,QVariant> ApplicationSettings;

signals:
    void settingsRefresh();

private slots:
    void on_useProxy_toggled(bool checked);

    void on_enableAnimations_clicked(bool checked);

    void on_animationsLevel_valueChanged(int value);

    void on_enableAutoUpdates_toggled(bool checked);

    void on_enableAnimations_toggled(bool checked);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_enableAnimations_stateChanged(int arg1);

    void on_tabWidget_currentChanged(QWidget *arg1);

private:
    Ui::SettingsDialog *ui;

    QMap<QString,QVariant> OriginalSettings;
};

#endif // SETTINGSDIALOG_H
