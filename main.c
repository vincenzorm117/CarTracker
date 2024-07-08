
#include "Universal.h"


char CarsFileLocation[BUFSIZ]="/Users/";
bool writeNothing;
int gNumberOfCars;
struct CarInfo *gHead,*gTail;


int main (void)
{
    char command[kSmall];

    gHead=NULL;
    gTail=NULL;
    gNumberOfCars=0;
    
    EnterDirectory();
    ReadFile();
    
    
    do{
        writeNothing=false;
        if(0>=(printf("Enter Command(Try \"help\"// %d cars entered):",gNumberOfCars)))
            ErrorReport("MAIN: printf failed");
        if(NULL==(fgets(command, kSmall, stdin)))
            ErrorReport("MAIN: fgets failed");
        ReplaceReturnAtEndOfString(command);         
        CaseNonSensitive(command);
                
        if(strcmp(command, "help\0")==0)
            PrintCommands();
        if(strcmp(command, "list\0")==0)
            ListCars();
        if(strcmp(command, "new\0")==0)
            AddStruct(ReadStruct());
        if(strcmp(command, "delete\0")==0){
            if(gNumberOfCars){
                ListCars();
            XPrint("\nFORMAT: \"n\" n being the number after Car# of the car you wish to delete.");
            deleteStruct(GetInteger());
            }else{XPrint("\nNo car information has been entered\n");}
        }
        if(strcmp(command, "delall\0")==0){
            if(gNumberOfCars){
            if(AreYouSure())
                deleteAllStructs();
            }else{XPrint("\nNo car information has been entered\n");}
        }
        if(strcmp(command, "edit\0")==0){
            if(gNumberOfCars){
            ListCars();
            EditCarInformation(GetInteger());
            }else{XPrint("\nNo car information has been entered\n");}
        }


        
        

    }while(strcmp(command, "quit\0")!=0);
    
    UpdateFile();
    
    XPrintNoCarriageReturn("Goodbye...");
    
    return 0;
}





