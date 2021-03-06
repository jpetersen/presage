
/******************************************************
 *  Presage, an extensible predictive text entry system
 *  ---------------------------------------------------
 *
 *  Copyright (C) 2008  Matteo Vescovi <matteo.vescovi@yahoo.co.uk>
 *  Copyright (C) 2018  rinigus <rinigus.git@gmail.com>

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


#include "presage.h"

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifdef HAVE_STDLIB_H
# include <stdlib.h>
#endif

#include <getopt.h>

#include <iostream>
#include <sstream>

const char PROGRAM_NAME[] = "presage_demo_forget";

void disclaimer ();
void parse_cmd_line_args (int argc, char** argv);
void print_version ();
void print_usage ();
void print_prediction (const std::vector<std::string>&);

std::string config;
std::string word;

int main(int argc, char** argv)
{
    parse_cmd_line_args (argc, argv);
    disclaimer ();

    // magic starts here...
    LegacyPresageCallback callback;
    Presage presage (&callback, config);

    if (word.empty()) {
      std::cerr << "Word to forget is not specified\n";
      return -1;
    }

    presage.forget(word);

    std::cout << "Word " << word << " forgotten\n";
    return 0;
}


void disclaimer ()
{
    std::cout <<
        "Presage Forget Demo\n"
        "--------------------\n"
        "\n"
        "This program is intended as a demonstration of Presage ONLY.\n"
        "\n"
        "The Presage project aims to provide an intelligent predictive text entry platform.\n"
        "\n"
        "Its intent is NOT to provide a predictive text entry user interface.\n"
        "Think of Presage as the predictive backend that sits behind a shiny user interface and does all the predictive heavy lifting.\n"
        "\n" << std::endl;
}

void parse_cmd_line_args (int argc, char* argv[])
{
    int next_option;

    // getopt structures
    const char* const short_options = "c:w:hv";

    const struct option long_options[] = {
	{ "config",       required_argument, 0, 'c' },
	{ "word",         required_argument, 0, 'w' },
	{ "help",         no_argument,       0, 'h' },
	{ "version",      no_argument,       0, 'v' },
	{ 0, 0, 0, 0 }
    };

    do {
        next_option = getopt_long( argc, argv, 
                                   short_options, long_options, NULL );

        switch( next_option ) {
	case 'c': // --config or -c option
            config = optarg;
            break;
	case 'w': // --word or -w option
            word = optarg;
	    break;
	case 'h': // --help or -h option
	    print_usage ();
	    exit (0);
	    break;
	case 'v': // --version or -v option
	    print_version ();
	    exit (0);
	    break;
	case '?': // unknown option
	    print_usage();
	    exit (0);
	    break;
	case -1:
	    break;
	default:
	    abort ();
	    break;
	}

    } while (next_option != -1);
}

void print_version ()
{
    std::cout << PROGRAM_NAME << " (" << PACKAGE << ") version " << VERSION << std::endl
              << "Copyright (C) 2004 Matteo Vescovi." << std::endl
              << "This is free software; see the source for copying conditions.  There is NO" << std::endl
              << "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE," << std::endl
              << "to the extent permitted by law." << std::endl;
}

void print_usage ()
{
    std::cout << "Usage: " << PROGRAM_NAME << " [OPTION]..." << std::endl
              << std::endl
              << "At the prompt, type in some text. Hit enter to generate a prediction." << std::endl
              << "Any text input is valid, including no text, a single character, or a long string." << std::endl
              << std::endl
              << "  -c, --config CONFIG  use config file CONFIG" << std::endl
              << "  -w, --word W         word to forget" << std::endl
              << "  -h, --help           display this help and exit" << std::endl
              << "  -v, --version        output version information and exit" << std::endl
              << std::endl
              << "Direct your bug reports to: " << PACKAGE_BUGREPORT << std::endl;
}
