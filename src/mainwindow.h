#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "models/vkmodel.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

  protected:
    QWidget *m_centralWidget;
    QVBoxLayout *m_vBoxLayout;
    QPushButton *m_pushButton;
    QPushButton *m_buttonGetAudioList;
    VkModel *m_vkModel;

protected slots:
    void getAudioList();
    void getToken();
};


#endif // MAINWINDOW_H
