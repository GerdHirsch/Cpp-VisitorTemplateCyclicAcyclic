/*
 * SwitchCyclicAcyclicRepository.h
 *
 *  Created on: 05.12.2016
 *      Author: Gerd
 */

#ifndef SWITCHCYCLICACYCLICREPOSITORY_H_
#define SWITCHCYCLICACYCLICREPOSITORY_H_

#include <Visitor/DefaultLoggingPolicy.h>
#include <visitor/Typelist.h>
#include <visitor/BaseKind.h>
#include <Visitor/Cyclic/Repository.h>
#include <Visitor/Acyclic/Repository.h>

class NonVisitable;

namespace CyclicAcyclicRepository{
class E1;
class E2;
class E3;


using typelist =
		VisitorFramework::Typelist
		<
		E1, E2, E3,
		NonVisitable
		>;

namespace CAR = VisitorFramework::Cyclic;
//namespace CAR = VisitorFramework::Acyclic;

using Repository = CAR::Repository
		<
//		VisitorFramework::EmptyLoggingPolicy,
		VisitorFramework::DemoLoggingPolicy,
//		BaseKind::Abstract,
		BaseKind::Default,
		typelist
		>;
}
#endif /* SWITCHCYCLICACYCLICREPOSITORY_H_ */
