
/******************************************************
 *  Presage, an extensible predictive text entry system
 *  ---------------------------------------------------
 *
 *  Copyright (C) 2008  Matteo Vescovi <matteo.vescovi@yahoo.co.uk>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
                                                                             *
                                                                **********(*)*/


#ifndef PRESAGE_DUMMYPLUGIN
#define PRESAGE_DUMMYPLUGIN

#include "plugins/plugin.h"


/** Dummy plugin is provided here to show how to implement real plugins.
 *
 */
class DummyPlugin : public Plugin {
public:
    DummyPlugin(Configuration*, ContextTracker*);
    ~DummyPlugin();

    virtual Prediction predict(const size_t size, const char** filter) const;

    virtual void learn();
    virtual void extract();
    virtual void train();

private:
	
};

#endif // PRESAGE_DUMMYPLUGIN
