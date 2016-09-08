#ifndef CLASSES_H
#define CLASSES_H

#include <QObject>

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
    MyDerivedClass() : MyBaseClass() { }
    virtual ~MyDerivedClass() {}
    QString text() { return m_text; }
    void setText(const QString &text) { m_text = text; }
private:
    QString m_text;

};

class MyObject: public QObject
{
    Q_OBJECT
    Q_PROPERTY(MyDerivedClass* myProp READ myProp WRITE setMyProp)
public:
    MyObject() : QObject() { }
    virtual ~MyObject() {}
    MyDerivedClass* myProp() { return m_myProp; }
    void setMyProp(MyDerivedClass* myProp) { m_myProp = myProp; }

private:
    MyDerivedClass* m_myProp;
};


#endif // CLASSES_H


