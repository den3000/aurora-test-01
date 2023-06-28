#ifndef MAINVM_H
#define MAINVM_H

#include <QObject>
#include <QString>

class CustomModel
{
public:
    explicit CustomModel(const QString name, const QString description, const int amount);

    QString name;
    QString description;
    int amount;
};

class MainVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)

public:
    explicit MainVM(QObject *parent = nullptr);
    ~MainVM();
    Q_INVOKABLE void foo() const;
    Q_INVOKABLE void openAboutPageWithModel(int idx);

signals:
    void gotoAboutPage();
    void gotoAboutPageWithInt(int value);
    void gotoAboutPageWithString(QString value);
    void gotoAboutPageWithModel(CustomModel model);

private:
    QList<CustomModel> models;
};

#endif // MAINVM_H
