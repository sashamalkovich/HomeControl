#ifndef _SER_RES_H_
#define _SER_RES_H_

#include <Arduino.h>
#include "def.h"


class SerRes {

public:

    explicit SerRes();

    ~SerRes();

  virtual int *response();

    char *response(char &);

    static bool equals(const char *, const char *);
protected:


private:
    char *pInputString;

    char input;
    char symbol;

    char *ser_res(char *, char &);

    int responseCommand(char **, char *);

    int *respResult(char **, int *intArr);

    char **array;
    int *intArray;

    long timer;


};

#endif //_SER_RES_H_
