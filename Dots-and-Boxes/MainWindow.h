#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QLabel;

/**
 * @brief Класс главного окна. Именно он будет включать основной интерфейс.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void _newGame();
    void _onCellCaptured();
    void _onCellSideCaptured();

private:
    void _onGameOver();
    void _nextTurn();
    void _updateStatusBar();
    QString _styledPlayerName() const;

private:
    /**
     * @brief Специальный указатель, который позволяет обращаться к объектам на форме
     * (см. презентацию по QtDesigner).
     */
    Ui::MainWindow *ui;
    QLabel* m_statusBarLabel = nullptr;

    const int m_playerCount = 2;
    int m_currentPlayer;
    int m_playerTurnsLeft;
};
