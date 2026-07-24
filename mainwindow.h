#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "SimpleTCPChatClient/simpletcpchatclient.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_sendButton_pressed();
    void AddText(const QString &text);
private:
    Ui::MainWindow *ui;
    SimpleTCPChatClient *client;
    QThread *thread;
};
#endif // MAINWINDOW_H