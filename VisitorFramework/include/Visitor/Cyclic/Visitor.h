/*
 * VisitorCyclic.h
 *
 *  Created on: 10.11.2016
 *      Author: Gerd
 */

#ifndef VISITORCYCLIC_H_
#define VISITORCYCLIC_H_

#include "../BaseKind.h"
#include "../TypeFunctions.h"

#include <typeinfo>

namespace VisitorFramework{

namespace Cyclic {
//=================================================================
// Visitables
//=================================================================
template<class VisitorBase>
class Visitable
{
public:
    virtual ~Visitable(){};
	virtual void accept(VisitorBase& visitor) = 0;
	virtual std::string toString() const{
			return typeid(*this).name();
	}
};
//---------------------------------------------------------------------
/**
 * Baseclass for all Visitables:
 * usage: MyVisitable : VisitableImpl<MyVisitable, ...>{...}
 * is used in Repository
 */
template
	<
		class ConcreteVisitable,
		class VisitorBase,
		class LoggingPolicy,
		class VisitableImplementation = ConcreteVisitable
	>
struct VisitableImpl : Visitable<VisitorBase>, LoggingPolicy {
	typedef Visitable<VisitorBase> base_type;

	void accept(VisitorBase& visitor){
		this->logAccepted(*this, visitor);
		decltype(auto) visitable = This()->getVisitable();

		// visitable kann z.B. shared_ptr<ConcreteVisitable> sein
		// der nicht mehr gültig ist
		if(!visitable){
			this->logInvalidVisitable(*this, visitor);
			return;
		}
		visitor.visit(*(This()->getVisitable()) );
	}
protected:
	// Muss überschrieben werden wenn ConcreteVisitable und
	// VisitableImplementation nicht übereinstimmen (siehe Adapter)
	ConcreteVisitable* getVisitable() {
		return static_cast<ConcreteVisitable*>(this);
	}
	ConcreteVisitable const* getVisitable() const {
		return static_cast<ConcreteVisitable const*>(this);
	}

	VisitableImplementation* This(){
		return static_cast<VisitableImplementation*>(this);
	}
	VisitableImplementation const* This() const {
		return static_cast<VisitableImplementation const*>(this);
	}
};
//=================================================================
// Visitors
//=================================================================
/**
 * infrastructure to Create the Baseclass of a Cyclic Visitor
 * class A; class B; class C;
 */
template<class LoggingPolicy, class ToVisit, class... Rest>
struct InheritFromDefault
	:
//	protected getAccessor<ToVisit>,
	public InheritFromDefault<LoggingPolicy, Rest...>
{
public:
	virtual void visit(ToVisit& visitable){
//		LoggingPolicy::logNotVisited(visitable, *this);
		this->logNotVisited(visitable, *this);
	}

	using InheritFromDefault<LoggingPolicy, Rest...>::visit;
};
template<class LoggingPolicy, class ToVisit>
struct InheritFromDefault<LoggingPolicy, ToVisit>
	:
//	protected getAccessor<ToVisit>,
	public LoggingPolicy
{
public:
	virtual void visit(ToVisit& visitable){
//		LoggingPolicy::logNotVisited(visitable, *this);
		this->logNotVisited(visitable, *this);
	}

	virtual std::string toString() const{
			return typeid(*this).name();
		}
};
//---------------------------------------------------------------------
template<class ToVisit, class... Rest>
struct InheritFromAbstract
	:
//	protected getAccessor<ToVisit>,
	public InheritFromAbstract<Rest...>{
public:
	virtual void visit(ToVisit& v) = 0;
	using base_type = InheritFromAbstract<Rest...>;
	using base_type::visit;
};
template<class ToVisit>
struct InheritFromAbstract<ToVisit>
//	: protected getAccessor<ToVisit>
{
public:
	virtual void visit(ToVisit& v) = 0;

	virtual std::string toString() const{
			return typeid(*this).name();
		}
};
//---------------------------------------------------------------------
/**
 * infrastructure to Create the Baseclass of a Cyclic Visitor
 * class A; class B; class C;
 * usage: using VisitorBase = visitsDefault<A, B, C>;
 */
//template<class LogginPolicy, class ToVisit, class...Rest>
//using visitsDefault = InheritFromDefault<LogginPolicy, ToVisit, Rest...>;
//template<class ToVisit, class...Rest>
//using visitsAbstract = InheritFromAbstract<ToVisit, Rest...>;
//---------------------------------------------------------------------

template<class LoggingPolicy_, class = BaseKind::Abstract>
struct SwitchBaseKind{
	template<class ...Visitables>
	using implementsVisitor = Cyclic::InheritFromAbstract<Visitables...>;
};
template<class LoggingPolicy_>
struct SwitchBaseKind<LoggingPolicy_, BaseKind::Default>{
	template<class ...Visitables>
	using implementsVisitor = Cyclic::InheritFromDefault<LoggingPolicy_, Visitables...>;
};

}} // end namespace VisitorCyclic


#endif /* VISITORCYCLIC_H_ */
