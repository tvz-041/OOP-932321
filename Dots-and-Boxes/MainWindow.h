#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief Класс главного окна. Именно он будет включать основной интерфейс.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    /**
     * @brief Специальный указатель, который позволяет обращаться к объектам на форме
     * (см. презентацию по QtDesigner).
     */
    Ui::MainWindow *ui;
};
