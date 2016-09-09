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

    auto value1QSP = QSharedPointer<MyDerivedClass>(new MyDerivedClass(100));
    auto value2QSP = QSharedPointer<MyDerivedClass>(new MyDerivedClass(200));
    auto value3PTR = new MyDerivedClass(300);
    auto value4PTR = new MyDerivedClass(400);

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
    qDebug()<<myObject->myQSPProp()->value();
    qDebug()<<"Base Cl: "<<myObject->metaObject()->property(1).write(myObject.data(),varQSPBase)<<" <-- SHOULD return true and just work!";
    qDebug()<<myObject->myQSPProp()->value();
    qDebug()<<" --> QSP inheritance works in 5.5.1, fails in >=5.6";
    qDebug()<<"";
    qDebug()<<"Writing normal pointer:";
    qDebug()<<"Derived: "<<myObject->metaObject()->property(2).write(myObject.data(),varPtrDerived);
    qDebug()<<myObject->myPtrProp()->value();
    qDebug()<<"Base Cl: "<<myObject->metaObject()->property(2).write(myObject.data(),varPtrBase);
    qDebug()<<myObject->myPtrProp()->value();
    qDebug()<<" --> Normal pointer inheritance works in both versions ";
    qDebug()<<"";

    qDebug()<<"Writing QSP to normal (wrong usage!):";
//    myObject->
    qDebug()<<"Derived: "<<myObject->metaObject()->property(2).write(myObject.data(),varQSPDerived) << "content: ";
    qDebug()<<"Base Cl: "<<myObject->metaObject()->property(2).write(myObject.data(),varQSPBase) << "content: ";
    qDebug()<<" --> sometimes works in 5.5.1 (shouldn't), in version >=5.6 it fails (better) ";
    qDebug()<<"";

    qDebug()<<"Writing normal to QSP (also wrong)";
    qDebug()<<"!! --> This crashes in 5.5.1, returns false in 5.7! <-- !!";
    qDebug()<<"Derived: "<<myObject->metaObject()->property(1).write(myObject.data(),varPtrDerived);
    qDebug()<<"Base Cl: "<<myObject->metaObject()->property(1).write(myObject.data(),varPtrBase);
    qDebug()<<" --> Works in 5.5.1 (shouldn't), but may crash randomly, in version >=5.6 it fails (better) ";

//    qDebug()<<"";
}
