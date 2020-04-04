#ifndef _RUN_PROG_H_
#define _RUN_PROG_H_


class RunProg {

public:
    explicit RunProg();

    ~RunProg();


    void exec(int*);


protected:
    typedef void (RunProg::*pfn_MyFuncType)(int);

    pfn_MyFuncType *arr;

    virtual void exe_0(int);

    virtual void exe_1(int);

    virtual void exe_2(int);

    virtual void exe_3(int);

    virtual void exe_4(int);

    virtual void exe_5(int);

    virtual void exe_6(int);

    virtual void exe_7(int);

    virtual void exe_8(int);

    virtual void exe_9(int);

    virtual void exe_10(int);

    virtual void exe_11(int);

    virtual void exe_12(int);

    virtual void exe_13(int);

    virtual void exe_14(int);

    virtual void exe_15(int);

    virtual void exe_16(int);

    virtual void exe_17(int);

    virtual void exe_18(int);

    virtual void exe_19(int);

};

#endif //_RUN_PROG_H_
