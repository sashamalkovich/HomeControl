#include "ser_res.h"

SerRes::SerRes()
{
    pInputString = new char[20];
    symbol = '~';
    input = '\0';
    array = new char *[20];
    intArray = new int[2];
    array[0] = "GET";
    array[1] = "PUT";
    array[2] = "QUT";
    array[3] = "TEST";
    array[4] = "TOST";
    array[5] = "TIST";
    array[6] = "GOT";
    array[7] = "POT";
    array[8] = "QYT";
    array[9] = "TUST";
    array[10] = "TAST";
    array[11] = "TYST";
    array[12] = "GUT";
    array[13] = "PET";
    array[14] = "QOT";
    array[15] = "TECT";
    array[16] = "TICT";
    array[17] = "TOCT";
    array[18] = "GED";
    array[19] = "PUD";

    intArray[0] = 0;
    intArray[1] = 0;

    timer = millis();

    for (int i = 0; i < 20; i++)
    {
        pInputString[i] = '\0';
    }
}

SerRes::~SerRes()
{
}

int *SerRes::response()
{

    int *s_res = respResult(array, intArray);
    //Serial.print("s_res -> ");
    // Serial.println(s_res);

    for (int i = 0; i < 20; i++)
    {
        pInputString[i] = '\0';
    }

    _SERIAL.flush();
    return s_res;
}

char *SerRes::response(char &symbol)
{
    return ser_res(pInputString, symbol);
}

char *SerRes::ser_res(char *inputString, char &symbol)
{
    static bool readSwitch;
    int i = 0;
    while (_SERIAL.available() > 0)
    {
        input = _SERIAL.read();

        if (input == symbol)
        {
            for (int i = 0; i < 20; i++)
            {
                inputString[i] = '\0';
            }
            readSwitch = true;
            continue;
        }
        else if (input == '\n')
        {
            readSwitch = false;
            break;
        }
        if (readSwitch)
        {
            inputString[i] = input;
        }
        i++;
    }

    return inputString;
}

bool SerRes::equals(const char *input1, const char *input2)
{
    bool sw;
    for (uint8_t i = 0; i < sizeof(input1) + 1; i++)
    {
        if (input1[i] == input2[i])
        {
        }
        else
        {
            return false;
        }
    }
    return true;
}

int SerRes::responseCommand(char **commandArray, char *inputString)
{
    for (uint8_t i = 0; i < sizeof(commandArray[i]); i++)
    {

        if (equals(commandArray[i], inputString))
        {
            return i;
        }
    }
    return -1;
}

int *SerRes::respResult(char **array, int *intArr)
{
    char symbols[11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int tempArray[10];
    int tt = 000;
    for (int i = 0; i < 10; i++)
        tempArray[i] = 0;
    char *temp = ser_res(pInputString, symbol);
    int count = 0;
    bool sWitch = false;
    for (int i = 0; i < 20; i++)
    {
        if (equals(array[i], temp))
        {
            intArr[0] = i;
            break;
        }
        else
        {
            intArr[0] = -1;
        }
    }
    for (int i = 0; i < 10; i++)
    {
        if (temp[i] == '(' && !sWitch)
        {
            sWitch = true;
        }
        else if (temp[i] == ')' && sWitch)
        {
            sWitch = false;
        }
        if (sWitch)
        {
            for (int y = 0; y < 10; y++)
            {
                if (temp[i] == symbols[y])
                {
                    tempArray[count] = int(temp[i] - 48);
                    count++;
                    break;
                }
            }
        }
    }
    if (!sWitch)
    {
        for (int i = 0; i < count; i++)
        {
            tt *= 10;
            tt += tempArray[i];
        }
        intArr[1] = tt;
    }

    /*
    Serial.print("intA -> ");
    Serial.print(intArr[0]);
    Serial.print(", ");
    Serial.print(intArr[1]);
    Serial.println(" ");
*/
    delay(20);
    return intArr;
}
