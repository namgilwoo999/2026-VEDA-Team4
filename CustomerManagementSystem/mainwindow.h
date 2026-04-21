#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loginwidget.h"
#include "shopwidget.h"
#include "signupwidget.h"
#include "userdb.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void OnLoginRequested(const QString &id, const QString &password);
    void OnSignUpRequested();
    void OnSignupCompleted();
    void OnSignUpCancelled();

private:
    Ui::MainWindow *ui;
    LoginWidget *m_loginWidget;
    ShopWidget *m_shopWidget;
    SignupWidget *m_signupWidget;
    UserDB m_userDb;
};
#endif // MAINWINDOW_H
