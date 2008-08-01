
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


#ifndef PRESAGE_PLUGINREGISTRY
#define PRESAGE_PLUGINREGISTRY


#include "plugins/plugin.h"

class ContextTracker;

/** PluginRegistry manages Plugin objects.
 *
 */
class PluginRegistry {
  public:
    PluginRegistry(Configuration* config);
    ~PluginRegistry();

    class Iterator {
    public:
	Iterator(std::vector<Plugin*>&);
	~Iterator();

	bool hasNext() const;
	Plugin* next();
	
    private:
	std::vector<Plugin*>::iterator iter_end;
	std::vector<Plugin*>::iterator iter_curr;

    };

    Iterator iterator();
    void setContextTracker(ContextTracker* ct);

  private:
    void setPlugins(const std::string& plugin_list);
    void addPlugin(const std::string& plugin_name);
    void removePlugins();

    Configuration*  config;
    ContextTracker* contextTracker;
    Logger<char>    logger;

    std::string          plugins_list;
    std::vector<Plugin*> plugins;        // active Plugins

    static const Variable LOGGER;
    static const Variable PLUGINS;
};

#endif // PRESAGE_PLUGINREGISTRY
