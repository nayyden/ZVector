#ifndef GLDEBUGBUFFERWIDGET_H
#define GLDEBUGBUFFERWIDGET_H
#include <QGLWidget>

class GLDebugBufferWidget : public QGLWidget
{
    Q_OBJECT
public:
    GLDebugBufferWidget(QWidget *parent = 0);

public slots:
    void drawBuffer(QImage buffer);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    QImage buffer;
};

#endif // GLDEBUGBUFFERWIDGET_H
