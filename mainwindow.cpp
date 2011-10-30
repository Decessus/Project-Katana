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

#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setAnimated(true);
    ui->setupUi(this);

    QPalette pal = palette();
    pal.setBrush(QPalette::Window,QBrush(QColor(70, 70, 70)));
    this->setPalette(pal);
    this->setAutoFillBackground(true);

    currentPage = new WebFrame();

    ui->centralWidget->setLayout(ui->gridLayout);

    this->setStyle(new QPlastiqueStyle());

    settings = new SettingsDialog();
    connect(settings,SIGNAL(settingsRefresh()),this,SLOT(settingsRefresh()));

    QSize size = appSettings.value("size", QSize(750, 400)).toSize();
    QByteArray state = appSettings.value("state", QByteArray()).toByteArray();
    QStringList tabsMap = appSettings.value("tabs",QStringList()).toStringList();
    restoreState(state);

    setGeometry(
                QStyle::alignedRect(
                    Qt::LeftToRight,
                    Qt::AlignCenter,
                    size,
                    qApp->desktop()->availableGeometry()
                ));

    setAttribute(Qt::WA_TranslucentBackground);

    ui->gridLayoutWidget->setVisible(false);
    ui->titleWidget->setLayout(ui->titleLayout);

    ui->closeButton->setIcon(QIcon(":/icons/close_icon.gif"));
    ui->closeButton->setIconSize(QSize(14,14));
    ui->minimizeButton->setIcon(this->style()->standardIcon(QStyle::SP_TitleBarMinButton));
    ui->minimizeButton->setIconSize(QSize(14,14));
    ui->maximizeButton->setIcon(this->style()->standardIcon(QStyle::SP_TitleBarMaxButton));
    ui->maximizeButton->setIconSize(QSize(14,14));
    ui->closeButton->raise();
    ui->minimizeButton->raise();
    ui->maximizeButton->raise();

    ui->gridLayoutWidget_2->setVisible(false);

    ui->centralWidget->setStyleSheet(QString("background:rgb(70,70,70,70); border-radius:10px;"));

    ui->goBack->setIcon(this->style()->standardIcon(QStyle::SP_ArrowBack));
    ui->goBack->setIconSize(QSize(20,20));
    ui->goBack->setStyleSheet(QString("background-color:rgb(40,40,40);border-radius:2px; border-top-right-radius:0px; border-bottom-right-radius:0px; border:1px solid black;"));

    ui->goForward->setIcon(this->style()->standardIcon(QStyle::SP_ArrowForward));
    ui->goForward->setIconSize(QSize(20,20));
    ui->goForward->setStyleSheet(QString("background-color:rgb(40,40,40);border-radius:2px; border-top-left-radius:0px; border-bottom-left-radius:0px; border:1px solid black; border-left:none; "));

    ui->pageButton->setIcon(this->style()->standardIcon(QStyle::SP_BrowserReload));
    ui->pageButton->setIconSize(QSize(20,20));
    ui->pageButton->setStyleSheet(QString("background-color:rgb(40,40,40);border-radius:2px; border:1px solid black; border-top-left-radius:0px; border-bottom-left-radius:0px; border-left:none;"));

    ui->homeButton->setIcon(QIcon(QString(":/icons/home-icon.png")));
    ui->homeButton->setIconSize(QSize(20,20));
    ui->homeButton->setStyleSheet(QString("background-color:rgb(40,40,40);border-radius:2px; border:1px solid black; border-top-right-radius:0px; border-bottom-right-radius:0px;"));


    ui->settingsButton->setIcon(QIcon(QString(":/icons/settings-icon.png")));
    ui->settingsButton->setIconSize(QSize(20,20));
    ui->settingsButton->setStyleSheet(QString("background:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(135, 135, 135, 255), stop:1 rgba(87, 87, 87, 255));border-radius:4px; border-bottom-right-radius:0px; border-bottom-left-radius:0px; border:1px solid black; border-bottom-color:rgb(120,120,120);"));

    ui->settingsButton->setMenu(ui->menuFile);

    ui->statusBar->setStyleSheet(QString("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(104, 104, 104, 214), stop:1 rgba(35, 35, 35, 194));border-bottom: 2px solid qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 166));border-radius:0px;"));

    dragBar = new DragWidget(this);
    dragBar->setParent(ui->titleWidget);
    dragBar->lower();
    ui->label->lower();

    ui->scrollAreaWidgetContents_3->setAcceptDrops(true);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->stackedWidget->setStyleSheet(QString("background-color:rgb(255,255,255,255);border-right:2px solid rgb(0,0,0,150);border-left:2px solid rgb(0,0,0,150);border-radius:0px;"));

    if(tabsMap.size() > 0) {
        QMessageBox messageBox(this);

        QAbstractButton *loadPreviousSession =
        messageBox.addButton(tr("Yes"), QMessageBox::ActionRole);
        QPushButton *loadNewSession =
        messageBox.addButton(tr("No"), QMessageBox::ActionRole);
        messageBox.setIcon(QMessageBox::Question);
        messageBox.setDefaultButton(loadNewSession);
        messageBox.setText(QString("Would you like to reload your previous session?"));
        messageBox.setWindowTitle(QString(""));
        messageBox.exec();
        if (messageBox.clickedButton() == loadPreviousSession) {
            foreach(QString url,tabsMap) {
                addPage(url);
            }
        }
        else {
            tabsMap.clear();
        }

    }

    if(tabsMap.size() <= 0) {
        addPage();
    }

    GoogleSuggest = new GSuggestCompletion(ui->lineEdit);
    GoogleSuggest->setStyleSheet(QString("border:1px solid rgb(0,0,0,255);background-color:rgb(180,180,180,255);margin-bottom:2px;"));
    ui->menuBar->hide();

    fontDb.addApplicationFont(QString(":/Ubuntu-R.tff"));
    this->setFont(QFont(QString("ubuntu"),11));

    if(appSettings.value(QString("animations")).toBool() && appSettings.value(QString("animations_level")).toInt() > 4) {
        QPropertyAnimation *in = new QPropertyAnimation(this,QByteArray("windowOpacity"));
        in->setDuration(450);
        in->setStartValue(qreal(0.0));
        in->setEndValue(qreal(1.0));
        in->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

void MainWindow::settingsRefresh() {
    QMapIterator<QString,QVariant> iterator(settings->ApplicationSettings);

    while(iterator.hasNext()) {
        iterator.next();
        appSettings.setValue(iterator.key(),iterator.value());
    }

    appSettings.sync();
}

void MainWindow::toggleAnimations(bool enable) {
    animations = enable;
}

void MainWindow::loadFinished(bool ok,WebFrame *frame) {
    TabButton *button = pageMap.key(frame);

    if(button)
        button->setLoading(false);
}

void MainWindow::loadStarted(WebFrame *frame) {
    TabButton *button = pageMap.key(frame);

    if(button)
        button->setLoading(true);
}

void MainWindow::iconChanged(QIcon icon, WebFrame *frame) {
}

MainWindow::~MainWindow()
{
    appSettings.setValue(QString("size"), size());
    appSettings.setValue(QString("state"), saveState());

    QStringList tabsMap;

    QMapIterator<TabButton*,WebFrame*> iterator(pageMap);

    while (iterator.hasNext()) {
        iterator.next();
        tabsMap.append(iterator.value()->url().toString());
    }

    appSettings.setValue("tabs", tabsMap);

    delete ui;
}

void MainWindow::shutDown() {
}

void MainWindow::addPage(QString url) {
    WebFrame *tempFrame = new WebFrame();
    connect(tempFrame,SIGNAL(loadFinished(bool,WebFrame*)),this,SLOT(loadFinished(bool,WebFrame*)));
    connect(tempFrame,SIGNAL(titleChanged(QString,WebFrame*)),this,SLOT(updateTitle(QString,WebFrame*)));
    connect(tempFrame,SIGNAL(urlChanged(QString,WebFrame*)),this,SLOT(urlChanged(QString,WebFrame*)));
    connect(tempFrame,SIGNAL(loadStarted(WebFrame*)),this,SLOT(loadStarted(WebFrame*)));
    connect(tempFrame,SIGNAL(loadFinished(bool,WebFrame*)),this,SLOT(loadFinished(bool,WebFrame*)));

    if(url.isEmpty() || url.isNull())
        tempFrame->load(QUrl("http://google.com"));
    else
        tempFrame->load(QUrl(url));

    qDebug() << (pageMap.size() * 121) + (5 * pageMap.size());
    TabButton *tempButton = new TabButton(ui->scrollAreaWidgetContents_3);
    tempButton->setFont(QFont(QString("Ubuntu"),10));
    tempButton->setGeometry(QRect((pageMap.size()) * 121,5,120,20));

    tempButton->setVisible(true);
    tempButton->raise();
    connect(tempButton,SIGNAL(clicked(TabButton*)),this,SLOT(tabClicked(TabButton*)));
    connect(tempButton,SIGNAL(closeRequested(TabButton*)),this,SLOT(tabCloseRequested(TabButton*)));

    if(appSettings.value(QString("animations")).toBool() && appSettings.value(QString("animations_level")).toInt() >= 1) {
        QPropertyAnimation *in = new QPropertyAnimation(tempButton,"geometry");
        in->setDuration(150);
        in->setStartValue(QRect(-120,5,120,20));

        if(pageMap.size() > 1)
            in->setEndValue(QRect((pageMap.size()) * 121 + 5 * (pageMap.size()),5,120,20));
        else if(pageMap.size() == 1)
            in->setEndValue(QRect((pageMap.size()) * 121 + 10 * (pageMap.size()),5,120,20));
        else
            in->setEndValue(QRect(pageMap.size() * 121 + 5,5,120,20));

        in->start(QAbstractAnimation::DeleteWhenStopped);
    }

    pageMap.insert(tempButton,tempFrame);

    if(pageMap.size() > 1 && ui->scrollArea->height() == 0) {
        if(animations) {
            qDebug() << "yes";
            QPropertyAnimation *in2 = new QPropertyAnimation(ui->scrollArea,"size");
            in2->setDuration(100);
            in2->setStartValue(ui->scrollArea->size());
            in2->setEndValue(QSize(ui->scrollArea->width(),30));
            in2->start(QAbstractAnimation::DeleteWhenStopped);
        }
        else {
            ui->scrollArea->setFixedSize(ui->scrollArea->width(),30);
        }
    }

    ui->stackedWidget->addWidget(tempFrame);
    ui->stackedWidget->setCurrentWidget(tempFrame);

    this->tabClicked(tempButton);


}

void MainWindow::tabCloseRequested(TabButton *button) {

    //Exit application if last tab is closed
    this->tabClicked(button);
    if(pageMap.size() == 1)
        this->close();

    QMapIterator<TabButton*,WebFrame*> iterator(pageMap);

    int indexOf = 0;
    while(iterator.hasNext()) {
        if(button == iterator.next().key())
            break;
    }

    TabButton *tempButton = iterator.key();
    WebFrame *tempFrame = iterator.value();

    TabButton *nextPage;
    if(iterator.hasNext()) {
        nextPage = iterator.next().key();
        qDebug() << "Map iterator next";
    }
    else {
        if(iterator.hasPrevious()) {
            nextPage = iterator.previous().key();
            qDebug() << "Map iterator previous";
        }
        else {
            qDebug() << "No map iterator";
            return;
        }
    }

    this->tabClicked(nextPage);

    //Remove closed tab and webview
    pageMap.remove(button);
    delete tempButton;
    delete tempFrame;

    //Reorder tabs
    QMapIterator<TabButton*,WebFrame*> iterator2(pageMap);

    tempButton = new TabButton();
    indexOf = 0;

    while(iterator2.hasNext()) {
        iterator2.next();
        tempButton = iterator2.key();

        qDebug() << iterator2.key();

        tempButton->setStyleSheet(QString("margin-left:5px;"));

        if(animations) {
            QPropertyAnimation *in = new QPropertyAnimation(tempButton,"geometry");
            in->setDuration(150);
            in->setStartValue(QRect(QPoint(-120,5),QSize(120,20)));
            in->setEndValue(QRect(QPoint(indexOf * 121,5),QSize(120,20)));
            in->start(QAbstractAnimation::DeleteWhenStopped);
        }
        else {
            tempButton->setGeometry(QRect(QPoint(indexOf * 121,5),QSize(120,20)));
        }

        indexOf++;
    }

    if(pageMap.size() == 1) {
        if(animations) {
            qDebug() << "yes";
            QPropertyAnimation *in2 = new QPropertyAnimation(ui->scrollArea,"size");
            in2->setDuration(100);
            in2->setStartValue(ui->scrollArea->size());
            in2->setEndValue(QSize(ui->scrollArea->width(),0));
            in2->start(QAbstractAnimation::DeleteWhenStopped);
        }
        else {
            ui->scrollArea->setFixedSize(ui->scrollArea->width(),0);
        }
    }
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    CurrentSize.setHeight(event->size().height()-25);
    CurrentSize.setWidth(event->size().width());
    //currentPage->setGeometry(QRect(0,0,CurrentSize.width(),CurrentSize.height() - 25));

    GoogleSuggest->setSuggestSize(QSize(event->size().width() - 173,100));

    path.moveTo(0,CurrentSize.height() / 2);
    path.quadTo(500,200,0,0);
    dragBar->setFixedSize(event->size());

    if((pageMap.size() * 122) < event->size().width())
        ui->scrollAreaWidgetContents_3->setFixedWidth(event->size().width());
    else
        ui->scrollAreaWidgetContents_3->setFixedWidth(pageMap.size() * 122);

    if (pageMap.size() <= 1) {

    }
    else {
        ui->scrollArea->setFixedSize(event->size().width(), 30);
    }
}


void MainWindow::updateTitle(QString title, WebFrame *frame) {
    TabButton *tempButton = pageMap.key(frame);
    tempButton->setToolTip(title);
    if(title.length() > 13) {
        tempButton->setText(title.mid(0,10).append(".."));
    }
    else
        tempButton->setText(title);

    if(frame == static_cast<WebFrame*>(ui->stackedWidget->currentWidget())) {
        this->setWindowTitle(QString("Katana (0.1a) :: %1").arg(title));
        ui->label->setText(QString("Katana (0.1a) :: %1").arg(title));
    }
}

void MainWindow::on_actionNew_Tab_triggered() {
    addPage();
}

void MainWindow::on_closeButton_clicked()
{
    this->close();
}

void MainWindow::tabClicked(TabButton *button) {
    if(pageMap.value(button) != static_cast<WebFrame*>(ui->stackedWidget->currentWidget()))
        ui->stackedWidget->setCurrentWidget(pageMap.value(button));
    QMapIterator<TabButton*,WebFrame*> iterator(pageMap);
    while(iterator.hasNext()) {
        TabButton *tempButton = iterator.next().key();
        if(tempButton->isChecked())
            tempButton->setChecked(false);
    }
    button->setChecked(true);
    ui->lineEdit->setText(static_cast<WebFrame*>(ui->stackedWidget->currentWidget())->url().toString());
    QString title = static_cast<WebFrame*>(ui->stackedWidget->currentWidget())->page()->mainFrame()->title();
    this->setWindowTitle(QString("Katana (0.1a) :: %1").arg(title));
    ui->label->setText(QString("Katana (0.1a) :: %1").arg(title));
}

/** Draging Widget **/
DragWidget::DragWidget(QMainWindow *parent) : QWidget(parent) {
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->parentWindow = parent;
}

void DragWidget::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        mMoving = true;
        mLastMousePosition = event->pos();
    }
}

