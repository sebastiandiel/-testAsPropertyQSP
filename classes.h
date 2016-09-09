#ifndef CLASSES_H
#define CLASSES_H

#include <QObject>
#include <QSharedPointer>

class MyBaseClass: public QObject
{
    Q_OBJECT
public:
    MyBaseClass() : QObject() { }
    virtual ~MyBaseClass() {}
};
class MyDerivedClass: public MyBaseClass
{
    Q_OBJECT
public:
    MyDerivedClass(int value) : MyBaseClass() { m_value = value; }
    virtual ~MyDerivedClass() {}
    int value() { return m_value;}
private:
    int m_value;
};

class MyObject: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QSharedPointer<MyDerivedClass> myQSPProp READ myQSPProp WRITE setMyQSPProp)
    Q_PROPERTY(MyDerivedClass* myPtrProp READ myPtrProp WRITE setMyPtrProp)
public:
    MyObject() : QObject() { }
    virtual ~MyObject() {}

    QSharedPointer<MyDerivedClass> myQSPProp() { return m_myQSPProp; }
    void setMyQSPProp(QSharedPointer<MyDerivedClass> myQSPProp) { m_myQSPProp = myQSPProp; }
    MyDerivedClass* myPtrProp() { return m_myPtrProp; }
    void setMyPtrProp(MyDerivedClass* myPtrProp) { m_myPtrProp = myPtrProp; }

private:
    QSharedPointer<MyDerivedClass> m_myQSPProp;
    MyDerivedClass* m_myPtrProp;
};

#endif // CLASSES_H


