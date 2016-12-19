/*
 * DemoMyAcyclicRepository.cpp
 *
 *  Created on: 04.12.2016
 *      Author: Gerd
 */

#include "AcyclicVisitables.h"
#include "NonVisitable.h"
#include "NonVisitableWithAccessor.h"

#include "AcyclicVisitors.h"
#include "AcyclicRepository.h"
#include "DemoRunVisitor.h"

#include <iostream>
#include <memory>
#include <vector>

namespace AcyclicRepository{

using Visitable = Repository::Visitable;
using Visitor = Repository::Visitor;

using SharedPointer = std::shared_ptr<Visitable>;
using Visitables = std::vector<SharedPointer>;

template<class Adaptee>
using AdapterReference = Repository::AdapterByReference<Adaptee>;
template<class Adaptee>
using AdapterWeak = Repository::AdapterByWeakpointer<Adaptee>;
}

using namespace AcyclicRepository;
using namespace std;

void demoAcyclicRepository(){
	cout << "================================" << endl;
	std::cout << "==== demoAcyclicRepository() ====" << std::endl;
	Visitables visitables;

	DemoVisitor13 visitor13;
	DemoVisitor23 visitor23;
	NonVisitableWithAccessor nvwa;
	auto pNV = std::make_shared<NonVisitable>();

	{
		auto p = std::make_shared<NonVisitable>();
		visitables.push_back(SharedPointer(new AdapterWeak<NonVisitable>(p)));
	}

	visitables.push_back(SharedPointer(new E1));
	visitables.push_back(SharedPointer(new E2));
	visitables.push_back(SharedPointer(new E3));
	visitables.push_back(SharedPointer(new AdapterWeak<NonVisitable>(pNV)));
	visitables.push_back(SharedPointer(new AdapterReference<NonVisitableWithAccessor>(nvwa)));

	demoRunVisitor(visitor13, visitables);
//	demoRunVisitor(visitor23, visitables);


	std::cout << "==== end demoAcyclicRepository() ====" << std::endl;
}
