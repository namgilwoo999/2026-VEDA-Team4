#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include "signupwidget.h"

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

signals:
    void LoginRequested(const QString &id, const QString &password);
    void CancelRequested();

private slots:
    void OnLoginClicked();
    void OnCancelClicked();
    void OnSignupClicked();

private:
    Ui::LoginWidget *ui;
    SignupWidget *m_signup;
};

#endif // LOGINWIDGET_H
