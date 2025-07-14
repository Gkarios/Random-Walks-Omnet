//
// Generated file, do not edit! Created by opp_msgtool 6.1 from RandomWalkerMsg.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "RandomWalkerMsg_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Class(RandomWalkerMsg)

RandomWalkerMsg::RandomWalkerMsg(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

RandomWalkerMsg::RandomWalkerMsg(const RandomWalkerMsg& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

RandomWalkerMsg::~RandomWalkerMsg()
{
    delete [] this->path;
    delete [] this->visitedNodes;
    delete [] this->visitedPerHop;
}

RandomWalkerMsg& RandomWalkerMsg::operator=(const RandomWalkerMsg& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void RandomWalkerMsg::copy(const RandomWalkerMsg& other)
{
    this->hopCountr = other.hopCountr;
    delete [] this->path;
    this->path = (other.path_arraysize==0) ? nullptr : new int[other.path_arraysize];
    path_arraysize = other.path_arraysize;
    for (size_t i = 0; i < path_arraysize; i++) {
        this->path[i] = other.path[i];
    }
    delete [] this->visitedNodes;
    this->visitedNodes = (other.visitedNodes_arraysize==0) ? nullptr : new int[other.visitedNodes_arraysize];
    visitedNodes_arraysize = other.visitedNodes_arraysize;
    for (size_t i = 0; i < visitedNodes_arraysize; i++) {
        this->visitedNodes[i] = other.visitedNodes[i];
    }
    delete [] this->visitedPerHop;
    this->visitedPerHop = (other.visitedPerHop_arraysize==0) ? nullptr : new int[other.visitedPerHop_arraysize];
    visitedPerHop_arraysize = other.visitedPerHop_arraysize;
    for (size_t i = 0; i < visitedPerHop_arraysize; i++) {
        this->visitedPerHop[i] = other.visitedPerHop[i];
    }
    this->walkerId = other.walkerId;
}

void RandomWalkerMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->hopCountr);
    b->pack(path_arraysize);
    doParsimArrayPacking(b,this->path,path_arraysize);
    b->pack(visitedNodes_arraysize);
    doParsimArrayPacking(b,this->visitedNodes,visitedNodes_arraysize);
    b->pack(visitedPerHop_arraysize);
    doParsimArrayPacking(b,this->visitedPerHop,visitedPerHop_arraysize);
    doParsimPacking(b,this->walkerId);
}

void RandomWalkerMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->hopCountr);
    delete [] this->path;
    b->unpack(path_arraysize);
    if (path_arraysize == 0) {
        this->path = nullptr;
    } else {
        this->path = new int[path_arraysize];
        doParsimArrayUnpacking(b,this->path,path_arraysize);
    }
    delete [] this->visitedNodes;
    b->unpack(visitedNodes_arraysize);
    if (visitedNodes_arraysize == 0) {
        this->visitedNodes = nullptr;
    } else {
        this->visitedNodes = new int[visitedNodes_arraysize];
        doParsimArrayUnpacking(b,this->visitedNodes,visitedNodes_arraysize);
    }
    delete [] this->visitedPerHop;
    b->unpack(visitedPerHop_arraysize);
    if (visitedPerHop_arraysize == 0) {
        this->visitedPerHop = nullptr;
    } else {
        this->visitedPerHop = new int[visitedPerHop_arraysize];
        doParsimArrayUnpacking(b,this->visitedPerHop,visitedPerHop_arraysize);
    }
    doParsimUnpacking(b,this->walkerId);
}

int RandomWalkerMsg::getHopCountr() const
{
    return this->hopCountr;
}

void RandomWalkerMsg::setHopCountr(int hopCountr)
{
    this->hopCountr = hopCountr;
}

size_t RandomWalkerMsg::getPathArraySize() const
{
    return path_arraysize;
}

int RandomWalkerMsg::getPath(size_t k) const
{
    if (k >= path_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)path_arraysize, (unsigned long)k);
    return this->path[k];
}

