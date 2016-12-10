/*
 * AcyclicRepository.h
 *
 *  Created on: 05.12.2016
 *      Author: Gerd
 */

#ifndef ACYCLICREPOSITORY_H_
#define ACYCLICREPOSITORY_H_


#include <Visitor/DefaultLoggingPolicy.h>
#include <visitor/Typelist.h>
#include <visitor/BaseKind.h>
#include <Visitor/Acyclic/Repository.h>

class NonVisitable;
class NonVisitableWithAccessor;

namespace AcyclicRepository{
class E1;
class E2;
class E3;

namespace VF = VisitorFramework;

using typelist =
		VisitorFramework::Typelist
		<
		E1, E2, E3,
		NonVisitableWithAccessor
		>;

using Repository = VF::Acyclic::Repository
		<
//		VF::EmptyLoggingPolicy,
		VF::DemoLoggingPolicy,
		BaseKind::Abstract,
//		BaseKind::Default,
		typelist
		>;
}




#endif /* ACYCLICREPOSITORY_H_ */
