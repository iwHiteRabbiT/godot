/*************************************************************************/
/*  harry_editor_plugin.cpp                                              */
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

#include "harry_editor_plugin.h"

/**
 * @Author iWhiteRabbiT
*/

HarryEditorPlugin::HarryEditorPlugin(EditorNode *p_editor) {

	editor = p_editor;
	harry_editor = memnew(HarryEditor);
	harry_editor->set_custom_minimum_size(Size2(0, 300));

	button = editor->add_bottom_panel_item(TTR("Harry"), harry_editor);
	button->hide();
}

HarryEditorPlugin::~HarryEditorPlugin() {
}

void HarryEditorPlugin::make_visible(bool isVisible) {

	if (isVisible) {
		button->show();
		editor->make_bottom_panel_item_visible(harry_editor);
		harry_editor->set_process(true);
		//harry_editor->show();
	} else {
		if (harry_editor->is_visible_in_tree())
			editor->hide_bottom_panel();
		button->hide();
		harry_editor->set_process(false);
		//harry_editor->hide();
	}
}

void HarryEditorPlugin::edit(Object *p_object) {

	harry_editor->edit(Object::cast_to<Harry>(p_object));
}

bool HarryEditorPlugin::handles(Object *p_object) const {

	return p_object->is_class("Harry");
}
