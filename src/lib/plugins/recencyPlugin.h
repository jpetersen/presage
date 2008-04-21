
/*********************************************************
 *  Soothsayer, an extensible predictive text entry system
 *  ------------------------------------------------------
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

#ifndef SOOTH_RECENCYPLUGIN
#define SOOTH_RECENCYPLUGIN

#include "plugins/plugin.h"
#include "core/utility.h"    // strtolower
#include "core/logger.h"

#include <assert.h>

/** Recency statistical plugin.
 *
 * (from Wikipedia) A quantity is said to be subject to exponential
 * decay if it decreases at a rate proportional to its
 * value. Symbolically, this can be expressed as the following
 * differential equation, where N is the quantity and λ is a positive
 * number called the decay constant.
 *
 *  \frac{dN}{dt} = -\lambda N.
 *
 * The solution to this equation is below:
 *
 *  N(t) = N_0 e^{-\lambda t}. \,
 *
 * Here N(t) is the quantity at time t, and N0 = N(0) is the (initial)
 * quantity, at time t = 0.
 *
 * This is the form of the equation that is most commonly used to
 * describe exponential decay. The constant of integration N0 denotes
 * the original quantity at t = 0. (The notation λ for the decay
 * constant is a remnant of the usual notation for an eigenvalue. In
 * this case, λ is the eigenvalue of the opposite of the
 * differentiation operator with N(t) as the corresponding
 * eigenfunction).
 *
 */
class RecencyPlugin : public Plugin {
public:
    RecencyPlugin(Configuration*, ContextTracker*);
    ~RecencyPlugin();

    virtual Prediction predict(const size_t) const;

    virtual void learn();
    virtual void extract();
    virtual void train();

private:

    double lambda;
    double n_0;
    int cutoff_threshold;

};

#endif // SOOTH_RECENCYPLUGIN
