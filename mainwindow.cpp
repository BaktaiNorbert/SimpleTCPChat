#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QThread"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    thread = new QThread(this);
    client = new SimpleTCPChatClient(8080);
    client->moveToThread(thread);
    connect(thread, &QThread::started, client, &SimpleTCPChatClient::ReadLoop);
    connect(client, &SimpleTCPChatClient::OutputChanged, this, &MainWindow::AddText);
    thread->start();

    connect(thread, &QThread::finished, client, &QObject::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
}

MainWindow::~MainWindow()
{
    client->Stop();
    thread->quit();
    thread->wait();
    delete ui;
}

void MainWindow::AddText(const QString& text){
    if(text == ""){
        return;
    }
    qDebug() << text;
    QPlainTextEdit* response = new QPlainTextEdit(ui->chatLogParent);
    response->setPlainText(text.toUtf8());
    response->setReadOnly(true);
    response->setMaximumHeight(40);
    response->setFocusPolicy(Qt::NoFocus);
    response->setStyleSheet("background-color: #292931");
    if (ui->chatLogParent->layout() == nullptr){
        QVBoxLayout *layout = new QVBoxLayout(ui->chatLogParent);
        layout->setAlignment(Qt::AlignBottom);
        ui->chatLogParent->setLayout(layout);
    }

    ui->chatLogParent->layout()->addWidget(response);
}

void MainWindow::on_sendButton_pressed()
{
    QString text = ui->inputField->toPlainText();
    client->SendMessage(text);
    ui->inputField->clear();
    AddText(text);
}

