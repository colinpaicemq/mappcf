# mappcf
This C code maps from PCF numeric values back to character strings.
For example you can get data from PCF,  type:value
```
3070:b'M801                                     
1175:10 
3116:b'TAPE    ' 
3148:b'        ' 
1203:20 
```
which is not very helpful.
The mappcf code takes 1203,20 and returns
```
Sysp Alloc Unit : Alloc Blk 
```
The above values become
```
Response Q Mgr Name : b'M801' 
Sysp Type : Type Initial 
Sysp Archive Unit1 : b'TAPE' 
Sysp Archive Unit2 : b'' 
Sysp Alloc Unit : Alloc Blk 
```

The hard part of this mappcf function was to map PCF values such as MQIACF_SUB_TYPE
to its MQ provided formatting routines such as MQSUBTYPE_STR(), available in CMQSTRC.h

## Contents
- MQMAP.h contains the mapping from the PCF identifier to formatting function
- checkMap.c takes the MQMAP.h, checks the values are in ascending order, and outputs the data in a sortable format
- genmake to make checkMap.c 
- doPCFValues.h provides C functions to map the numberic values to their strings.

The function getPCFValue() in doPCFValues.h does the work.

## Using it from your C program

```
getPCFValue(MQLONG what, 
            MQLONG value, 
            char **pWhat, 
            char **pValue, 
            char **pPValue);
...
free(pWhat);
free(pValue);
free(pPValue);

```

- What - is the PCF value, such as MQIACF_SUB_TYPE
- value - is the value from the PCF request
- pWhat - is a pointer to a character representation of the "what" value.  For example "SUB_TYP" (the value "MQIACF_SUB_TYPE" with the prefix removed)
- pValue - is a pointer to the string representing the value. For example MQSYSP_ALLOC_BLK
- pPValue - is a pointer to the prettified with the prefix removed and the string made more usable.  MQ functions are used to format these strings, so the final string is *Alloc Blk*.

In the MQMAP list are two specials.
-  *MQMAP(10000,MQCFT_STR), // PCF special  10,000 used for looking up PCF Extended responses*.  This returns strings such as MQCFT_RESPONSE, and MQCFT_STRING 
-  *MQMAP(10001,MQCMD_STR), // PCF Special 10,001 for looking up PCF command.*   This returns strings such as MQCMD_INQUIRE_Q_MGR, and MQCMD_CLEAR_Q 

You need to free the returned strings after use.




