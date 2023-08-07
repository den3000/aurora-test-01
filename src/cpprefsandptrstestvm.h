#ifndef CPPREFSANDPTRSTESTVM_H
#define CPPREFSANDPTRSTESTVM_H

#include <QObject>
#include <QDebug>

class Model {};

class Klazz {
    Model modelVal;
    Model& modelRef1;
    Model& modelRef2;
    std::optional<Model> optModel = std::nullopt;

public:
    Klazz(Model& modelRef1, Model model2) :
        modelRef1(modelRef1),
            // warning: binding reference member 'modelRef2'
            // to stack allocated parameter 'model2'
        modelRef2(model2)
    {
        Q_UNUSED(this->modelVal)
        Q_UNUSED(this->modelRef1)
        Q_UNUSED(this->modelRef2)
    };

    Model getModelVal() { return modelVal; }
    Model& getModelRef1() { return modelRef1; }
    Model& getModelRef2() { return modelRef2; }

    Model createModelOnStackRetByVal(){ return Model(); }
    Model* createModelOnHeapRetByPtr(){ return new Model(); }
    Model& createModelOnHeapRetByRef(){ return *(new Model()); }

        // error: non-const lvalue reference to type 'Model'
        // cannot bind to a temporary of type 'Model'
    // Model& createModelOnStackRetByRefRaw(){ return Model(); }

        // error: non-const lvalue reference to type 'Model'
        // cannot bind to a temporary of type 'Model *'
    // Model& createModelOnHeapRetByRefRaw(){ return new Model(); }

        // error: indirection requires pointer
        // operand ('Model' invalid)
    // Model& createModelOnStackRetByRef1(){ return *(Model()); }

        // error: taking the address of a temporary
        // object of type 'Model'
        // error: non-const lvalue reference to type
        // 'Model' cannot bind to a temporary of type 'Model *'
    //  Model& createModelOnStackRetByRef2(){ return &(Model()); }
};

class CppRefsAndPtrsTestVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)

public:
    explicit CppRefsAndPtrsTestVM(QObject *parent = nullptr)
        : QObject(parent) {
        qDebug() << "Created";

        // // declaring a variable by creating model on stack
        // Model ms1 = Model(); //Q_UNUSED(ms1)

        // // declaring ref to model on stack
        // Model& rms1 = ms1; Q_UNUSED(rms1)

        // // declaring ptr to model on stack
        // //  by taking the address of that model
        // Model * pms1 = &ms1; // Q_UNUSED(pms1)

        // // declaring a variable by dereferecing ptr
        // //  to model on stack
        // Model dms1 = *(pms1); Q_UNUSED(dms1)

        // // declaring a variable by creating model on heap
        // Model* pmh1 = new Model();

        // // declaring a variable by dereferecing a pointer
        // //  model on heap
        // Model mh1 = *(pmh1); Q_UNUSED(mh1) // pmh1.deref()
        // Model mh2 = *(new Model());
        // delete &mh2;

        // // declaring a ref by dereferecing a pointer
        // //  model on heap
        // Model& rpmh1 = *(pmh1); // pmh1.deref()


        // Q_UNUSED(rpmh1)
        // Q_UNUSED(ms1)

        // Model m1 = Model();
        // Model m2 = Model();
        // Klazz k = Klazz(m1, m2);
        // Model ms = k.createModelOnStackRetByVal();
        // Model* pmh = k.createModelOnHeapRetByPtr();
        // Model& rmh = k.createModelOnHeapRetByRef();


            // error: non-const lvalue reference to type 'Model'
            // cannot bind to a temporary of type 'Model *'
        // Model& rmh = k.createModelOnHeapRetByPtr();
    };

    ~CppRefsAndPtrsTestVM() { qDebug() << "Released"; };

signals:

};
#endif // CPPREFSANDPTRSTESTVM_H
