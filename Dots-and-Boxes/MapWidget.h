#pragma once

#include <QGraphicsView>

#include "CellSideGraphicsObject.h"
#include "MapModel.h"

class MapWidget : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MapWidget(QWidget *parent = nullptr);
    ~MapWidget() override = default;

    void setVisible(bool visible) override;

public slots:
    void clear();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void _updateSceneRect();
    void _addBorder(int x, int y, Qt::Orientation type);

private:
    int m_cellSize = 50;
    int m_borderThickness = 10;
    MapModel m_model;
    QGraphicsScene *m_scene = nullptr;
    QVector<CellSideGraphicsObject*> m_sides;
};

