#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

#define SCRIPT_FILE_PATH "E:/01_Project/01_docu/02_script/01_SecureCRT/SecureCRT_run_t_cmd.vbs"
#define SECURECRT_SCREEN_SEND "crt.Screen.Send"
typedef struct _SEND_BTN_INFO_s_{
    QPushButton* sendBtn;
    QString sendStr;
}SEND_BTN_INFO_s;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void slot_secureCRT_send_string();
private:
    void init_send_string_buttons();

private:
    Ui::MainWindow *ui;
    //QMap<int , SEND_BTN_INFO_s> _sendBtnMap;
    QMap<QPushButton* , QString> _sendBtnMap;
};

#endif // MAINWINDOW_H
