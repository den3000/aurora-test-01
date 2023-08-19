#ifndef CPPREFSANDPTRSTESTVM_H
#define CPPREFSANDPTRSTESTVM_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "memory"

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

    QString details(QString && topic = "") const {
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

       testByValCalls();
       testByRefCalls();
       testByConstRefCalls();
       testByRvalRefCalls();
       testByConstRvalRefCalls();

       testRvoNrvo();

       testPassSmartPointers();
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
        // 1
        ModelOptMove mt1("mt1");
        // "mt1" is rvalue, which is moved inside
        // constructor, so no copy at all

        // 2
        QString mt2tag("mt2");
        ModelOptMove mt2(mt2tag);
        // mt2tag is lvalue, which is passed by value
        // to constructor, so one copy on passing and
        // then one move inside constructor

        // 3
        QString mt3tag("mt3");
        ModelOptMove mt3(std::move(mt3tag));
        // mt3tag is lvalue, but transformed to rvalue
        // using std::move when passed into constructor,
        // so no copy on passing and, only one move and
        // then one move inside constructor

        // 4
        QString mt4tag("mt4");
        QString & mt4tagRef = mt4tag;
        ModelOptMove mt4(mt4tagRef);
        // seems like same as by value

        // 4.1
        // ModelOptMove mt4(std::move(mt4tagRef));
        // seems like same as by moved value
    };

    // by val
    void testByValCalls() {
        // 1
        qDebug() << "\n";
        fooByVal(ModelOptMove("mt0"));
        // Only one cnstr called, since it is temp object
        // it will be directly created in function scope

        qDebug() << "\n";
        ModelOptMove mt1("mt1");
        qDebug() << mt1.details("mt1 after being created");

        // 2
        qDebug() << "\n";
        fooByVal(mt1);
        // Copy cnstr called, not the best solution
        // but might be desired behaviour
        qDebug() << mt1.details("mt1 after pass by copy");

        // 3
        qDebug() << "\n";
        ModelOptMove & mt1ref = mt1;
        fooByVal(mt1ref);
        // Same as for pass by value
        qDebug() << mt1.details("mt1 after pass by ref");

        // 4
        qDebug() << "\n";
        fooByVal(std::move(mt1));
        // Move cnstr called, better then using copy
        // cnstr, but not as optimal as passing by ref or PF

        // 4.1
        // fooByVal(std::move(mt1ref));
        // same as just move variable
        qDebug() << mt1.details("mt1 after pass by move");
    }

    void fooByVal(ModelOptMove m){
        qDebug() << m.details("fooMoveOpt");

        /*
            // use the following if you want to
            // pass m further with minimal losses
                auto am = std::move(m);
                // ... do what is necessary
                fooByVal2(am);

            // but technically you can just do
                fooByVal2(m);
            // if copy is fine
        */
    };

    void fooByVal2(ModelOptMove m){ Q_UNUSED(m) };

    // by ref
    void testByRefCalls() {
        //
        qDebug() << "\n";
        // fooByRef(ModelOptMove("mt0"));
        // won't compile, since temp object
        // can't be passed by ref

        qDebug() << "\n";
        ModelOptMove mt1("mt1");
        qDebug() << mt1.details("mt1 after being created");

        // 1
        qDebug() << "\n";
        fooByRef(mt1);
        // No cnstr called at all, just passed by ref
        qDebug() << mt1.details("mt1 after pass by ref from val");

        // 2
        qDebug() << "\n";
        ModelOptMove & mt1ref = mt1;
        fooByRef(mt1ref);
        // No cnstr called at all, just passed by ref
        qDebug() << mt1.details("mt1 after pass by ref from ref");

        //
        // fooByRef(std::move(mt1));
        // won't compile: non-const lvalue reference to type 'ModelOptMove' cannot bind to a temporary of type 'typename std::remove_reference<ModelOptMove &>::type' (aka 'ModelOptMove')

        //
        // fooByRef(std::move(mt1ref));
        // won't compile: non-const lvalue reference to type 'ModelOptMove' cannot bind to a temporary of type 'typename std::remove_reference<ModelOptMove &>::type' (aka 'ModelOptMove')
    }

    void fooByRef(ModelOptMove & m){
        qDebug() << m.details("fooRef");

        /*
            // use the following if you want to
            // pass m further with minimal losses
                // ... do what is necessary
                fooByRef2(m);
        */

        fooByRef2(m);
    };

    void fooByRef2(ModelOptMove & m){ Q_UNUSED(m) };

    // by const ref
    void testByConstRefCalls() {
        // 1
        qDebug() << "\n";
        fooConstRef(ModelOptMove("mt0"));
        // Only one cnstr called, since it is temp object
        // it will be directly created in function scope

        qDebug() << "\n";
        ModelOptMove mt1("mt1");
        qDebug() << mt1.details("mt1 after being created");

        // 2
        qDebug() << "\n";
        fooConstRef(mt1);
        // just passed by ref
        qDebug() << mt1.details("mt1 after pass by ref from val");

        // 3
        qDebug() << "\n";
        ModelOptMove & mt1ref = mt1;
        fooConstRef(mt1ref);
        // just passed by ref
        qDebug() << mt1.details("mt1 after pass by ref from ref");

        // 4
        qDebug() << "\n";
        fooConstRef(std::move(mt1));
        // just passed by ref

        // 4.1
        // fooConstRef(std::move(mt1ref));
        // just passed by ref
        qDebug() << mt1.details("mt1 after pass by move");
    }

    void fooConstRef(ModelOptMove const & m){
        // m is immutable here
        qDebug() << m.details("fooConstRef");

        /*
            // use the following if you want to
            // pass m further with minimal losses
                // ... do what is necessary
                fooConstRef2(m);
        */

        fooConstRef2(m);
    };

    void fooConstRef2(ModelOptMove const & m){ Q_UNUSED(m) };

    // by rval ref
    void testByRvalRefCalls() {
        // 1
        qDebug() << "\n";
        fooByRvalRef(ModelOptMove("mt0"));
        // no copy, just perfect forwarding

        qDebug() << "\n";
        ModelOptMove mt1("mt1");
        ModelOptMove &mt1ref = mt1; Q_UNUSED(mt1ref)
        qDebug() << mt1.details("mt1 after being created");

        //
        // fooByRvalRef(mt1);
        // won't compile, because only rvalue is acceptable

        //
        // fooByRvalRef(mt1ref);
        // won't compile: mt1ref is lvalue, rvalue required

        // 2
        qDebug() << "\n";
        fooByRvalRef(std::move(mt1));
        // no copy, just perfect forwarding
        qDebug() << mt1.details("mt1 after pass by move");

        //
        // fooByRvalRef(std::move(mt1ref));
        // no copy, just perfect forwarding, but doesn't make sense, just use 2.
    }

    void fooByRvalRef(ModelOptMove && m){
        qDebug() << m.details("fooMoveOnly");
        m.m_tag = "";
        /*
            // use the following if you want to
            // pass m further with minimal losses
            fooByRvalRef2(std::move(m));

            // but you can't just use the following
                fooByRvalRef2(m);
            // because m is lvalue, not rvalue
        */
    };

    void fooByRvalRef2(ModelOptMove && m){ Q_UNUSED(m) };

    // by const rval ref
    void testByConstRvalRefCalls() {
        // 1
        qDebug() << "\n";
        fooByConstRvalRef(ModelOptMove("mt0"));
        // no copy, just perfect forwarding

        qDebug() << "\n";
        ModelOptMove mt1("mt1");
        qDebug() << mt1.details("mt1 after being created");

        //
        // fooConstMoveOnly(mt1);
        // won't compile, because only rvalue is acceptable

        // 2
        qDebug() << "\n";
        fooByConstRvalRef(std::move(mt1));
        // no copy, just perfect forwarding
        qDebug() << mt1.details("mt1 after pass by move");
    }

    void fooByConstRvalRef(ModelOptMove const && m){
        // m is immutable here

        qDebug() << m.details("fooMoveOnly");

        /*
            // use the following if you want to
            // pass m further with minimal losses
            fooByConstRvalRef2(std::move(m));

            // but you can't just use the following
                fooByConstRvalRef2(m);
            // because m is lvalue, not rvalue
        */
    };

    void fooByConstRvalRef2(ModelOptMove const && m){ Q_UNUSED(m) };

    // all calls
    void testAllCalls(){
        ModelOptMove mt0("mt0");
        ModelOptMove & mtRef0 = mt0;

        fooByVal(ModelOptMove("mt0_in_place"));
        fooByVal(mt0);
        fooByVal(mtRef0);
        fooByVal(std::move(mt0));
        fooByVal(std::move(mtRef0));

        ModelOptMove mt1("mt1");
        ModelOptMove & mtRef1 = mt1;

        // fooByRef(ModelOptMove("mt1"));
        fooByRef(mt1);
        fooByRef(mtRef1);
        // fooByRef(std::move(mt1));
        // fooByRef(std::move(mtRef1));

        ModelOptMove mt2("mt2");
        ModelOptMove & mtRef2 = mt2;

        fooConstRef(ModelOptMove("mt2_in_place"));
        fooConstRef(mt2);
        fooConstRef(mtRef2);
        fooConstRef(std::move(mt2));
        fooConstRef(std::move(mtRef2));

        ModelOptMove mt3("mt3");
        ModelOptMove & mtRef3 = mt3;

        fooByRvalRef(ModelOptMove("mt3_in_place"));
        // fooByRvalRef(mt3);
        // fooByRvalRef(mtRef3);
        fooByRvalRef(std::move(mt3));
        fooByRvalRef(std::move(mtRef3));
    };

    // rvo / nrvo
    void testRvoNrvo(){
        qDebug() << "\n";
        ModelOptMove mRvo1 = fooRvo1();
        ModelOptMove mRvo2 = fooRvo2(2);
        ModelOptMove mNrvo1 = fooNrvo1();
        ModelOptMove mNrvo2 = fooNrvo2(2);

        ModelOptMove mNrvoFail1 = fooNrvoFail1(2);
        ModelOptMove mNrvoFail2_2 = fooNrvoFail2(2);
        ModelOptMove mNrvoFail2_3 = fooNrvoFail2(3);
    };

    ModelOptMove fooRvo1() {
        qDebug() << "\n";
        return ModelOptMove("rvo1");
    };

    ModelOptMove fooRvo2(int i) {
        qDebug() << "\n";
        switch (i) {
        case 1: return ModelOptMove("rvo2_1");
        case 2: return ModelOptMove("rvo2_2");
        case 3: return ModelOptMove("rvo2_3");
        default: return ModelOptMove("rvo2_def");
        }
    };

    ModelOptMove fooNrvo1() {
        qDebug() << "\n";
        ModelOptMove m("nrvo1");
        return m;
    };

    ModelOptMove fooNrvo2(int i) {
        qDebug() << "\n";

        ModelOptMove m;
        switch (i) {
        case 1: m.m_tag = "nrvo2_1"; break;
        case 2: m.m_tag = "nrvo2_2"; break;
        case 3: m.m_tag = "nrvo2_3"; break;
        default: m.m_tag = "nrvo2_def"; break;
        }

        return m;
    };

    ModelOptMove fooNrvoFail1(int i) {
        qDebug() << "\n";

        switch (i) {
        case 1: {
            ModelOptMove m("nrvofail1_1");
            return m; // move constructor used
        }
        case 2: {
            ModelOptMove m("nrvofail1_2");
            return m; // move constructor used
        }
        case 3: {
            ModelOptMove m("nrvofail1_3");
            return m; // move constructor used
        }
        default: {
            ModelOptMove m("nrvofail1_def");
            return m; // move constructor used
        }
        }
    };

    ModelOptMove fooNrvoFail2(int i) {
        qDebug() << "\n";
        if (i == 2) {
            return ModelOptMove("nrvofail1_2"); // rvo used
        }

        ModelOptMove m;
        switch (i) {
        case 1: m.m_tag = "nrvofail1_1"; break; // move constructor used
        case 3: m.m_tag = "nrvofail1_3"; break; // move constructor used
        default: m.m_tag = "nrvofail1_def"; break; // move constructor used
        }

        return m;
    };

    // smart pointers
    void testPassSmartPointers(){
        // shared
        qDebug() << "\n";
        auto spm1 = std::make_shared<ModelOptMove>("spm1");
        auto spm2 = std::shared_ptr<ModelOptMove>(new ModelOptMove("spm2"));
        std::shared_ptr<ModelOptMove> spm3(new ModelOptMove("spm3"));

        qDebug() << "\n";
        qDebug() << "spm1.useCount = " << spm1.use_count();
        fooSharedPtrTest(spm1);
        qDebug() << "spm1.useCount = " << spm1.use_count();

        // weak
        qDebug() << "\n";
        auto spm4 = std::make_shared<ModelOptMove>("spm4");
        std::weak_ptr<ModelOptMove> wpm4(spm4);

        qDebug() << "spm4.useCount = " << spm1.use_count();
        qDebug() << "wpm4.useCount = " << wpm4.use_count();
        fooWeakPtrTest(wpm4);

        // unique
        qDebug() << "\n";
        auto upm1 = std::make_unique<ModelOptMove>("upm1");
        auto upm2 = std::unique_ptr<ModelOptMove>(new ModelOptMove("upm2"));
        std::unique_ptr<ModelOptMove> upm3(new ModelOptMove("upm3"));

        qDebug() << upm1.get()->details("unique before fooUniquePtrTest");
        fooUniquePtrTest(std::move(upm1));
        // will cause crash, unique ptr should not be accesed after move
        // qDebug() << upm1.get()->details("unique after fooUniquePtrTest");
    };

    void fooSharedPtrTest(std::shared_ptr<ModelOptMove> spm) {
        qDebug() << "spm.useCount = " << spm.use_count();
        auto details = spm.get()->details("shared");
        qDebug() << details;
    }

    void fooWeakPtrTest(std::weak_ptr<ModelOptMove> wpm) {
        qDebug() << "wpm.useCount = " << wpm.use_count();
        qDebug() << wpm.lock().get()->details("weak");
    }

    void fooUniquePtrTest(std::unique_ptr<ModelOptMove> upm) {
        auto details = upm.get()->details("unique");
        qDebug() << details;
    }


signals:

};
#endif // CPPREFSANDPTRSTESTVM_H
