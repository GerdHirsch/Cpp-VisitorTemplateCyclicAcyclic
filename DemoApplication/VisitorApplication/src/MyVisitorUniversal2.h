/*
 * MyVisitorUniversal2.h
 *
 *  Created on: 12.11.2016
 *      Author: Gerd
 */

#ifndef MYVISITORUNIVERSAL2_H_
#define MYVISITORUNIVERSAL2_H_


#include "Element_1.h"
#include "Element_2.h"
#include "Element_3.h"
#include "NonVisitableWithAccessor.h"
#include "MyVisitorCyclicAcyclic.h"

namespace DemoSwitchCyclicAcyclic{

struct VisitorUniversal2 : public Repository::MyVisitorBase {

	void visit(Element_1 &d) override {
		std::cout << toString() << "::visit: " << d.toString() << std::endl;
	}
	void visit(Element_2 &d) override {
		std::cout << toString() << "::visit: " << d.toString() << std::endl;
	}
	void visit(Element_3 &d) //override
	{
		std::cout << toString() << "::visit: " << d.toString() << std::endl;
	}
	void visit(NonVisitable &d) override {
		std::cout << toString() << "::visit: " << d.toString() << std::endl;
	}
	void visit(NonVisitableWithAccessor &d) override {
		// Accessor is only for Acyclic Visitors
//		this->setData(d, "VisitorUniversal 2 Data");
		std::cout << toString() << "::visit: " << d.toString() << std::endl;
	}
	std::string toString() const override {
		return "VisitorUniversal2";
	}
};

}

#endif /* MYVISITORUNIVERSAL2_H_ */
