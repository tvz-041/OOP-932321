#pragma once

#include <QGraphicsView>

#include "MapModel.h"

class CellSideGraphicsObject;

/**
 * @brief Виджет игровой карты.
 * QGraphicsView является "окошком", через которое мы смотрим на сцену.
 * (сцена может быть очень большой, но нам отображается только та часть,
 * которая соответствует размерам QGraphicsView).
 */
class MapWidget : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MapWidget(QWidget *parent = nullptr);
    ~MapWidget() override = default;

    void setVisible(bool visible) override;

    static QColor playerColor(int player);
    static QString playerColorString(int player);
    QColor currentPlayerColor() const;
    void setCurrentPlayer(int player);

/**
 * Слоты - это обычные методы, с одной дополнительной возможностью:
 * они могут принимать сигналы.
 */
public slots:
    void clear();
    void onCellSideClicked(CellSideGraphicsObject *side);

signals:
    // TODO: разместить вызовы данных сигналов
    void cellCaptured();
    void cellSideCaptured();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void _updateView();

    /**
     * @brief Добавляет палочку на игровое поле.
     */
    void _addBorder(int row, int col, Qt::Orientation type);

    /**
     * @brief Осуществляет закрас ячейки цветом текущего игрока.
     */
    void _paintCell(int row, int col);

private:
    /**
     * @brief Внутренний размер ячейки (без учёта границ) в пикселях.
     */
    int m_cellSize = 50;

    /**
     * @brief Толщина границы в пикселях.
     */
    int m_borderThickness = 10;

    /**
     * @brief Модель нашей игровой карты (содержит данные о принадлежности палочек/ячеек)
     */
    MapModel m_model;

    /**
     * @brief Сцена, на которой будут размещаться наши палочки.
     */
    QGraphicsScene *m_scene = nullptr;

    int m_currentPlayer = 1;
    static const int m_playerCount = 2;
};

