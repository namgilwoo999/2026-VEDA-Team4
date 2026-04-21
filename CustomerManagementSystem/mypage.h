#ifndef MYPAGE_H
#define MYPAGE_H

#include <QDialog>
#include "userdb.h"

namespace Ui {
class Mypage;
}

class Mypage : public QDialog
{
    Q_OBJECT

public:
    explicit Mypage(const QString &username, QWidget *parent = nullptr);
    ~Mypage();

signals:
    void AccountDeleted();
    void LogoutRequested();

private slots:
    void OnMenuItemClicked(int row);
    void OnChangePasswordClicked();
    void OnConfirmDeleteClicked();
    void OnCancelPasswordClicked();
    void OnCancelDeleteClicked();
    void OnLogoutClicked();

private:
    Ui::Mypage *ui;
    UserDB m_userDb;
    QString m_username;
};

#endif // MYPAGE_H
