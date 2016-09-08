#include <QCoreApplication>
#include <QDebug>
#include <QObject>
#include <QMetaProperty>
#include <QMetaObject>
#include <QSharedPointer>
#include "classes.h"


int main(int argc, char *argv[])
{
    auto myObject = QSharedPointer<MyObject>(new MyObject());
    auto value1 = QSharedPointer<MyDerivedClass>(new MyDerivedClass());
    value1->setText("Wert1");
    auto value2 = QSharedPointer<MyDerivedClass>(new MyDerivedClass());
    value2->setText("Wert2");

    QVariant var1;
    QVariant var2;

    var1.setValue<QSharedPointer<MyDerivedClass>>(value1);
    var2.setValue<QSharedPointer<MyBaseClass>>(value2);

    qDebug()<<myObject->metaObject()->property(1).write(myObject.data(),var1);
//    qDebug()<<myObject->myProp()->text();
    qDebug()<<myObject->metaObject()->property(1).write(myObject.data(),var2);
//    qDebug()<<myObject->myProp()->text();

    QCoreApplication a(argc, argv);

    return a.exec();
}
