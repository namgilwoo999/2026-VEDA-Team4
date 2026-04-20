#ifndef SIGNUPWIDGET_H
#define SIGNUPWIDGET_H

#include <QWidget>

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
    void SignupRequested(const QString &id, const QString &password,
                         const QString &name, const QString &birth,
                         const QString &phone, bool phoneAlarm,
                         const QString &email, bool emailAlarm);
    void CheckIdRequested(const QString &id);
    void CancelRequested();

private slots:
    void OnConfirmClicked();
    void OnCancelClicked();
    void OnCheckIdClicked();

private:
    Ui::SignupWidget *ui;
};

#endif // SIGNUPWIDGET_H
