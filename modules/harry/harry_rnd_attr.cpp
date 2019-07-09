/*************************************************************************/
/*  harry_basic_primitive.cpp                                            */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2019 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2019 Godot Engine contributors (cf. AUTHORS.md)    */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "harry_rnd_attr.h"

/**
  @Author iWhiteRabbiT
*/

void HarryRndAttr::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_attribute_class", "attr_class"), &HarryRndAttr::set_attribute_class);
	ClassDB::bind_method(D_METHOD("get_attribute_class"), &HarryRndAttr::get_attribute_class);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "attribute_class", PROPERTY_HINT_ENUM, ATTRIBCLASSES), "set_attribute_class", "get_attribute_class");

	ClassDB::bind_method(D_METHOD("set_attr_name", "attr_name"), &HarryRndAttr::set_attr_name);
	ClassDB::bind_method(D_METHOD("get_attr_name"), &HarryRndAttr::get_attr_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "attr_name"), "set_attr_name", "get_attr_name");

	ClassDB::bind_method(D_METHOD("set_operation", "operation"), &HarryRndAttr::set_operation);
	ClassDB::bind_method(D_METHOD("get_operation"), &HarryRndAttr::get_operation);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "operation", PROPERTY_HINT_ENUM, OPERATIONS), "set_operation", "get_operation");

	ClassDB::bind_method(D_METHOD("set_dimension", "dimension"), &HarryRndAttr::set_dimension);
	ClassDB::bind_method(D_METHOD("get_dimension"), &HarryRndAttr::get_dimension);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "dimension"), "set_dimension", "get_dimension");

	ClassDB::bind_method(D_METHOD("set_min_val", "min_val"), &HarryRndAttr::set_min_val);
	ClassDB::bind_method(D_METHOD("get_min_val"), &HarryRndAttr::get_min_val);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "min_val"), "set_min_val", "get_min_val");

	ClassDB::bind_method(D_METHOD("set_max_val", "max_val"), &HarryRndAttr::set_max_val);
	ClassDB::bind_method(D_METHOD("get_max_val"), &HarryRndAttr::get_max_val);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "max_val"), "set_max_val", "get_max_val");

	BIND_CONSTANT(SET);
	BIND_CONSTANT(ADD);
	// BIND_CONSTANT(MIN);
	// BIND_CONSTANT(MAX);
	BIND_CONSTANT(MUL);
}


void HarryRndAttr::set_attribute_class(AttribClass attr_class) {

	this->attr_class = attr_class;
	dirty();
}

HarryNode::AttribClass HarryRndAttr::get_attribute_class() {

	return attr_class;
}

void HarryRndAttr::set_attr_name(StringName attr_name) {

	this->attr_name = attr_name;
	dirty();
}
StringName HarryRndAttr::get_attr_name() {

	return attr_name;
}

void HarryRndAttr::set_operation(Operation operation) {

	this->operation = operation;
	dirty();
}

HarryRndAttr::Operation HarryRndAttr::get_operation() {

	return operation;
}

void HarryRndAttr::set_dimension(int dimension) {

	this->dimension = dimension;
	dirty();
}
int HarryRndAttr::get_dimension() {

	return dimension;
}

void HarryRndAttr::set_min_val(Vector3 min_val) {

	this->min_val = min_val;
	dirty();
}
Vector3 HarryRndAttr::get_min_val() {

	return min_val;
}

void HarryRndAttr::set_max_val(Vector3 max_val) {

	this->max_val = max_val;
	dirty();
}
Vector3 HarryRndAttr::get_max_val() {

	return max_val;
}

void HarryRndAttr::create_geo(Vector<CacheCount> &p_input_caches, bool bypass) {

	if (p_input_caches.size()>0)
		copy_from_cache(p_input_caches[0]);

	if (bypass)
		return;

	if(dimension == 1)
		RandomizeAttr(this, attr_class, attr_name, operation, 0, min_val.x, max_val.x);

	if(dimension == 2)
		RandomizeAttr(this, attr_class, attr_name, operation, Vector2(), min_val.x, max_val.x);

	if(dimension == 3)
		RandomizeAttr(this, attr_class, attr_name, operation, Vector3(), min_val.x, max_val.x);
}

void HarryRndAttr::RandomizeAttr(HarryNode *p_node, AttribClass p_attr_class, StringName p_attr, Operation operation, Variant p_default, float min, float max) {

	int c = p_node->get_attrib_class_count(p_attr_class);

	if (c == 0)
		return;

	Variant::Type type = p_default.get_type();

	if (type == Variant::VECTOR3) {

		for (int i = 0; i < c; i++) {

			Vector3 &v = Vector3(
					Math::random(min, max),
					Math::random(min, max),
					Math::random(min, max));

			Variant current = p_node->get_attrib(p_attr_class, p_attr, i);
			Variant val = VariantOperation(current, v, operation);
			p_node->set_attrib(p_attr_class, p_attr, i, val, p_default);
		}

		return;
	}

	if (type == Variant::VECTOR2) {

		for (int i = 0; i < c; i++) {

			Vector2 &v = Vector2(
					Math::random(min, max),
					Math::random(min, max));

			Variant current = p_node->get_attrib(p_attr_class, p_attr, i);
			Variant val = VariantOperation(current, v, operation);
			p_node->set_attrib(p_attr_class, p_attr, i, v, p_default);
		}

		return;
	}

	if (type == Variant::COLOR) {

		for (int i = 0; i < c; i++) {

			Color &v = Color(
					Math::random(min, max),
					Math::random(min, max),
					Math::random(min, max));

			Variant current = p_node->get_attrib(p_attr_class, p_attr, i);
			Variant val = VariantOperation(current, v, operation);
			p_node->set_attrib(p_attr_class, p_attr, i, v, p_default);
		}

		return;
	}

	if (type == Variant::REAL) {

		for (int i = 0; i < c; i++) {

			float v = Math::random(min, max);
			Variant current = p_node->get_attrib(p_attr_class, p_attr, i);
			Variant val = VariantOperation(current, v, operation);
			p_node->set_attrib(p_attr_class, p_attr, i, val, p_default);
		}

		return;
	}

	if (type == Variant::INT) {

		for (int i = 0; i < c; i++) {

			int v = Math::fast_ftoi(Math::random(min, max));
			Variant current = p_node->get_attrib(p_attr_class, p_attr, i);
			Variant val = VariantOperation(current, v, operation);
			p_node->set_attrib(p_attr_class, p_attr, i, val, p_default);
		}

		return;
	}
}

Variant HarryRndAttr::VariantOperation(Variant current, Variant new_val, Operation operation) {

	switch (operation)
	{
	case SET:
		return new_val;

	case ADD:
		return Variant::evaluate(Variant::OP_ADD, current, new_val);
	
	// case MIN:
	// case MAX:
	
	case MUL:
		return Variant::evaluate(Variant::OP_MULTIPLY, current, new_val);
	
	default:
		return current;
	}
}
