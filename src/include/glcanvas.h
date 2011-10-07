#ifndef GLCANVAS_H
#define GLCANVAS_H

#include <QGLWidget>
#include <QMouseEvent>
#include "Shape.hpp"
#include <QLinkedList>

enum QDRAW_TOOL{
    QDRAW_TOOL_CREATE,
    QDRAW_TOOL_TRANSLATE,
    QDRAW_TOOL_RESIZE
};

class GLCanvas : public QGLWidget
{

    Q_OBJECT
public:
    explicit GLCanvas(QWidget *parent = 0);
    virtual ~GLCanvas()
    {
        QLinkedList<Shape*>::iterator it = m_shapes.begin();
        while( it !=  m_shapes.end() )
        {
            delete *it;
            it++;
        }
    }

signals:

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *e);

    void mouseReleaseEvent(QMouseEvent *event );
    void mouseMoveEvent(QMouseEvent * event );

public slots:

private:
    struct point
    {
        double x;
        double y;
    };

    QList<point> vertexList;
    QLinkedList<Shape*> m_shapes;
    Shape* m_current;
    QVector2D m_mousePos;
    QDRAW_TOOL m_currentTool;
};



#endif // GLCANVAS_H
