#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStringList>

#include <QFile>
#include <QTextStream>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init_send_string_buttons();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_send_string_buttons()
{
    connect(ui->pushButton_recordStart, QPushButton::clicked, this, MainWindow::slot_secureCRT_send_string);
    connect(ui->pushButton_normal, QPushButton::clicked, this, MainWindow::slot_secureCRT_send_string);

    _sendBtnMap[ui->pushButton_normal] = "t app key uart 5";
    _sendBtnMap[ui->pushButton_recordStart] = "t app key uart 7";

}
void MainWindow::slot_secureCRT_send_string()
{
    qDebug() << "reboot";
    QString strAll;
    QStringList strList;
    QPushButton* p_btn =  (QPushButton*)sender();
    QString sendStr = _sendBtnMap[p_btn];

    /* open file */
    QFile readFile(SCRIPT_FILE_PATH);

    if (!readFile.open(QFile::ReadOnly)) { //| QFile::Truncate
        qDebug() << "open file error";
        return ;
    } else {
        qDebug() << "open file success";
    }

    strAll = readFile.readAll();

    readFile.close();

    /** write */
    QFile writeFile(SCRIPT_FILE_PATH);
    if (!writeFile.open(QFile::WriteOnly | QFile::Truncate)) {
        qDebug() << "open file error";
        return ;
    }

    QTextStream fileStream(&writeFile);
    strList = strAll.split("\n");
    for (int i=0; i<strList.count(); i++) {
        if (strList.at(i).contains(SECURECRT_SCREEN_SEND)) {
            QString tmpString = SECURECRT_SCREEN_SEND;
            tmpString += "\"";
            tmpString += sendStr; // send string command
            tmpString += "\"";
            tmpString += "&chr(13)";
            fileStream << tmpString << "\n";
            qDebug() << tmpString;
        } else {
            if (i == strList.count()-1) {
                fileStream << strList.at(i);
            } else {
                fileStream << strList.at(i) << "\n";
            }
        }

    }

    writeFile.close();
}
