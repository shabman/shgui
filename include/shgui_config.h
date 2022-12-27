/*
 * ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
 * 
 * Copyright (C) 2022 Mustafa Malik (@shabman)
 * 
 * 	This software is provided 'as-is', without any express or implied
 * 	warranty. In no event will the authors be held liable for any damages
 *  arising from the use of this software.
 * 
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute it
 *  freely, subject to the following restrictions:
 * 
 * 	1. 	The origin of this software must not be misrepresented; you must not
 *   	claim that you wrote the original software. If you use this software
 *   	in a product, an acknowledgment in the product documentation would be
 *   	appreciated but is not required.
 *  2. 	Altered source versions must be plainly marked as such, and must not be
 *   	misrepresented as being the original software.
 * 	3. This notice may not be removed or altered from any source distribution.
 * 
 * 	 Email Mustafa Malik:	avia.shabbyman@gmail.com 
 * 
 * ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
*/

#ifndef SHGUI_INCLUDE_CONFIG_H
#define SHGUI_INCLUDE_CONFIG_H

#define SHGUI_VERSION "0.1"

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <functional>

#include <dirent.h>
#include <limits.h>

#define SHGUI_NAME
#define __SHGUI_MULTI_VA_ARGS(_1, ...) SHGUI_NAME

/*
#define SHGUI_NOEXCEPT(...) noexcept( \
	__SHGUI_MULTI_VA_ARGS(__VA_ARGS__, SHGUI_NOEXCEPT_1)(__VA_ARGS__) \
)
* */

#define SHGUI_NOEXCEPT 	noexcept
#define SHGUI_STATIC	static
#define SHGUI_EXPORT	extern
#define SHGUI_VOID		[[noreturn]] void
#define SHGUI_NOEDIT	const

// Core

#include <raylib.h>
#include "../lib/rcpp426/include/raylib-cpp.hpp"

#define DEFAULT_WIDTH 	900
#define DEFAULT_HEIGHT 	500

typedef Vector2 Dimension;

class __shgui_internals {
protected:
	SHGUI_STATIC std::vector<std::function<void()>*> __shgui_private_functions;
	// --
	SHGUI_STATIC SHGUI_VOID __add_func(const std::function<void()>* __f) SHGUI_NOEXCEPT {
		__shgui_private_functions.push_back(__f);
	}
public:
	SHGUI_STATIC SHGUI_NOEDIT bool __is_private(const std::function<void()>* __f) SHGUI_NOEXCEPT {
		bool expected = false;
		for (int i = 0; i < __shgui_private_functions.size(); i++) {
			if (__shgui_private_functions[i] == __f) {
				expected = true;
				break;
			}
		}
		return expected;
	}
};

template<typename T>
class shgui_base {
public:
	shgui_base() { }
	virtual ~shgui_base();
public:
	virtual SHGUI_VOID on_event(const std::string&, const T*) SHGUI_NOEXCEPT;
 };

struct shgui_color {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

struct shgui_image {
	const char* fp;
};

struct shgui_text_field_cache {
	std::vector<std::string> o_text;
	std::vector<std::string> n_text;
	
	unsigned int undo_key;
	unsigned int redo_key;
};

struct shgui_top_bar_menu {
	std::vector<std::map<std::string, std::function<void()>>> menu;
};

struct shgui_context_menu : public shgui_top_bar_menu {
	Dimension mouse_pos;
};

#define DEFAULT_RENDER_COLOUR BLACK

Color shgui_make_rgb_col(const struct shgui_color& scf) {
	return Color {scf.r, scf.g, scf.b, scf.a};
}

// Caller sensitive
SHGUI_VOID __shgui_setup() {
	__shgui_internals::__add_func(&__shgui_setup);
}

#endif /* SHGUI_INCLUDE_CONFIG_H */