void RandomWalkerMsg::setPathArraySize(size_t newSize)
{
    int *path2 = (newSize==0) ? nullptr : new int[newSize];
    size_t minSize = path_arraysize < newSize ? path_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        path2[i] = this->path[i];
    for (size_t i = minSize; i < newSize; i++)
        path2[i] = 0;
    delete [] this->path;
    this->path = path2;
    path_arraysize = newSize;
}

void RandomWalkerMsg::setPath(size_t k, int path)
{
    if (k >= path_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)path_arraysize, (unsigned long)k);
    this->path[k] = path;
}

void RandomWalkerMsg::insertPath(size_t k, int path)
{
    if (k > path_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)path_arraysize, (unsigned long)k);
    size_t newSize = path_arraysize + 1;
    int *path2 = new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        path2[i] = this->path[i];
    path2[k] = path;
    for (i = k + 1; i < newSize; i++)
        path2[i] = this->path[i-1];
    delete [] this->path;
    this->path = path2;
    path_arraysize = newSize;
}

void RandomWalkerMsg::appendPath(int path)
{
    insertPath(path_arraysize, path);
}

void RandomWalkerMsg::erasePath(size_t k)
{
    if (k >= path_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)path_arraysize, (unsigned long)k);
    size_t newSize = path_arraysize - 1;
    int *path2 = (newSize == 0) ? nullptr : new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        path2[i] = this->path[i];
    for (i = k; i < newSize; i++)
        path2[i] = this->path[i+1];
    delete [] this->path;
    this->path = path2;
    path_arraysize = newSize;
}

size_t RandomWalkerMsg::getVisitedNodesArraySize() const
{
    return visitedNodes_arraysize;
}

int RandomWalkerMsg::getVisitedNodes(size_t k) const
{
    if (k >= visitedNodes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)visitedNodes_arraysize, (unsigned long)k);
    return this->visitedNodes[k];
}

void RandomWalkerMsg::setVisitedNodesArraySize(size_t newSize)
{
    int *visitedNodes2 = (newSize==0) ? nullptr : new int[newSize];
    size_t minSize = visitedNodes_arraysize < newSize ? visitedNodes_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        visitedNodes2[i] = this->visitedNodes[i];
    for (size_t i = minSize; i < newSize; i++)
        visitedNodes2[i] = 0;
    delete [] this->visitedNodes;
    this->visitedNodes = visitedNodes2;
    visitedNodes_arraysize = newSize;
}

void RandomWalkerMsg::setVisitedNodes(size_t k, int visitedNodes)
{
    if (k >= visitedNodes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)visitedNodes_arraysize, (unsigned long)k);
    this->visitedNodes[k] = visitedNodes;
}

void RandomWalkerMsg::insertVisitedNodes(size_t k, int visitedNodes)
{
    if (k > visitedNodes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)visitedNodes_arraysize, (unsigned long)k);
    size_t newSize = visitedNodes_arraysize + 1;
    int *visitedNodes2 = new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        visitedNodes2[i] = this->visitedNodes[i];
    visitedNodes2[k] = visitedNodes;
    for (i = k + 1; i < newSize; i++)
        visitedNodes2[i] = this->visitedNodes[i-1];
    delete [] this->visitedNodes;
    this->visitedNodes = visitedNodes2;
    visitedNodes_arraysize = newSize;
}

void RandomWalkerMsg::appendVisitedNodes(int visitedNodes)
{
    insertVisitedNodes(visitedNodes_arraysize, visitedNodes);
}

void RandomWalkerMsg::eraseVisitedNodes(size_t k)
{
    if (k >= visitedNodes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)visitedNodes_arraysize, (unsigned long)k);
    size_t newSize = visitedNodes_arraysize - 1;
    int *visitedNodes2 = (newSize == 0) ? nullptr : new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        visitedNodes2[i] = this->visitedNodes[i];
    for (i = k; i < newSize; i++)
        visitedNodes2[i] = this->visitedNodes[i+1];
    delete [] this->visitedNodes;
    this->visitedNodes = visitedNodes2;
    visitedNodes_arraysize = newSize;
}

