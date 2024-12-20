#include <QLabel>
#include <QMessageBox>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_statusBarLabel(new QLabel(this))
{
    ui->setupUi(this);
    ui->statusbar->addPermanentWidget(m_statusBarLabel, 1);

    /*
     * Соединяет выбранные сигнал и слот.
     * Требует 4 параметра-указателя:
     * - адрес объекта, который будет отправлять сигнал
     * - адрес метода-сигнала
     * - адрес объекта, который будет получать сигнал и содержит нужный слот
     * - адрес метода-слота
     *
     * В данном случае имеем:
     * ui->pushButton_newGame - указатель на QPushButton;
     * &QPushButton::clicked - метод-сигнал QPushButton;
     * this - указатель на MainWindow;
     * &MainWindow::_newGame - метод-слот MainWindow;
     */
    connect(ui->pushButton_newGame, &QPushButton::clicked, this, &MainWindow::_newGame);

    // TODO: установить соединения с остальными слотами

    _newGame();
}

MainWindow::~MainWindow()
{
    // Остальные дочерние виджеты будут удалены автоматически
    delete ui;
}

void MainWindow::_newGame()
{
    // TODO: обнулить LCD
    ui->mapWidget->clear();
    m_currentPlayer = m_playerCount;
    m_playerTurnsLeft = 0;
    _nextTurn();
}

void MainWindow::_onGameOver() // TODO: Добавить вызов этого метода при завершении игры
{
    QMessageBox::information(this, tr("Game over"), tr("The %1 is wins!").arg(_styledPlayerName()));
    _newGame();
}

void MainWindow::_nextTurn()
{
    m_currentPlayer = m_currentPlayer % m_playerCount + 1;
    m_playerTurnsLeft = 1;
    ui->mapWidget->setCurrentPlayer(m_currentPlayer);
    _updateStatusBar();
}

void MainWindow::_updateStatusBar()
{
    m_statusBarLabel->setText(tr("Current player: ") + _styledPlayerName());
}

QString MainWindow::_styledPlayerName() const
{
    QString colorText = ui->mapWidget->playerColorString(m_currentPlayer);
    QString colorHex = ui->mapWidget->playerColor(m_currentPlayer).name();
    QString styleStr = "<span style=\" color: %1; font-weight: bold;\">%2</span>";
    return styleStr.arg(colorHex, colorText);
}

void MainWindow::_onCellCaptured()
{
    ++m_playerTurnsLeft;
    QLCDNumber* lcdNumber = nullptr;
    switch (m_currentPlayer) {
        case 1:
            lcdNumber = ui->lcdNumber_firstPlayerScore;
            break;
        case 2:
            lcdNumber = ui->lcdNumber_secondPlayerScore;
            break;
        default:
            break;
    }

    if (lcdNumber)
    {
        // TODO: обновить LCD
    }
}

void MainWindow::_onCellSideCaptured()
{
    if (m_playerTurnsLeft <= 1)
    {
        _nextTurn();
    }
    else
    {
        --m_playerTurnsLeft;
    }
}
