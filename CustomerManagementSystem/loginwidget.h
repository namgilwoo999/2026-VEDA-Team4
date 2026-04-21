#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

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
    void SignUpRequested();

private slots:
    void OnLoginClicked();
    void OnCancelClicked();
    void OnSignUpClicked();

private:
    Ui::LoginWidget *ui;
};

#endif // LOGINWIDGET_H