size_t RandomWalkerMsg::getVisitedPerHopArraySize() const
{
    return visitedPerHop_arraysize;
}

int RandomWalkerMsg::getVisitedPerHop(size_t k) const
{
    if (k >= visitedPerHop_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)visitedPerHop_arraysize, (unsigned long)k);
    return this->visitedPerHop[k];
}

void RandomWalkerMsg::setVisitedPerHopArraySize(size_t newSize)
{
    int *visitedPerHop2 = (newSize==0) ? nullptr : new int[newSize];
    size_t minSize = visitedPerHop_arraysize < newSize ? visitedPerHop_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        visitedPerHop2[i] = this->visitedPerHop[i];
    for (size_t i = minSize; i < newSize; i++)
        visitedPerHop2[i] = 0;
    delete [] this->visitedPerHop;
    this->visitedPerHop = visitedPerHop2;
    visitedPerHop_arraysize = newSize;
}

void RandomWalkerMsg::setVisitedPerHop(size_t k, int visitedPerHop)
{
    if (k >= visitedPerHop_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)visitedPerHop_arraysize, (unsigned long)k);
    this->visitedPerHop[k] = visitedPerHop;
}

void RandomWalkerMsg::insertVisitedPerHop(size_t k, int visitedPerHop)
{
    if (k > visitedPerHop_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)visitedPerHop_arraysize, (unsigned long)k);
    size_t newSize = visitedPerHop_arraysize + 1;
    int *visitedPerHop2 = new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        visitedPerHop2[i] = this->visitedPerHop[i];
    visitedPerHop2[k] = visitedPerHop;
    for (i = k + 1; i < newSize; i++)
        visitedPerHop2[i] = this->visitedPerHop[i-1];
    delete [] this->visitedPerHop;
    this->visitedPerHop = visitedPerHop2;
    visitedPerHop_arraysize = newSize;
}

void RandomWalkerMsg::appendVisitedPerHop(int visitedPerHop)
{
    insertVisitedPerHop(visitedPerHop_arraysize, visitedPerHop);
}

void RandomWalkerMsg::eraseVisitedPerHop(size_t k)
{
    if (k >= visitedPerHop_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)visitedPerHop_arraysize, (unsigned long)k);
    size_t newSize = visitedPerHop_arraysize - 1;
    int *visitedPerHop2 = (newSize == 0) ? nullptr : new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        visitedPerHop2[i] = this->visitedPerHop[i];
    for (i = k; i < newSize; i++)
        visitedPerHop2[i] = this->visitedPerHop[i+1];
    delete [] this->visitedPerHop;
    this->visitedPerHop = visitedPerHop2;
    visitedPerHop_arraysize = newSize;
}

int RandomWalkerMsg::getWalkerId() const
{
    return this->walkerId;
}

void RandomWalkerMsg::setWalkerId(int walkerId)
{
    this->walkerId = walkerId;
}

class RandomWalkerMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_hopCountr,
        FIELD_path,
        FIELD_visitedNodes,
        FIELD_visitedPerHop,
        FIELD_walkerId,
    };
  public:
    RandomWalkerMsgDescriptor();
    virtual ~RandomWalkerMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(RandomWalkerMsgDescriptor)

RandomWalkerMsgDescriptor::RandomWalkerMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(RandomWalkerMsg)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

RandomWalkerMsgDescriptor::~RandomWalkerMsgDescriptor()
{
    delete[] propertyNames;
}

bool RandomWalkerMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RandomWalkerMsg *>(obj)!=nullptr;
}

