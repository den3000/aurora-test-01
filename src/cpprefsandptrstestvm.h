#ifndef CPPREFSANDPTRSTESTVM_H
#define CPPREFSANDPTRSTESTVM_H

#include <QObject>
#include <QDebug>
#include <QString>

class ModelOnlyWithCopy {
public:
    QString tag;
    explicit ModelOnlyWithCopy(QString tag): tag {tag} { qDebug() << "Created " << this->tag; };
    ~ModelOnlyWithCopy() { qDebug() << "Released " << this->tag; };
};

class ModelByRef{
public:
    QString tag;
    explicit ModelByRef(QString& tag): tag {tag} { qDebug() << "Created " << this->tag; };
    ~ModelByRef() { qDebug() << "Released " << this->tag; };
};

class ModelByConstRef {
public:
    QString tag;
    explicit ModelByConstRef(QString const & tag): tag {tag} { qDebug() << "Created " << this->tag; };
    ~ModelByConstRef() { qDebug() << "Released " << this->tag; };
};

class ModelByRvalRef {
public:
    QString tag;
    // tag {std::move(tag)} used to avoid call for QString-copy
    // when instantiating tag variable for ModelByRvalRef
    explicit ModelByRvalRef(QString&& tag): tag {std::move(tag)} { qDebug() << "Created " << this->tag; };
    ~ModelByRvalRef() { qDebug() << "Released " << this->tag; };
};

class ModelByConstRvalRef {
public:
    QString tag;
    // tag {std::move(tag)} used to avoid call for QString-copy
    // when instantiating tag variable for ModelByConstRvalRef
    // but actually this is pretty dangeruous, and might fail
    // on different compilers, because T const && is a constant
    // and should not be moved
    explicit ModelByConstRvalRef(QString const && tag): tag {std::move(tag)} { qDebug() << "Created " << this->tag; };
    ~ModelByConstRvalRef() { qDebug() << "Released " << this->tag; };
};

class ModelTest {
public:
    explicit ModelTest() {
        qDebug() << "Created: NO ARG";
    };

    explicit ModelTest(ModelTest const & other) {
        Q_UNUSED(other)
        qDebug() << "Created: const-ref ARG";
    };

    explicit ModelTest(ModelTest && other) {
        Q_UNUSED(other)
        qDebug() << "Created: rvalue-ref ARG";
    };

    ModelTest & operator=(ModelTest const & other) {
        Q_UNUSED(other)
        qDebug() << "=: const-ref ARG";
        return *this;
    };

    ModelTest & operator=(ModelTest && other) {
        Q_UNUSED(other)
        qDebug() << "=: rvalue-ref ARG";
        return *this;
    };

    ~ModelTest() { qDebug() << "Released"; };
};

class ModelOptMove {
public:
    QString m_tag;
    QString m_cnstr;

    explicit ModelOptMove()
    : m_tag {"default"} 
    , m_cnstr {"no args"}
    {
        qDebug() << details("DEF cnstr");
    };

    explicit ModelOptMove(QString tag)
    : m_tag { std::move(tag) } 
    , m_cnstr {"with arg"}
    {
        qDebug() << details("ARG cnstr");
    };

    // if explicit then won't compile on arg passing
    ModelOptMove(ModelOptMove const & other)
    : m_tag { std::move(other.m_tag) }
    , m_cnstr {"copy"}
    {
        qDebug() << details("COPY cnstr");
    }

    ModelOptMove(ModelOptMove && other)
    : m_tag { std::move(other.m_tag) }
    , m_cnstr {"move"}
    {
        qDebug() << details("MOVE cnstr");
    }

    ~ModelOptMove() { 
        qDebug() << details("Dsstr");
    };

