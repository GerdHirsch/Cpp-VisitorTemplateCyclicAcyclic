/*
 * AdapterTest.h
 *
 *  Created on: 10.01.2017
 *      Author: Gerd
 */

#ifndef INCLUDE_ADAPTERTEST_H_
#define INCLUDE_ADAPTERTEST_H_

#include "../Mocks/NonVisitable.h"

#include "../Mocks/DefaultPolicy.h"

#include "../Mocks/MockVisitor.h"

#include "../Mocks/CyclicVisitables.h"
#include "../Mocks/AcyclicVisitables.h"

#include "../Mocks/CyclicRepository.h"
#include "../Mocks/AcyclicRepository.h"

#include <memory>
#include <iostream>

namespace CR = CyclicRepository;
namespace AR = AcyclicRepository;

class AdapterTest{
	using this_type = AdapterTest;

	// TODO how to test this property?
	void notConstructibleWithRValueSharedPtr();
	//=====================================
	// Cyclic
	//=====================================
	void visitCyclicAdapterByReference();
	void visitCyclicAdapterByValue();

	void visitCyclicAdapterByWeakpointer();
	void visitCyclicAdapterInvalidVisitable();
	void cyclicAdapterWeakpointerStayValid();
	//=====================================
	// Acyclic
	//=====================================
	void visitAcyclicAdapterByReference();
	void visitAcyclicAdapterByValue();

	void visitAcyclicAdapterByWeakpointer();
	void visitAcyclicAdapterInvalidVisitable();
	void acyclicAdapterWeakpointerStayValid();

public:
	template<class DerivedTest = this_type>
	static cute::suite make_suite(){
		cute::suite s { };
		//=====================================
		// Cyclic
		//=====================================
		s.push_back(CUTE_SMEMFUN(DerivedTest, visitCyclicAdapterByReference));
		s.push_back(CUTE_SMEMFUN(DerivedTest, visitCyclicAdapterByValue));
		s.push_back(CUTE_SMEMFUN(DerivedTest, visitCyclicAdapterByWeakpointer));
		s.push_back(CUTE_SMEMFUN(DerivedTest, visitCyclicAdapterInvalidVisitable));
		s.push_back(CUTE_SMEMFUN(DerivedTest, cyclicAdapterWeakpointerStayValid));
		//=====================================
		// Acyclic
		//=====================================
		s.push_back(CUTE_SMEMFUN(DerivedTest, visitAcyclicAdapterByReference));
		s.push_back(CUTE_SMEMFUN(DerivedTest, visitAcyclicAdapterByValue));
		s.push_back(CUTE_SMEMFUN(DerivedTest, visitAcyclicAdapterByWeakpointer));
		s.push_back(CUTE_SMEMFUN(DerivedTest, visitAcyclicAdapterInvalidVisitable));
		s.push_back(CUTE_SMEMFUN(DerivedTest, acyclicAdapterWeakpointerStayValid));

		return s;
	}
};

