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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QStackedWidget>
#include <QWidget>
#include <QLayout>
#include <QPropertyAnimation>
#include <QAnimationGroup>

#include <QToolButton>
#include <QWebPage>
#include <QWebPluginFactory>
#include <QMap>
#include <QMapIterator>

#include <QNetworkDiskCache>

#include <QPlastiqueStyle>

#include <QSizePolicy>
#include <QPainterPath>

#include <QDesktopWidget>
#include <QGradient>
#include <QGradientStop>

#include <QEvent>

#include <QAction>
#include <QActionGroup>

#include <QMenuItem>

#include <QRegExp>
#include <QTimer>

#include <QMessageBox>
#include <QFontDatabase>
#include <QtWebKit/QWebPage>
#include <QtWebKit/QWebFrame>

#include <3rdParty/googlesuggest.h>
#include <webframe.h>
#include <tabbutton.h>
#include <settingsdialog.h>

class DragWidget : public QWidget
{
public:
    explicit DragWidget(QMainWindow *parent);

protected:
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
private:
    QMainWindow *parentWindow;
    QPoint mLastMousePosition;
    bool mMoving;
};

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNew_Tab_triggered();
    virtual void resizeEvent(QResizeEvent *event);
    virtual void updateTitle(QString title, WebFrame* frame);
    virtual void loadFinished(bool ok,WebFrame* frame);
    virtual void loadStarted(WebFrame* frame);
    virtual void iconChanged(QIcon icon,WebFrame* frame);
    virtual void tabClicked(TabButton*);
    virtual void urlChanged(QString url,WebFrame *frame);
    virtual void toggleAnimations(bool enable);
    virtual void tabCloseRequested(TabButton *button);
    virtual void onEditingFinished();
    virtual void settingsRefresh();

    virtual void shutDown();

    void on_closeButton_clicked();

    void on_lineEdit_returnPressed();
    void addPage(QString url = QString());

    void on_actionAnimated_Interface_triggered(bool checked);

    void on_lineEdit_editingFinished();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_goBack_clicked();

    void on_goForward_clicked();

    void on_actionSave_Page_As_triggered();

    void on_actionPrint_Page_triggered();

    void on_actionApplication_Settings_triggered();

private:
    Ui::MainWindow *ui;

    QLayout *webLayout;




    WebFrame* currentPage;
    WebFrame* newPage;

    QStackedWidget* webStack;

    QSize CurrentSize;

    QWidget* controlFrame;

    bool addNewPage;
    bool animations;

    QPainterPath path;

    QActionGroup *actionGroup;
    QAction *newTab;
    QAction *enableAnimations;

    QMap<TabButton*,WebFrame*> pageMap;
    DragWidget* dragBar;

    QSettings appSettings;

    QTimer urlTimer;

    GSuggestCompletion *GoogleSuggest;
    QFontDatabase fontDb;

    SettingsDialog* settings;
};

#endif // MAINWINDOW_H
