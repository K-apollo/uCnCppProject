#ifndef INITFORM_H
#define INITFORM_H

#include <QWidget>

namespace Ui {
class InitForm;
}

class InitForm : public QWidget
{
    Q_OBJECT

public:
    explicit InitForm(QWidget *parent = nullptr);
    ~InitForm();

private:
    Ui::InitForm *ui;
};

#endif // INITFORM_H