//=====================================
// Cyclic
//=====================================
inline
void AdapterTest::visitCyclicAdapterByReference(){
	NonVisitable nonVisitable;
	CR::Repository::AdapterByReference<NonVisitable> adapter(nonVisitable);

	using Visitor = VTM::MockVisitor<CR::Repository, CR::E1, NonVisitable>;
	Visitor visitor;
	adapter.accept(visitor);

	ASSERTM("Cyclic Visitor::visit(NonVisitable&) not called", visitor.nonVisitableVisited);
}
inline
void AdapterTest::visitCyclicAdapterByValue(){
	NonVisitable nonVisitable;
	CR::Repository::AdapterByValue<NonVisitable> adapter(nonVisitable);
	//tempor�re objekte Adapter Ctor
	CR::Repository::AdapterByValue<NonVisitable> adapterWithTemp((NonVisitable()) );

	using Visitor = VTM::MockVisitor<CR::Repository, CR::E1, NonVisitable>;
	Visitor visitor;
	adapter.accept(visitor);

	ASSERTM("Cyclic Visitor::visit(NonVisitable&) not called", visitor.nonVisitableVisited);
}
inline
void AdapterTest::visitCyclicAdapterByWeakpointer(){

	auto nonVisitable = std::make_shared<NonVisitable>();
	CR::Repository::AdapterByWeakpointer<NonVisitable> adapter(nonVisitable);

	using Visitor = VTM::MockVisitor<CR::Repository, CR::E1, NonVisitable>;
	Visitor visitor;
	adapter.accept(visitor);

	ASSERTM("Cyclic Visitor::visit(NonVisitable&) not called", visitor.nonVisitableVisited);
}
inline
void AdapterTest::visitCyclicAdapterInvalidVisitable(){
	using Adapter = CR::Repository::AdapterByWeakpointer<NonVisitable>;
	std::shared_ptr<Adapter> pAdapter;
	{
		auto nonVisitable = std::make_shared<NonVisitable>();
		pAdapter = std::make_shared<Adapter>(nonVisitable);
	}

	using Visitor = VTM::MockVisitor<CR::Repository, CR::E1, NonVisitable>;
	Visitor visitor;

	ASSERTM("DefaultPolicy logInvalidVisitable not initialized", !VTM::MockLoggingPolicy::invalidVisitable);

	pAdapter->accept(visitor);

	ASSERTM("DefaultPolicy logInvalidVisitable not called", VTM::MockLoggingPolicy::invalidVisitable);
}
inline
void AdapterTest::cyclicAdapterWeakpointerStayValid(){
	using Adapter = CR::Repository::AdapterByWeakpointer<NonVisitable>;
	auto nonVisitable = std::make_shared<NonVisitable>();

	std::weak_ptr<NonVisitable> pWeak(nonVisitable);

	auto pAdapter = std::make_shared<Adapter>(pWeak);;
	auto p = pWeak.lock();

	ASSERTM("Weak_ptr not copied", p != nullptr );
}
//=====================================
// Acyclic
//=====================================
inline
void AdapterTest::visitAcyclicAdapterByReference(){
	NonVisitable nonVisitable;
	AR::Repository::AdapterByReference<NonVisitable> adapter(nonVisitable);

	using Visitor = VTM::MockVisitor<AR::Repository, AR::E1, NonVisitable>;
	Visitor visitor;
	adapter.accept(visitor);

	ASSERTM("Cyclic Visitor::visit(NonVisitable&) not called", visitor.nonVisitableVisited);
}
inline
void AdapterTest::visitAcyclicAdapterByValue(){

	NonVisitable nonVisitable;
	AR::Repository::AdapterByValue<NonVisitable> adapter(nonVisitable);
//	AR::Repository::AdapterByValue<NonVisitable> adapter((NonVisitable()) );

	using Visitor = VTM::MockVisitor<AR::Repository, AR::E1, NonVisitable>;
	Visitor visitor;
	adapter.accept(visitor);

	ASSERTM("Cyclic Visitor::visit(NonVisitable&) not called", visitor.nonVisitableVisited);
}
inline
void AdapterTest::visitAcyclicAdapterByWeakpointer(){

	auto nonVisitable = std::make_shared<NonVisitable>();
	AR::Repository::AdapterByWeakpointer<NonVisitable> adapter(nonVisitable);

	using Visitor = VTM::MockVisitor<AR::Repository, AR::E1, NonVisitable>;
	Visitor visitor;
	adapter.accept(visitor);

	ASSERTM("Cyclic Visitor::visit(NonVisitable&) not called", visitor.nonVisitableVisited);
}
inline
void AdapterTest::visitAcyclicAdapterInvalidVisitable(){
	using Adapter = AR::Repository::AdapterByWeakpointer<NonVisitable>;
	std::shared_ptr<Adapter> pAdapter;
	{
		auto nonVisitable = std::make_shared<NonVisitable>();
		pAdapter = std::make_shared<Adapter>(nonVisitable);
	}

	using Visitor = VTM::MockVisitor<AR::Repository, AR::E1, NonVisitable>;
	Visitor visitor;

	ASSERTM("DefaultPolicy logInvalidVisitable not initialized", !VTM::MockLoggingPolicy::invalidVisitable);

	pAdapter->accept(visitor);

	ASSERTM("DefaultPolicy logInvalidVisitable not called", VTM::MockLoggingPolicy::invalidVisitable);
}
inline
void AdapterTest::acyclicAdapterWeakpointerStayValid(){
	using Adapter = AR::Repository::AdapterByWeakpointer<NonVisitable>;
	auto nonVisitable = std::make_shared<NonVisitable>();

	std::weak_ptr<NonVisitable> pWeak(nonVisitable);

	auto pAdapter = std::make_shared<Adapter>(pWeak);;
	auto p = pWeak.lock();

	ASSERTM("Weak_ptr not copied", p != nullptr );
}
#endif /* INCLUDE_ADAPTERTEST_H_ */
