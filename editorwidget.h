#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QVector3D>
#include <QVector>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class EditorWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit EditorWidget(QWidget *parent = nullptr);
    ~EditorWidget();

    void loadFile(const QString &filePath);
    void createEditArea(const QPoint &position);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    QVector<QVector3D> editAreas;        // 편집 영역을 저장할 벡터

    QOpenGLShaderProgram *shaderProgram; // 셰이더 프로그램
    QOpenGLBuffer        *vertexBuffer;  // 버텍스 버퍼
};
#endif // EDITORWIDGET_H
