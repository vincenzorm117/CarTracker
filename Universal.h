#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/***********> #DEFINES <*****************/
#define kYear       5
#define kTiny       7
#define kSmall     256



/***********> STRUCTURE <*****************/
struct CarInfo{
    char make[kSmall];
    char model[kSmall];
    char year[kYear];
    char engine[kSmall];
    int carNumber;
    
    struct CarInfo *next;    
};


/***********> GLOBAL VARIABLES <*****************/
extern bool writeNothing;
extern struct CarInfo *gHead, *gTail; 
extern int gNumberOfCars;
extern char CarsFileLocation[BUFSIZ];


/***********> FUNCTION PROTOTYPES <*****************/
void Flush(void);
void ReplaceReturnAtEndOfString( char *theString );
void PrintCommands(void);
void AddStruct(struct CarInfo *currentPtr);
struct CarInfo *ReadStruct(void);
void ListCars(void);
char ReadStructFromFile(FILE *fp, struct CarInfo *infoPtr);
void ReadFile(void);
void UpdateFile(void);
void ErrorReport(const char *report);
void XPrint(const char *message);
void deleteAllStructs(void);
char AreYouSure( void );
void XPrintNoCarriageReturn(const char *message);
int GetInteger(void);
void NumberLinkedList(void);
void deleteStruct(const int carNum);
void EditCarInformation(int carNum);
void EnterDirectory(void);
void CaseNonSensitive(char *string);