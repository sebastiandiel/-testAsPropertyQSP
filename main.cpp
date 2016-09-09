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

    auto value1QSP = QSharedPointer<MyDerivedClass>(new MyDerivedClass());
    auto value2QSP = QSharedPointer<MyDerivedClass>(new MyDerivedClass());
    auto value3PTR = new MyDerivedClass();
    auto value4PTR = new MyDerivedClass();

    QVariant varQSPDerived;
    QVariant varQSPBase;

    QVariant varPtrDerived;
    QVariant varPtrBase;

    varQSPDerived.setValue<QSharedPointer<MyDerivedClass>>(value1QSP);
    varQSPBase.setValue<QSharedPointer<MyBaseClass>>(value2QSP);

    varPtrDerived.setValue<MyDerivedClass*>(value3PTR);
    varPtrBase.setValue<MyBaseClass*>(value4PTR);

    qDebug()<<"Writing QSharedPointer:";
    qDebug()<<"Derived: "<<myObject->metaObject()->property(1).write(myObject.data(),varQSPDerived);
    qDebug()<<"Base Cl: "<<myObject->metaObject()->property(1).write(myObject.data(),varQSPBase)<<" <-- SHOULD return true and just work!";

    qDebug()<<"Writing normal pointer:";
    qDebug()<<"Derived: "<<myObject->metaObject()->property(2).write(myObject.data(),varPtrDerived);
    qDebug()<<"Base Cl: "<<myObject->metaObject()->property(2).write(myObject.data(),varPtrBase);

    qDebug()<<"Writing QSP to normal (wrong usage!):";
    qDebug()<<"Derived: "<<myObject->metaObject()->property(2).write(myObject.data(),varQSPDerived);
    qDebug()<<"Base Cl: "<<myObject->metaObject()->property(2).write(myObject.data(),varQSPBase);

    qDebug()<<"Writing normal to QSP (also wrong)";
    qDebug()<<"!! --> This crashes in 5.5.1, returns false in 5.7! <-- !!";
    qDebug()<<"Derived: "<<myObject->metaObject()->property(1).write(myObject.data(),varPtrDerived);
    qDebug()<<"Base Cl: "<<myObject->metaObject()->property(1).write(myObject.data(),varPtrBase);
}
