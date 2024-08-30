#ifndef NEXTFORM_H
#define NEXTFORM_H

#include <QWidget>

namespace Ui {
    class NextForm;
}

class NextForm : public QWidget
{
    Q_OBJECT

public:
    explicit NextForm(QWidget *parent = nullptr);
    ~NextForm();

private:
    Ui::NextForm *ui;
};

#endif // NEXTFORM_H
