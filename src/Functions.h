//
// Created by macbook on 2020-03-07.
//

#ifndef HOME_CTRL_FUCTIONS_H
#define HOME_CTRL_FUCTIONS_H

#include "Menu.h"
#include <ser_res.h>
#include <run_prog.h>
#include <EEPROM.h>


class Functions : public Menu, public SerRes, virtual public RunProg
{

public:
    explicit Functions();
    ~Functions();

protected:
   
    virtual void setupFunc();
    void loadParam();
    void saveParam() override;
    void exec();
    void sendParam();
    void exe_0(int) override;
    void exe_1(int) override;
    void exe_2(int) override;
    void exe_3(int) override;

    void exe_6(int) override;
    void exe_7(int) override;
    void exe_8(int) override;
    void exe_9(int) override;
    void exe_10(int) override;
    void exe_11(int) override;
    void exe_12(int) override;
    void exe_13(int) override;

    void eGet();
    void ePut();
    void eDef();

private:
    int *pSerResArr;
};

#endif //HOME_CTRL_FUCTIONS_H
