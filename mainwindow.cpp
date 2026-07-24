#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QThread"

SimpleTCPChat::SimpleTCPChat(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SimpleTCPChat)
{
    ui->setupUi(this);
    client = nullptr;
}

void SimpleTCPChat::Connect(){
    thread = new QThread(this);
    QString ip = ui->IP->toPlainText();
    QStringList ipport = ip.split(":");

    QByteArray ba = ui->username->toPlainText().toUtf8();
    char* cstr = ba.data();

    QByteArray ba2 = ui->targetUser->toPlainText().toUtf8();
    char* cstr2 = ba2.data();

    client = new SimpleTCPChatClient(ipport[0].toUtf8().data(),
                                     ipport[1].toInt(),
                                     cstr,
                                     cstr2);
    client->moveToThread(thread);
    connect(thread, &QThread::started, client, &SimpleTCPChatClient::ReadLoop);
    connect(client, &SimpleTCPChatClient::OutputChanged, this, &SimpleTCPChat::AddText);
    thread->start();

    connect(thread, &QThread::finished, client, &QObject::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
}

SimpleTCPChat::~SimpleTCPChat()
{
    if(client != nullptr){
        client->Stop();
        thread->quit();
        thread->wait();
    }
    delete ui;
}

void SimpleTCPChat::AddText(const QString& text){
    if(text == ""){
        return;
    }
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

void SimpleTCPChat::on_sendButton_pressed()
{
    if(client == nullptr){
        return;
    }
    QString text = ui->inputField->toPlainText();
    client->SendMessage(text);
    ui->inputField->clear();
    AddText(text);
}


void SimpleTCPChat::on_pushButton_pressed()
{
    Connect();
}