    QString details(QString && topic) {
        return topic
                .append(" tag: ")
                .append(m_tag)
                .append(" cnstr: ")
                .append(m_cnstr);
    }
};


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
        qDebug() << "Created as copy " << this->tag;
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

        createModels();
        createModelOnStack();
        createModelOnHeap();

        testCreationWithOptMove();
        testMoveOptCalls();
        testMoveOnlyCalls();
    };

    ~CppRefsAndPtrsTestVM() { qDebug() << "Released"; };

    void createModels() {
        qDebug() << "============================";

        //      Model m(...)
        // is equivalent to
        //      Model m = Model(...)

        ModelOnlyWithCopy mowc0("model0 only with copy");
        QString movc1tag = "model1 only with copy";
        ModelOnlyWithCopy mowc1(movc1tag);

        QString mbr2tag = "model2 by ref";
        ModelByRef mbr2(mbr2tag);

        //! error:
        // no matching constructor for initialization of 'ModelByRef'
        // candidate constructor (the implicit copy constructor) not viable: no known conversion from 'QString' to 'const ModelByRef' for 1st argument
        // candidate constructor not viable: expects an l-value for 1st argument
//        ModelByRef mbr2(QString("model2 by ref"));

        //! error:
        // no matching constructor for initialization of 'ModelByRef'
        // candidate constructor (the implicit copy constructor) not viable: no known conversion from 'const char [14]' to 'const ModelByRef' for 1st argument
        // candidate constructor not viable: no known conversion from 'const char [14]' to 'QString &' for 1st argument
//        ModelByRef mbr2("model2 by ref");


        ModelByConstRef mbr3("model3 by const ref");
        QString mbr4tag = "model4 by const ref";
        ModelByConstRef mbr4(mbr4tag);
        ModelByConstRef mbr5(QString("model5 by const ref"));

        ModelByRvalRef mbrvr6("model6 by rvalue ref");
        QString mbrvr7tag = "model7 by rvalue ref";
        qDebug() << "before move mbrvr7tag.len = " << mbrvr7tag.length();
        ModelByRvalRef mbrvr7(std::move(mbrvr7tag));
        qDebug() << "after move mbrvr7tag.len = " << mbrvr7tag.length();
        // no matching constructor for initialization of 'ModelByRvalRef'
        // candidate constructor (the implicit copy constructor) not viable: no known conversion from 'QString' to 'const ModelByRvalRef' for 1st argument
        // candidate constructor not viable: no known conversion from 'QString' to 'QString &&' for 1st argument
//        ModelByRvalRef mbrvr7(mbrvr7tag);

        ModelByConstRvalRef mbcrvr7("model7 by const rvalue ref");
        QString mbrvr8tag = "model8 by const rvalue ref";
        ModelByRvalRef mbrvr8(std::move(mbrvr8tag));
        // error: no matching constructor for initialization of 'ModelByRvalRef'
        // note: candidate constructor (the implicit copy constructor) not viable: no known conversion from 'QString' to 'const ModelByRvalRef' for 1st argument
        // note: candidate constructor not viable: no known conversion from 'QString' to 'QString &&' for 1st argument
//        ModelByRvalRef mbrvr8(mbrvr8tag);

        ModelTest mtest1;
        ModelTest mtest2(mtest1);            // const-ref constructor
        ModelTest mtest3(std::move(mtest1)); // rvalue-ref constructor

        ModelTest mtest4;
        mtest4 = mtest1;             // const-ref assignment

        ModelTest mtest5;
        mtest5 = std::move(mtest1); // rvalue-ref assignment
    };

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

    void testCreationWithOptMove() {
        ModelOptMove mt1("mt1");
        // "mt1" is rvalue, which is moved inside
        // constructor, so no copy at all

        QString mt2tag("mt2");
        ModelOptMove mt2(mt2tag);
        // mt2tag is lvalue, which is passed by value
        // to constructor, so one copy on passing and
        // then one move inside constructor

        QString mt3tag("mt3");
        ModelOptMove mt3(std::move(mt3tag));
        // mt3tag is lvalue, but transformed to rvalue
        // using std::move when passed into constructor,
        // so no copy on passing and, only one move and
        // then one move inside constructor

        QString mt4tag("mt4");
        QString & mt4tagRef = mt4tag;
        ModelOptMove mt4(mt4tagRef);
        // seems like same as by value

        // ModelOptMove mt4(std::move(mt4tagRef));
        // seems like same as by moved value
    };

    void testMoveOptCalls() {
        // 1
        qDebug() << "\n";
        fooMoveOpt(ModelOptMove("mt0"));
        // Only one cnstr called, since it is temp object
        // it will be directly created in function scope

        qDebug() << "\n";
        ModelOptMove mt1("mt1");
        qDebug() << "mt1 addr: " << &mt1;
        qDebug() << mt1.details("mt1 after being created");

        // 2
        qDebug() << "\n";
        fooMoveOpt(mt1);
        // Copy cnstr called, not the best solution
        // but might be desired behaviour
        qDebug() << mt1.details("mt1 after pass by copy");

        // 3
        qDebug() << "\n";
        ModelOptMove & mt1ref = mt1;
        fooMoveOpt(mt1ref);
        // Same as for pass by value
        qDebug() << mt1.details("mt1 after pass by ref");

        // 3.1
        // fooMoveOpt(&mt1);
        // won't compile, instead of pass by ref
        // use std::move below, not optimal, but possible

        // 4
        qDebug() << "\n";
        fooMoveOpt(std::move(mt1));
        // Move cnstr called, better then using copy
        // cnstr, but not as optimal as passing by ref

        // 4.1
        // fooMoveOpt(std::move(mt1ref));
        // same as just move variable
        qDebug() << mt1.details("mt1 after pass by move");

        // We can define on caller side what behaviour
        // we exactly want, because after move has been
        // used moved object is not valid anymore
    }

    void fooMoveOpt(ModelOptMove m){
        qDebug() << "arg addr: " << &m;
        qDebug() << m.details("fooOptMoveCalls");

        /*
            // use the following if you want to
            // pass m further with minimal losses
                auto am = std::move(m);
                // ... do what is necessary
                footMoveOpt2(am);

            // but technically you can just do
                footMoveOpt2(m);
            // if copy is fine
        */
    };

    void footMoveOpt2(ModelOptMove m){ Q_UNUSED(m) };

    void testMoveOnlyCalls() {
        // 1
        qDebug() << "\n";
        fooMoveOnly(ModelOptMove("mt0"));
        // no copy, just perfect forwarding

        qDebug() << "\n";
        ModelOptMove mt1("mt1");
        qDebug() << "mt1 addr: " << &mt1;
        qDebug() << mt1.details("mt1 after being created");

        // 1.1
        // fooMoveOnly(mt1);
        // won't compile, because only rvalue is acceptable

        // 1.2
        // fooMoveOnly(&mt1);
        // won't compile, instead of pass by ref
        // use std::move below

        // 2
        qDebug() << "\n";
        fooMoveOnly(std::move(mt1));
        // no copy, just perfect forwarding
        qDebug() << mt1.details("mt1 after pass by move");
    }

    void fooMoveOnly(ModelOptMove && m){
        qDebug() << "arg addr: " << &m;
        qDebug() << m.details("fooOptMoveCalls");

        /*
            // use the following if you want to
            // pass m further with minimal losses
            fooMoveOnly2(std::move(m));

            // but you can't just use the following
                fooMoveOnly2(m);
            // because m is lvalue, not rvalue
        */
    };

    void fooMoveOnly2(ModelOptMove && m){ Q_UNUSED(m) };

signals:

};
#endif // CPPREFSANDPTRSTESTVM_H
