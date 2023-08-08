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
    // declaration on stack
    explicit Model(): tag {"default"} { qDebug() << "Created " << this->tag; };

    // Why can't use QString& and forced to use QString&&?
    explicit Model(QString tag): tag {tag} { qDebug() << "Created " << this->tag; };

    // Trivial copy-constructor
    // TODO: some kind of && and swap will be better probably?
    Model(const Model& other): tag(other.tag + " copy") {
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
        createModelOnHeap();
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

    void createModelOnHeap() {
        qDebug() << "============================";
        //! error: no viable conversion from 'Model *' to 'Model'
        // You can't create variable on stack using value semantics
        // Model mh = new Model("model1 on heap");

        // declaring a pointer to value by creating model1 on heap
        Model *pmh1 = new Model("model1 on heap");
        delete pmh1;

        // declaring a pointer to value by creating model2 on heap
        Model *pmh2 = new Model("model2 on heap");

        //! error: non-const lvalue reference to type 'Model' cannot bind to a value of unrelated type 'Model *'
        // you can't assign pointer to reference directly
        // as they are not replaceable during initilization
        // Reference should be initilized with value, not with
        // pointer to value
        // Model &rpmh2 = pmh2;

        // But you can declare a reference to a value
        // on heap by dereferencing a ptr to that value
        Model &rpmh2 = *(pmh2); Q_UNUSED(rpmh2)

        // Now you have a pointer to value and reference to value
        // And you can free memory using
        //          delete pmh2;
        // or
        delete &rpmh2;
        // because new and delete only working with addresses

        // Since reference should always be initialized, comparing
        // to pointers which might point to nothing (nullptr)
        // such approach is highly not recommended.
        // So references in general should be used to access and
        // interact with objects outside of object creation or
        // object ownership.

        // declaring a reference by dereferecing
        // a pointer to model on heap, not recommended
        Model& mh3 = *(new Model("model3 on heap"));
        delete &mh3;
        // 1. Object is created on heap
        // 2. Model& mh3 - is a declaration of reference
        // 3. Allocated objected assigned to reference
        // 4. delete &mh3 will free memory on stack
        // 5. Such approach is not recommended

        // declaring a variable by dereferecing
        // a pointer to model on heap, not recommended
        Model mh4 = *(new Model("model4 on heap"));
        // 1. Object is created on heap
        // 2. Model mh4 - is a declaration of variable on stack
        // 3. On assignment copy constructor will be called
        // 4. delete &mh4 will crash the app, because this is an address on stack
        // 5. Memory originally allocated on heap will leak.
    };
signals:

};
#endif // CPPREFSANDPTRSTESTVM_H
