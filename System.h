/*
 * System.h
 *
 *  Created on: 26-May-2010
 *      Author: shirish
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "headers.h"

using namespace std;
/**
 * Functions for obtaining system actions like files in a  directory etc
 */
class System {
public:
    System();
    virtual ~System();
    list<string> file_names(char dir[]);

private:

};

#endif /* SYSTEM_H_ */
