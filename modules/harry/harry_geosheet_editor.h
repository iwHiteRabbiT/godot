/*************************************************************************/
/*  harry_geosheet_editor.h                                              */
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

#ifndef HARRY_GEOSHEET_EDITOR_H
#define HARRY_GEOSHEET_EDITOR_H

//#include "editor/editor_node.h"
//#include "harry.h"
//#include "harry_subnet_graph_node.h"
//#include "harry_wrangle.h"
#include "scene/gui/graph_edit.h"
#include "scene/gui/tree.h"
#include "scene/gui/grid_container.h"
#include "scene/gui/button.h"
#include "harry_node.h"
//#include "editor/editor_plugin.h"
//#include "editor/pane_drag.h"

/**
 @Author iWhiteRabbiT
*/
class HarryGeoSheetEditor : public VBoxContainer {
	GDCLASS(HarryGeoSheetEditor, VBoxContainer);

	Tree *tree;
	Ref<HarryNode> current_node;

	HarryNode::AttribClass current_attrib_class;

protected:
	static void _bind_methods();

public:
	HarryGeoSheetEditor();
	//void edit();

	void refresh();
	void refresh(Ref<HarryNode> &p_node);
	void refresh_attrib(int index);
};

#endif
