
#include "Universal.h"


#define kDVDirecory     "/Users/punkarmy623/Desktop/cars.text"










/************************************************/




/* IMPLEMENT FILE OPEN/CLOSE operations that scan file for file location that being the username        */



/************************************************/



/************************************************/
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
/************************************************/
void ReadFile(void){
    FILE *fp;
    struct CarInfo *infoPtr;
    
    if(NULL==(fp = fopen(CarsFileLocation, "r")))
        return;
       
    do {
        if(NULL==(infoPtr=malloc(sizeof(struct CarInfo))))
            ErrorReport("ReadFile: Could not allocate CarInfo struct with malloc()");
        
        
    } while (ReadStructFromFile(fp, infoPtr));

    if(EOF==fclose(fp))
        ErrorReport("ReadFile: fclose failed");
    free(infoPtr);   
}
/************************************************/
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
/************************************************/
char ReadStructFromFile(FILE *fp, struct CarInfo *infoPtr){
    
    if ((fscanf(fp, "%[^\n]\n",infoPtr->make))!=EOF){
        if ((fscanf(fp, "%[^\n]\n",infoPtr->model))!=EOF){
            if ((fscanf(fp, "%[^\n]\n",infoPtr->year))!=EOF){
                if ((fscanf(fp, "%[^\n]\n",infoPtr->engine))==EOF){
                    return false;
                }else{AddStruct(infoPtr);return true;}
            }else{return false;}
        }else{return false;}
    }else{return false;}
}
/************************************************/
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
/************************************************/
void UpdateFile(void){
    FILE    *fp;
    struct CarInfo  *infoPtr;
   
    
    if(NULL==(fp=fopen(CarsFileLocation, "w")))
        ErrorReport("UpdateFile: Wrong Mac OS X username entered or file path nonexistent");
    
    if(writeNothing){}
    else{
    for(infoPtr=gHead;infoPtr!=NULL;infoPtr=infoPtr->next){
        if(0<(fprintf(fp, "%s\n",infoPtr->make))){
            if(0<(fprintf(fp, "%s\n",infoPtr->model))){
                if(0<(fprintf(fp, "%s\n",infoPtr->year))){
                    if(0<(fprintf(fp, "%s\n",infoPtr->engine))){
                    break;
                    }
                }else{break;}
            }else{break;}
        }else{break;}
                        
    }//For loop
  }//Else statement
    if(EOF==(fclose(fp)))
        ErrorReport("UpdateFile: fclose failed");
}
/************************************************/
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
/************************************************/
void EnterDirectory(void){
    
    
    char usrname[BUFSIZ];
    
    
    XPrint("Enter OS X Username [If incorrect all information entered will be lost]: ");
    XPrint("–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––");
    
    while(NULL==(fgets(usrname, BUFSIZ, stdin)))
        ;
    
    ReplaceReturnAtEndOfString(usrname);
    XPrint("–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––");
    
    strncat(CarsFileLocation, usrname, sizeof(usrname));
    strcat(CarsFileLocation, "/Desktop/Cars.text");
    

    

    if(0>(printf("FILE Location: %s\n",CarsFileLocation)))
        ErrorReport("EnterDirectory: printf failed");
    XPrint("–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––");
}
/************************************************/
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
/************************************************/