#include "editorwidget.h"
#include <QOpenGLShaderProgram>
#include <QDebug>

EditorWidget::EditorWidget(QWidget *parent)
    : QOpenGLWidget(parent),
    shaderProgram(nullptr),
    vertexBuffer(nullptr)
{
    qDebug() << "EditorWidget created.";                // 초기화 작업
    shaderProgram = new QOpenGLShaderProgram(this);     // 셰이더 프로그램 초기화

    // 버텍스 버퍼 초기화
    vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vertexBuffer->create();
}

EditorWidget::~EditorWidget()
{
    // 자원 해제 작업
    if (vertexBuffer) {
        vertexBuffer->destroy();
        delete vertexBuffer;
        vertexBuffer = nullptr;
    }

    if (shaderProgram) {
        shaderProgram->release();
        delete shaderProgram;
        shaderProgram = nullptr;
    }

    qDebug() << "EditorWidget destroyed.";
}

void EditorWidget::initializeGL()
{
    initializeOpenGLFunctions();  // OpenGL 함수 초기화
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 배경색을 검정색으로 설정

    // 셰이더 프로그램 로드 및 링크
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/simple.vert");
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag");
    shaderProgram->link();
    shaderProgram->bind();

    // 간단한 사각형의 정점 데이터 초기화
    static const float vertices[] = {
        -10.0f, -10.0f,
        10.0f, -10.0f,
        10.0f,  10.0f,
        -10.0f,  10.0f
    };

    vertexBuffer->bind();
    vertexBuffer->allocate(vertices, sizeof(vertices));
}

void EditorWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void EditorWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderProgram->bind();
    vertexBuffer->bind();

    // 생성된 편집 영역 렌더링
    foreach (QVector3D area, editAreas)
    {
        glPushMatrix();
        glTranslatef(area.x(), area.y(), area.z());

        // 사각형 그리기
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, nullptr);
        glDrawArrays(GL_QUADS, 0, 4);
        glDisableClientState(GL_VERTEX_ARRAY);

        glPopMatrix();
    }

    vertexBuffer->release();
    shaderProgram->release();
}

void EditorWidget::loadFile(const QString &filePath)
{
    qDebug() << "Loading file:" << filePath;
    // 파일을 로드하고 필요한 처리 (현재 예제에서는 로드 로직은 포함되지 않음)
}

void EditorWidget::createEditArea(const QPoint &position)
{
    QVector3D editArea(position.x(), position.y(), 0); // Z 값은 0으로 설정하여 2D처럼 다룸
    editAreas.append(editArea);
    update(); // 다시 그리기
}