void DragWidget::mouseMoveEvent(QMouseEvent* event)
{
    if( event->buttons().testFlag(Qt::LeftButton) && mMoving)
    {
        QPoint newPoint(event->globalPos().x() - mLastMousePosition.x(),
                        event->globalPos().y() - mLastMousePosition.y());
        parentWindow->move(newPoint);
        //mLastMousePosition = event->pos();
    }
}

void DragWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        mMoving = false;
    }
}

void MainWindow::on_lineEdit_returnPressed()
{

    if(urlTimer.isActive()) {
        disconnect(&urlTimer,SIGNAL(timeout()),this,SLOT(on_lineEdit_returnPressed()));
        urlTimer.stop();
    }

    GoogleSuggest->preventSuggest();
    GoogleSuggest->hideSuggestions();

    QRegExp urlExp(QString("^(http\://|)[a-zA-Z0-9\-\.]+\.(com|org|net|mil|edu)(/\S*)?$"));
    QRegExp ipExp(QString("^(http\://|)(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)"));

    if(urlExp.indexIn(ui->lineEdit->text()) >= 0 || ipExp.indexIn(ui->lineEdit->text()) >= 0) {
        QString url = ui->lineEdit->text();

        if(!url.startsWith(QString("http://"),Qt::CaseInsensitive)) {
            url.insert(0,QString("http://"));
        }

        WebFrame *tempFrame = static_cast<WebFrame*>(ui->stackedWidget->currentWidget());
        tempFrame->load(url);
    }

    else {
        QString url("http://www.google.com/search?gcx=c&sourceid=katana&client=ubuntu&channel=cs&ie=UTF-8&q=");
        QString term = ui->lineEdit->text().replace(QChar(' '),QChar('+'));
        url.append(term);
        WebFrame *tempFrame = static_cast<WebFrame*>(ui->stackedWidget->currentWidget());
        tempFrame->load(url);
    }
}

