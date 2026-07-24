#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "SimpleTCPChatClient/simpletcpchatclient.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class SimpleTCPChat;
}
QT_END_NAMESPACE

class SimpleTCPChat : public QMainWindow
{
    Q_OBJECT

public:
    explicit SimpleTCPChat(QWidget *parent = nullptr);
    ~SimpleTCPChat() override;

private slots:
    void on_sendButton_pressed();
    void AddText(const QString &text);
    void on_pushButton_pressed();

private:
    Ui::SimpleTCPChat *ui;
    SimpleTCPChatClient *client;
    QThread *thread;
    void Connect();
};
#endif // MAINWINDOW_H