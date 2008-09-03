
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


#ifndef PRESAGE_SELECTOR
#define PRESAGE_SELECTOR

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "core/suggestion.h"
#include "core/prediction.h"
#include "core/contextTracker.h"
#include "core/predictor.h"
#include "core/logger.h"

#include <string>
#include <vector>
#include <set>
#include <stdlib.h> // needed for abort()


typedef	std::set< std::string, std::less<std::string> > StringSet;


/** Selector selects which suggestions supplied by Predictor should be given to the user.
 *
 * Suggestions selection is performed based on users
 * preferences. Preferences are read from configuration and provided
 * by Configuration.
 * 
 * Selected suggestions are returned to the outside world.
 *
 * Customisable settings:
 * 
 * SUGGESTIONS: integer, number of suggestions to be selected
 *
 * REPEAT_SUGGESTIONS: boolean, controls whether a predicted token
 * should be suggested to the user once or multiple times, if its
 * prediction occurs within the same predictive context. A predictive
 * context corresponds to the set of suggestions computed when
 * predicting the same word (token). Some users may fail to see the
 * desired suggestion and might benefit from the fact that the same
 * token will be suggested again if it ranks high in the
 * prediction. If this option is enabled, Selector remembers which
 * tokens have been suggested in the current token and filters out
 * suggestions that have already been selected.
 *
 * GREEDY_SUGGESTION_THRESHOLD: integer, only tokens whose completion
 * is longer than the specified number of characters are selected. The
 * rationale behind this option is that a user might prefer to be
 * offered a longer word before a shorter word, because typing a
 * longer word is more time-consuming.
 * 
 * For example, given a threshold=2 and prefix="automa", token
 * "automatically" would be suggested, while "automatic" would not.
 *
 */
class Selector {
public:
    Selector(Configuration*, ContextTracker*);
    ~Selector();

    std::vector<std::string> select(Prediction);

    void update();

    int suggestions() const;
    bool repeat_suggestions() const;
    unsigned int greedy_suggestion_threshold() const;

    static const Variable SUGGESTIONS;
    static const Variable REPEAT_SUGGESTIONS;
    static const Variable GREEDY_SUGGESTION_THRESHOLD;

private:

    void updateSuggestedWords( const std::vector<std::string>& );
    void clearSuggestedWords();

    void repetitionFilter( std::vector<std::string>& );
    void thresholdFilter( std::vector<std::string>& );

    StringSet suggestedWords;

    std::string previous_prefix;

    ContextTracker* contextTracker;
    Configuration*  config;
    Logger<char> logger;
};


#endif // PRESAGE_SELECTOR
