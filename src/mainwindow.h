/*
  *  VKAudioSync
  *  Copyright (C) 2011 Denis Medved <thebucefal@gmail.com>
  *
  *  This program is free software: you can redistribute it and/or modify
  *  it under the terms of the GNU General Public License as published by
  *  the Free Software Foundation, either version 3 of the License, or
  *  (at your option) any later version.
  *
  *  This program is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License
  *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include "vk/provider.h"
#include "sync/synchronizer.h"

namespace Ui
{
    class MainWindow;
}
namespace VK
{
    class MainWindow;
}
    namespace Synch
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    QSettings *m_settings;
    VK::Provider *m_vkProvider;
    Synch::Synchronizer *m_synch;


private slots:

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setSettings(QSettings *settings);
    QSettings* getSettings();
    void setDir(QDir dir);

 public slots:
    void slotLoginSuccess();
    void slotLoginUnsuccess();
    void slotSelectDirectory();
    void slotAudioModelChanged(QList<VK::AudioModel>* list);
    void slotSynh();
};


#endif // MAINWINDOW_H
