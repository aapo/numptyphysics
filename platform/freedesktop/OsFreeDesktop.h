/*
 * This file is part of NumptyPhysics <http://thp.io/2015/numptyphysics/>
 * Coyright (c) 2008, 2009 Tim Edmonds <numptyphysics@gmail.com>
 * Coyright (c) 2012, 2014, 2015 Thomas Perl <m@thp.io>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 */


#include "Os.h"
#include <cstdlib>
#include <sstream>
#include <string>


class GLibString {
public:
    GLibString(char *value) : value(value) {}
    ~GLibString() { free(value); }

    operator std::string() { return value; }

private:
    char *value;
};


class OsFreeDesktop : public Os {
public:
    OsFreeDesktop()
        : Os()
    {
    }

    virtual bool openBrowser(const char *url)
    {
        return 0;
    }

    virtual std::string userDataDir()
    {
        const char* homedir;
        if ((homedir = getenv("HOME")) == NULL)
        {
            homedir = "/tmp";
        }

        std::stringstream ss;
        ss << homedir << "/.config/" << appName();
        std::string dir = ss.str();

        return dir;
    }
};
