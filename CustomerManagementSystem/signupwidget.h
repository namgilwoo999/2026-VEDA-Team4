#ifndef SIGNUPWIDGET_H
#define SIGNUPWIDGET_H

#include <QWidget>
#include "userdb.h"

namespace Ui {
class SignupWidget;
}

class SignupWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SignupWidget(QWidget *parent = nullptr);
    ~SignupWidget();

signals:
    void SignupCompleted();
    void CancelRequested();

private slots:
    void OnConfirmClicked();
    void OnCancelClicked();
    void OnCheckIdClicked();

private:
    Ui::SignupWidget *ui;
    UserDB m_userDb;
    bool m_idChecked = false;
};

#endif // SIGNUPWIDGET_H
