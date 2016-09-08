#include <QDebug>
#include <QObject>
#include <QMetaProperty>
#include <QMetaObject>
#include "classes.h"


int main(int argc, char *argv[])
{
    Q_UNUSED(argc)
    Q_UNUSED(argv)

    auto myObject = QSharedPointer<MyObject>(new MyObject());

    auto value1 = QSharedPointer<MyDerivedClass>(new MyDerivedClass());
    auto value2 = QSharedPointer<MyDerivedClass>(new MyDerivedClass());
    auto value3 = new MyDerivedClass();
    auto value4 = new MyDerivedClass();

    QVariant varQSPDerived;
    QVariant varQSPBase;

    QVariant varPtrDerived;
    QVariant varPtrBase;

    varQSPDerived.setValue<QSharedPointer<MyDerivedClass>>(value1);
    varQSPBase.setValue<QSharedPointer<MyBaseClass>>(value2);

    varPtrDerived.setValue<MyDerivedClass*>(value3);
    varPtrBase.setValue<MyBaseClass*>(value4);

    qDebug()<<"With QSharedPointer:";
    qDebug()<<"Derived: "<<myObject->metaObject()->property(1).write(myObject.data(),varQSPDerived);
    qDebug()<<"Base Cl: "<<myObject->metaObject()->property(1).write(myObject.data(),varQSPBase);
    qDebug()<<"With normal pointer:";
    qDebug()<<"Derived: "<<myObject->metaObject()->property(2).write(myObject.data(),varPtrDerived);
    qDebug()<<"Base Cl: "<<myObject->metaObject()->property(2).write(myObject.data(),varPtrBase);
    qDebug()<<"Writing QSP to normal (wrong thing to do!):";
    qDebug()<<"Derived: "<<myObject->metaObject()->property(2).write(myObject.data(),varQSPDerived);
    qDebug()<<"Base Cl: "<<myObject->metaObject()->property(2).write(myObject.data(),varQSPBase);
//    qDebug()<<"Writing normal to QSP (still wrong thing to do!):";
//    qDebug()<<"Derived: "<<myObject->metaObject()->property(1).write(myObject.data(),varPtrDerived);
//    qDebug()<<"Base Cl: "<<myObject->metaObject()->property(1).write(myObject.data(),varPtrBase);

}
