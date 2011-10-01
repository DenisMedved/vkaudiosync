#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include "vk/provider.h"
namespace Ui
{
    class MainWindow;
}
namespace VK
{
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
    QPushButton *m_pushButton; //auth button
    QPushButton *m_buttonGetAudioList; //get list button
    QPushButton *m_buttonExit;
    VK::Provider *m_vkProvider;

protected slots:
    void getAudioList();
    void getToken();
 public slots:
    void slotCloseApplication();

signals:
    void closeApplication();
};


#endif // MAINWINDOW_H