void MainWindow::urlChanged(QString url, WebFrame *frame) {
    if(frame == static_cast<WebFrame*>(ui->stackedWidget->currentWidget())) {
        ui->lineEdit->setText(url);
    }
}

void MainWindow::on_actionAnimated_Interface_triggered(bool checked)
{
    if(checked) {
        animations = true;
    }
    else {
        animations = false;
    }
}

void MainWindow::on_lineEdit_editingFinished()
{
}

void MainWindow::onEditingFinished() {
    if(urlTimer.isActive()) {
        disconnect(&urlTimer,SIGNAL(timeout()),this,SLOT(onEditingFinished()));
        urlTimer.stop();
    }

    QRegExp urlExp(QString("^(http\://|)[a-zA-Z0-9\-\.]+\.(com|org|net|mil|edu)(/\S*)?$"));
    QRegExp ipExp(QString("^(http\://|)(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)"));

    if(urlExp.indexIn(ui->lineEdit->text()) >= 0 || ipExp.indexIn(ui->lineEdit->text()) >= 0) {
        QString url = ui->lineEdit->text();

        if(!url.startsWith(QString("http://"),Qt::CaseInsensitive)) {
            url.insert(0,QString("http://"));
        }

        WebFrame *tempFrame = static_cast<WebFrame*>(ui->stackedWidget->currentWidget());
        tempFrame->load(url);

        GoogleSuggest->preventSuggest();
        GoogleSuggest->hideSuggestions();
    }
}

