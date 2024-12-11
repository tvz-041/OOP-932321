#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_clear, &QPushButton::clicked, ui->mapWidget, &MapWidget::clear);
}

MainWindow::~MainWindow()
{
    delete ui;
}