const char **RandomWalkerMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RandomWalkerMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RandomWalkerMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int RandomWalkerMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_hopCountr
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_path
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_visitedNodes
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_visitedPerHop
        FD_ISEDITABLE,    // FIELD_walkerId
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *RandomWalkerMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "hopCountr",
        "path",
        "visitedNodes",
        "visitedPerHop",
        "walkerId",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int RandomWalkerMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "hopCountr") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "path") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "visitedNodes") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "visitedPerHop") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "walkerId") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *RandomWalkerMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_hopCountr
        "int",    // FIELD_path
        "int",    // FIELD_visitedNodes
        "int",    // FIELD_visitedPerHop
        "int",    // FIELD_walkerId
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **RandomWalkerMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *RandomWalkerMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int RandomWalkerMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RandomWalkerMsg *pp = omnetpp::fromAnyPtr<RandomWalkerMsg>(object); (void)pp;
    switch (field) {
        case FIELD_path: return pp->getPathArraySize();
        case FIELD_visitedNodes: return pp->getVisitedNodesArraySize();
        case FIELD_visitedPerHop: return pp->getVisitedPerHopArraySize();
        default: return 0;
    }
}

void RandomWalkerMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RandomWalkerMsg *pp = omnetpp::fromAnyPtr<RandomWalkerMsg>(object); (void)pp;
    switch (field) {
        case FIELD_path: pp->setPathArraySize(size); break;
        case FIELD_visitedNodes: pp->setVisitedNodesArraySize(size); break;
        case FIELD_visitedPerHop: pp->setVisitedPerHopArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RandomWalkerMsg'", field);
    }
}

const char *RandomWalkerMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RandomWalkerMsg *pp = omnetpp::fromAnyPtr<RandomWalkerMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RandomWalkerMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RandomWalkerMsg *pp = omnetpp::fromAnyPtr<RandomWalkerMsg>(object); (void)pp;
    switch (field) {
        case FIELD_hopCountr: return long2string(pp->getHopCountr());
        case FIELD_path: return long2string(pp->getPath(i));
        case FIELD_visitedNodes: return long2string(pp->getVisitedNodes(i));
        case FIELD_visitedPerHop: return long2string(pp->getVisitedPerHop(i));
        case FIELD_walkerId: return long2string(pp->getWalkerId());
        default: return "";
    }
}

void RandomWalkerMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RandomWalkerMsg *pp = omnetpp::fromAnyPtr<RandomWalkerMsg>(object); (void)pp;
    switch (field) {
        case FIELD_hopCountr: pp->setHopCountr(string2long(value)); break;
        case FIELD_path: pp->setPath(i,string2long(value)); break;
        case FIELD_visitedNodes: pp->setVisitedNodes(i,string2long(value)); break;
        case FIELD_visitedPerHop: pp->setVisitedPerHop(i,string2long(value)); break;
        case FIELD_walkerId: pp->setWalkerId(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RandomWalkerMsg'", field);
    }
}

omnetpp::cValue RandomWalkerMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RandomWalkerMsg *pp = omnetpp::fromAnyPtr<RandomWalkerMsg>(object); (void)pp;
    switch (field) {
        case FIELD_hopCountr: return pp->getHopCountr();
        case FIELD_path: return pp->getPath(i);
        case FIELD_visitedNodes: return pp->getVisitedNodes(i);
        case FIELD_visitedPerHop: return pp->getVisitedPerHop(i);
        case FIELD_walkerId: return pp->getWalkerId();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RandomWalkerMsg' as cValue -- field index out of range?", field);
    }
}

void RandomWalkerMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RandomWalkerMsg *pp = omnetpp::fromAnyPtr<RandomWalkerMsg>(object); (void)pp;
    switch (field) {
        case FIELD_hopCountr: pp->setHopCountr(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_path: pp->setPath(i,omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_visitedNodes: pp->setVisitedNodes(i,omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_visitedPerHop: pp->setVisitedPerHop(i,omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_walkerId: pp->setWalkerId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RandomWalkerMsg'", field);
    }
}

const char *RandomWalkerMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr RandomWalkerMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RandomWalkerMsg *pp = omnetpp::fromAnyPtr<RandomWalkerMsg>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RandomWalkerMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RandomWalkerMsg *pp = omnetpp::fromAnyPtr<RandomWalkerMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RandomWalkerMsg'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

