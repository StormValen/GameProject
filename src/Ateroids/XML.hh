#pragma once
#include "ID.hh"
#include <fstream>
#include <sstream>
#include <iterator>
#include "Logger.hh"
#include "Assert.hh"
#include "Resource.hh"
#include <XML/rapidxml_utils.hpp>
#include "LevelScene.hh"
using namespace Logger;

void Xml(std::string filename) {

	rapidxml::xml_document<> doc;
	std::ifstream file(filename);
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	std::cout << "ROOT: " << doc.first_node()->name() << "\n";
	rapidxml::xml_node<> *pRoot = doc.first_node();

	int atr_counter = 0;
	for (rapidxml::xml_node<> *pRit = pRoot->first_node(); atr_counter < 4; atr_counter++ ) {
		std::cout<< "	CHILD: " << pRit->name() << " -> VALUE: " << pRit->value() << "\n";
		LevelScene::param.push_back(atoi(pRit->value()));
		pRit = pRit->next_sibling();
	}

	
}