void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    if(urlTimer.isActive()) {
        urlTimer.stop();
        urlTimer.start(500);
    }
    else {
        connect(&urlTimer,SIGNAL(timeout()),this,SLOT(onEditingFinished()));
        urlTimer.start(500);
    }
}

void MainWindow::on_goBack_clicked()
{
    static_cast<WebFrame*>(ui->stackedWidget->currentWidget())->back();
}

void MainWindow::on_goForward_clicked()
{
    static_cast<WebFrame*>(ui->stackedWidget->currentWidget())->forward();
}

void MainWindow::on_actionSave_Page_As_triggered()
{

    QString page = static_cast<WebFrame*>(ui->stackedWidget->currentWidget())->page()->mainFrame()->toHtml();
    QString saveName = QFileDialog::getSaveFileName(this,QString("Save As.."),QDir::homePath(),QString("Html Files (*.htm,*.html)"));

    if(saveName.isEmpty() || saveName.isNull())
        return;

    if(!saveName.endsWith(QString(".htm"),Qt::CaseInsensitive) && !saveName.endsWith(QString(".html"),Qt::CaseInsensitive))
        saveName.append(QString(".htm"));

    QFile saveFile(saveName);

    if(!saveFile.open(QIODevice::ReadWrite)) {
        QMessageBox *errorInfo = new QMessageBox(QMessageBox::Critical,
                                                 QString("Error Saving File"),
                                                 QString("There was an error saving %1 \r\n Error: %2").arg(saveName,saveFile.errorString()));

        errorInfo->exec();
        return;
    }

    saveFile.write(page.toAscii());
    saveFile.close();
}

