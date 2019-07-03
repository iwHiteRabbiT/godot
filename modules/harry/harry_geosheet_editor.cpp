/*************************************************************************/
/*  harry_geosheet_editor.cpp                                            */
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

#include "harry_geosheet_editor.h"

void HarryGeoSheetEditor::_bind_methods() {
	ClassDB::bind_method("refresh_attrib", &HarryGeoSheetEditor::refresh_attrib);
}

HarryGeoSheetEditor::HarryGeoSheetEditor() {

	set_name("Harry GeoSheet");

	GridContainer *grid = memnew(GridContainer);
	add_child(grid);
	grid->set_columns(4);

	Ref<ButtonGroup> group;
	group.instance();

	Button *btn;
	btn = memnew(Button);
	grid->add_child(btn);
	btn->set_text("Point");
	btn->set_button_group(group);
	btn->connect("pressed", this, "refresh_attrib", varray(0));

	btn = memnew(Button);
	grid->add_child(btn);
	btn->set_text("Vertex");
	btn->set_button_group(group);
	btn->connect("pressed", this, "refresh_attrib", varray(1));

	btn = memnew(Button);
	grid->add_child(btn);
	btn->set_text("Primitive");
	btn->set_button_group(group);
	btn->connect("pressed", this, "refresh_attrib", varray(2));

	btn = memnew(Button);
	grid->add_child(btn);
	btn->set_text("Detail");
	btn->set_button_group(group);
	btn->connect("pressed", this, "refresh_attrib", varray(3));

	tree = memnew(Tree);
	add_child(tree);
	tree->set_hide_root(true);
	tree->set_select_mode(Tree::SELECT_ROW);
	tree->set_allow_reselect(true);
	tree->set_drag_forwarding(this);
	tree->set_v_size_flags(SIZE_EXPAND_FILL);
	tree->set_column_titles_visible(true);

	//tree->set_columns(3);
	//tree->set_column_title(0, TTR("P"));
	//tree->set_column_title(1, TTR("N"));
	//tree->set_column_title(2, TTR("V"));
	//tree->set_column_title(2, TTR("A"));

	//for (int i = 0; i < 3; i++) {
	//	tree->set_column_expand(i, false);
	//	tree->set_column_min_width(i, 100);
	//}
	//tree->connect("cell_selected", this, "_autoload_selected");
	//tree->connect("item_edited", this, "_autoload_edited");
	//tree->connect("button_pressed", this, "_autoload_button_pressed");
	//tree->connect("item_activated", this, "_autoload_activated");

	//tree->clear();
	//TreeItem *root = tree->create_item();

	//for (int i = 0; i < 100; i++) {

	//	TreeItem *item = tree->create_item(root);

	//	for (int j = 0; j < 4; j++) {
	//		item->set_text(j, "+" + itos(i * j));
	//		item->set_editable(j, false);
	//		item->set_selectable(j, true);
	//	}
	//}
}

void HarryGeoSheetEditor::refresh() {

	if (!current_node.is_valid())
		return;

	tree->clear();
	TreeItem *root = tree->create_item();

	ATTRMAP att = current_node->get_attrib_class(current_attrib_class);

	List<StringName> att_names;
	att_names.push_back("");

	for (ATTRMAP::Element *a = att.front(); a; a = a->next()) {

		HarryNode::DefaultVectorVariant dvv = a->get();
		Variant::Type type = dvv.default.get_type();

		if (type == Variant::VECTOR3) {

			att_names.push_back(((String)a->key()) + "[x]");
			att_names.push_back(((String)a->key()) + "[y]");
			att_names.push_back(((String)a->key()) + "[z]");
		}
		else if (type == Variant::VECTOR2) {

			att_names.push_back(((String)a->key()) + "[x]");
			att_names.push_back(((String)a->key()) + "[y]");
		}
		else if (type == Variant::COLOR) {

			att_names.push_back(((String)a->key()) + "[r]");
			att_names.push_back(((String)a->key()) + "[g]");
			att_names.push_back(((String)a->key()) + "[b]");
		}
		else
			att_names.push_back(a->key());
	}

	tree->set_columns(att_names.size());

	for (int i = 0; i < att_names.size(); i++) {
		tree->set_column_title(i, att_names[i]);
		tree->set_column_expand(i, false);
		tree->set_column_min_width(i, 100);
	}

	if (!att.front())
		return;

	int nb_rows = current_node->get_attrib_class_count(current_attrib_class); //att.front()->get().values.size();

	for (int i = 0; i < nb_rows; i++) {
		TreeItem *item = tree->create_item(root);

		int j = 0;

		item->set_editable(j, false);
		item->set_selectable(j, true);
		item->set_text(j++, itos(i));

		for (ATTRMAP::Element *a = att.front(); a; a = a->next()) {

			int j0 = j;

			HarryNode::DefaultVectorVariant dvv = a->get();
			Variant::Type type = dvv.default.get_type();

			if (type == Variant::VECTOR3) {

				const Vector3 &v = a->get().values[i];
				item->set_text(j++, rtos(v.x));
				item->set_text(j++, rtos(v.y));
				item->set_text(j++, rtos(v.z));
			}
			else if (type == Variant::VECTOR2) {

				const Vector2 &v = a->get().values[i];
				item->set_text(j++, rtos(v.x));
				item->set_text(j++, rtos(v.y));
			}
			if (type == Variant::COLOR) {

				const Color &c = a->get().values[i];
				item->set_text(j++, rtos(c.r));
				item->set_text(j++, rtos(c.g));
				item->set_text(j++, rtos(c.b));
			}
			else
				item->set_text(j++, a->get().values[i]);


			for (int jx = j0; jx < j; jx++)
			{
				item->set_editable(jx, false);
				item->set_selectable(jx, true);
			}
		}
	}
}

void HarryGeoSheetEditor::refresh(Ref<HarryNode> &node) {

	current_node = node;

	refresh();
}

void HarryGeoSheetEditor::refresh_attrib(int index) {

	HarryNode::AttribClass new_attrib_class;
	switch (index) {
		case 0: new_attrib_class = HarryNode::AttribClass::POINT; break;
		case 1: new_attrib_class = HarryNode::AttribClass::VERTEX; break;
		case 2: new_attrib_class = HarryNode::AttribClass::PRIMITIVE; break;
		case 3: new_attrib_class = HarryNode::AttribClass::DETAIL; break;
	}

	if (current_attrib_class == new_attrib_class)
		return;

	current_attrib_class = new_attrib_class;

	refresh();
}
