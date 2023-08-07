#ifndef CPPREFSANDPTRSTESTVM_H
#define CPPREFSANDPTRSTESTVM_H

#include <QObject>
#include <QDebug>
#include <QString>

class Model {
public:
    QString tag;
    // We need constructor without argumanets
    // to allow `Model m` statements for variable
    // declaration on stack, but not 100% sure
    explicit Model(): tag {"default"} { qDebug() << "Created " << this->tag; };

    // Why can't use QString& and forced to use QString&&?
    explicit Model(QString tag): tag {tag} { qDebug() << "Created " << this->tag; };

    // Trivial copy-constructor
    // TODO: some kind of && and swap will be better probably?
    Model(const Model& other): tag(other.tag + " copy") {
//        tag = tag ;
        qDebug() << "Copy " << this->tag;
    };

    ~Model() { qDebug() << "Released " << this->tag; };
};

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

        createModelOnStack();

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

    void createModelOnStack() {
        qDebug() << "============================";
        // declaring a variable by creating model on stack
        Model ms1 = Model("model1 on stack"); //Q_UNUSED(ms1)

        // declaring ref to model on stack
        Model& rms1 = ms1; Q_UNUSED(rms1)

        // declaring ptr to model on stack
        // by taking the address of that model
        Model * pms1 = &ms1; // Q_UNUSED(pms1)

        // declaring a ref by dereferecing ptr
        // to model on stack
        Model& rdpms1 = *(pms1); Q_UNUSED(rdpms1)

        // declaring a variable by dereferecing ptr
        // to model on stack
        // Will implicitly use copy constructor
        // and actually create new variable on stack
        Model dpms2 = *(pms1); Q_UNUSED(dpms2)

        // declaring a variable by creating model on stack
        Model ms2("model2 on stack");
        // reassgning value of this variable by direct
        // assignment from another variable on stack.
        // No copy constructor called
        ms2 = ms1;

        // reassgning value of this variable by
        // dereferencing ptr to previous variable
        // on stack. No copy constructor called
        ms2 = *(pms1);

        // declaring a variable by assignemnt from
        // another variable on stack. Copy constructor called
        Model ms3 = ms1;
    };

signals:

};
#endif // CPPREFSANDPTRSTESTVM_H
