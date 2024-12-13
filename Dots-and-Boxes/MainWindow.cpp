#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*
     * Соединяет выбранные сигнал и слот.
     * Требует 4 параметра-указателя:
     * - адрес объекта, который будет отправлять сигнал
     * - адрес метода-сигнала
     * - адрес объекта, который будет получать сигнал и содержит нужный слот
     * - адрес метода-слота
     *
     * В данном случае имеем:
     * ui->pushButton_clear - указатель на QPushButton;
     * &QPushButton::clicked - метод-сигнал QPushButton;
     * ui->mapWidget - указатель на MapWidget;
     * &MapWidget::clear - метод-слот MapWidget;
     */
    connect(ui->pushButton_clear, &QPushButton::clicked, ui->mapWidget, &MapWidget::clear);
}

MainWindow::~MainWindow()
{
    // Остальные дочерние виджеты будут удалены автоматически
    delete ui;
}

