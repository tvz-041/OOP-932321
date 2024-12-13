#pragma once

#include <QGraphicsView>

#include "MapModel.h"

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

/**
 * Слоты - это обычные методы, с одной дополнительной возможностью:
 * они могут принимать сигналы.
 */
public slots:
    void clear();
    void onCellSideClicked();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void _updateSceneRect();
    void _addBorder(int x, int y, Qt::Orientation type);

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
};

