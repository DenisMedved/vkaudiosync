#include "mainwindow.h"
#include "ui_mainwindow.h"
#include  <QWidget>
#include  <QTextEdit>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_pushButton(new QPushButton),
    m_vBoxLayout(new QVBoxLayout),
    m_buttonGetAudioList( new QPushButton),
    m_centralWidget(new QWidget)
{
   m_centralWidget->setLayout(m_vBoxLayout);
   m_vBoxLayout->addWidget(m_pushButton);
   m_vBoxLayout->addWidget(m_buttonGetAudioList);
   setCentralWidget(m_centralWidget);
   m_vkModel = new VkModel();
   m_pushButton->setText("Authorize");
   m_buttonGetAudioList->setText("Get audio list");

    connect(m_pushButton, SIGNAL(clicked(bool)), this, SLOT(getToken()));
}

MainWindow::~MainWindow()
{
	delete m_pushButton;
	delete ui;
	delete m_vkModel;
}

void MainWindow::getToken(){
	m_vkModel->getAccess();
}
void MainWindow::getAudioList(){
	m_vkModel->getAudioList();
}