void MainWindow::on_actionPrint_Page_triggered()
{
    QPrinter printer;
    WebFrame* tempFrame = static_cast<WebFrame*>(ui->stackedWidget->currentWidget());
    tempFrame->print(&printer);
}

void MainWindow::on_actionApplication_Settings_triggered()
{
    QStringList keys = appSettings.allKeys();
    QMap<QString,QVariant> settingsMap;

    foreach(QString key,keys)
        settingsMap.insert(key,appSettings.value(key));

    settings->init(settingsMap);
    settings->show();
}

void MainWindow::on_minimizeButton_clicked()
{
    this->setWindowState(Qt::WindowMinimized);
}

void MainWindow::on_maximizeButton_clicked()
{
    if (this->windowState() == Qt::WindowMaximized) {
        ui->maximizeButton->setIcon(this->style()->standardIcon(QStyle::SP_TitleBarMaxButton));
        this->resize(appSettings.value(QString("restore_size"),QSize(700,550)).toSize());
        this->setWindowState(Qt::WindowNoState);
    }

    else {
        ui->maximizeButton->setIcon(this->style()->standardIcon(QStyle::SP_TitleBarNormalButton));
        appSettings.setValue(QString("restore_size"),this->size());
        this->setWindowState(Qt::WindowMaximized);
    }
}
