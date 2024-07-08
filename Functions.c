
#include "Universal.h"


#define FULL_YEAR   4
#define HALF_YEAR   2

extern int gNumberOfCars;
extern bool writeNothing;
/************************************************/
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
/************************************************/
void ListCars(void){
    struct CarInfo *listingPtr;
    
    if(NULL==gHead)
        XPrint("No car information has been entered");
    
    else{
    for(listingPtr=gHead;listingPtr!=NULL;listingPtr=listingPtr->next){
        if(0>(printf("––Car#%d–––––––––––\n",listingPtr->carNumber)))
            ErrorReport("ListCars: printf failed");
        if(0>(printf("Car maker: %s\n",listingPtr->make)))
            ErrorReport("ListCars: printf failed");
        if(0>(printf("Car model: %s\n",listingPtr->model)))
            ErrorReport("ListCars: printf failed");
        if(0>(printf("Year car produced: %s\n",listingPtr->year)))
            ErrorReport("ListCars: printf failed");
        if(0>(printf("Car engine: %s\n",listingPtr->engine)))
            ErrorReport("ListCars: printf failed");
        XPrint("–––––––––––––––––––");
        }//For loop
    }//Else statement
}
/************************************************/
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
/************************************************/
struct CarInfo *ReadStruct(void){
    struct CarInfo *dynamicPtr;
    char buffer[BUFSIZ];
    
    dynamicPtr = (struct CarInfo *)malloc(sizeof(struct CarInfo));
    if(NULL==dynamicPtr){
        printf("Error: memory allocation fail; out of memory\n");
        exit(0);
    }
    
    XPrint("–––––––––––––");
    
    XPrintNoCarriageReturn("Enter car maker: ");
    if(NULL==fgets(dynamicPtr->make, kSmall, stdin))
        ErrorReport("ReadStruct: fgets failed");
    ReplaceReturnAtEndOfString(dynamicPtr->make);
    
    XPrintNoCarriageReturn("Enter car model: ");
    if(NULL==(fgets(dynamicPtr->model, kSmall, stdin)))
        ErrorReport("ReadStruct: fgets failed");
    ReplaceReturnAtEndOfString(dynamicPtr->model);
    
  
    XPrintNoCarriageReturn("Enter year introduced: ");
    fflush(stdout);
    while(fgets(buffer, sizeof(buffer), stdin)!=NULL){
        size_t len = strlen(buffer);
        
        if (buffer[len - 1] == '\n')
            buffer[--len] = '\0';
        
        
        if(((len==HALF_YEAR)||(len==FULL_YEAR))&& ((strspn(buffer, "0123456789"))==len)){
            strcpy(dynamicPtr->year, buffer);
            break;
        }
           
        printf("Enter year introduced: ");
        fflush(stdout);
    }
    

    XPrintNoCarriageReturn("Enter car engine: ");
    if(NULL==(fgets(dynamicPtr->engine, kSmall, stdin)))
        ErrorReport("ReadStruct: fgets failed");
    ReplaceReturnAtEndOfString(dynamicPtr->engine);
    
    XPrint("–––––––––––––");
    
    
    
    return  dynamicPtr;
}
/************************************************/
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
/************************************************/
void AddStruct(struct CarInfo *currentPtr){

    gNumberOfCars++;
    
    currentPtr->carNumber=gNumberOfCars;
    
    if(NULL==gHead)
        gHead = currentPtr;
    else
        gTail->next = currentPtr;
        
        gTail = currentPtr;
        currentPtr->next = NULL;
}
/************************************************/
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
/************************************************/
void ErrorReport(const char *report){
    if(fprintf(stderr, "%s",report)<0)exit(0);
    exit(0);
}
/************************************************/
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
/************************************************/
void PrintCommands(void){
    XPrint("\nAvailable Commands");
    XPrint("–––––––––––––");
    XPrint("Type \"help\" to list available commands.");
    XPrint("Type \"list\" to list car entries.");
    XPrint("Type \"new\" to enter new car information.");
    XPrint("Type \"delete\" to delete specific car information.");
    XPrint("Type \"delAll\" to delete all information on all car entries.");
    XPrint("Type \"edit\" to edit specific car information.");
    XPrint("Type \"quit\" to quit the program.\n");    
}
/************************************************/
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
/************************************************/
void  deleteAllStructs(void){

    struct CarInfo *trackingPtr;
    
    while (gHead->next) {
        
        trackingPtr=gHead;
        if(trackingPtr->next==gTail){
            trackingPtr->next=NULL;
            free(gTail);
        }
        else{
            while (trackingPtr->next!=gTail) trackingPtr=trackingPtr->next;
            trackingPtr->next=NULL;
            free(gTail);
            gTail=trackingPtr; 
        }   
    }//END OF WHILE LOOP
    
    free(gHead);
    gHead=NULL;
    gTail=NULL;
    gNumberOfCars=0;
    
}
/************************************************/
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
/************************************************/
void Flush(void){
    while(getchar()!='\n')
        ;
}
/************************************************/
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
/************************************************/
void XPrint(const char *message){
    if(0>(printf("%s\n",message)))
        exit(0);
}
/************************************************/
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
/************************************************/
void XPrintNoCarriageReturn(const char *message){
    if(0>(printf("%s",message)))
        exit(0);
}
/************************************************/
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
/************************************************/
void deleteStruct(const int carNum){

    if(AreYouSure()==false)return;
    
    struct CarInfo *trackingPtr=gHead,*deletingPtr=gHead;
    
    if (0==gNumberOfCars) {return;}
    else if(1==gNumberOfCars){deleteAllStructs();}
    else if(carNum==gTail->carNumber){
        for(trackingPtr=gHead; trackingPtr->next!=gTail; trackingPtr=trackingPtr->next);
        trackingPtr->next=NULL;
        free(gTail);
        gTail=trackingPtr;
    }
    else{
        for(deletingPtr=gHead;carNum!=deletingPtr->carNumber;deletingPtr=deletingPtr->next);
        if(deletingPtr==gHead){
            deletingPtr=gHead->next;
            free(gHead);
            gHead=deletingPtr;
        }
        else{
        for (trackingPtr=gHead; trackingPtr->next!=deletingPtr; trackingPtr=trackingPtr->next);
            trackingPtr->next=deletingPtr->next;
            free(deletingPtr);
        }    
    }
    NumberLinkedList();
}
/************************************************/
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
/************************************************/
int GetInteger(void){
    int carNum;
    
    if(0==gNumberOfCars){
        XPrint("\nNo car information has been entered\n");
        return 0;
    }
    fflush(stdout);
    
    
    do {
        XPrintNoCarriageReturn("Enter Car Number: ");
        if(0>=(scanf("%d",&carNum)))
            ErrorReport("GetInteger: scanf failed");
        Flush();
    } while ((carNum<=0)||(gNumberOfCars<carNum));
    
    return carNum;
        
    
    
}
/************************************************/
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
/************************************************/
void NumberLinkedList(void){
    
    if(gHead==NULL)return;
    
    gNumberOfCars=0;
    struct CarInfo *numberingPtr;
    
        for(numberingPtr=gHead;numberingPtr!=NULL;numberingPtr=numberingPtr->next){
            gNumberOfCars++;
            numberingPtr->carNumber=gNumberOfCars;
        }
    
}
/************************************************/
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
/************************************************/
void EditCarInformation(int carNum){
    if(!carNum)return;
    
    char command[kSmall],buffer[BUFSIZ];
    struct CarInfo *editingPtr;
    bool allEntered=false;
    
    XPrint("–––––––––––––––––––––––––––––––––––––––––––––––––––––");
    XPrint("Which of the following fields would you like to edit?");
    XPrint("–––––––––––––––––––––––––––––––––––––––––––––––––––––");
    XPrint("\"make\"");
    XPrint("\"model\"");
    XPrint("\"year\"");
    XPrint("\"engine\"");
    XPrint("If you wish to edit all fields. Type \"all\"");
    XPrint("If you wish to cancel editing. Type \"cancel\"");
    XPrint("–––––––––––––––––––––––––––––––––––––––––––––––––––––");
    if(NULL==(fgets(command, kSmall, stdin)))
        ErrorReport("EditCarInformation: fgets failed");
    ReplaceReturnAtEndOfString(command);
    CaseNonSensitive(command);
    if(strcmp(command, "cancel\0")==0)return;
    if(strcmp(command, "all\0")==0)allEntered=true;
    
    for (editingPtr=gHead; carNum!=editingPtr->carNumber; editingPtr=editingPtr->next);

    
    if((strcmp(command, "make\0")==0)||(allEntered)){
        XPrint("––––––––––––––––––––––––––––––––––––");
        if(0>=(printf("Current car maker entered: %s\n",editingPtr->make)))
            ErrorReport("EditCarInformation: printf failed");
        XPrint("––––––––––––––––––––––––––––––––––––");
        XPrintNoCarriageReturn("Enter new car maker: ");
        if(NULL==(fgets(editingPtr->make, kSmall, stdin)))
            ErrorReport("EditCarInformation: fgets failed");
        ReplaceReturnAtEndOfString(editingPtr->make);
    }
    if((strcmp(command, "model\0")==0)||(allEntered)){
        XPrint("––––––––––––––––––––––––––––––––––––");
        if(0>=(printf("Current car model entered: %s\n",editingPtr->model)))
            ErrorReport("EditCarInformation: printf failed");
        XPrint("––––––––––––––––––––––––––––––––––––");
        XPrintNoCarriageReturn("Enter new car model: ");
        if(NULL==(fgets(editingPtr->model, kSmall, stdin)))
            ErrorReport("EditCarInformation: fgets failed");
        ReplaceReturnAtEndOfString(editingPtr->model);
    }
    if((strcmp(command, "year\0")==0)||(allEntered)){
        XPrint("––––––––––––––––––––––––––––––––––––");
        if(0>=(printf("Current car year entered: %s\n",editingPtr->year)))
            ErrorReport("EditCarInformation: printf failed");
        XPrint("––––––––––––––––––––––––––––––––––––");
        XPrintNoCarriageReturn("Enter new year: ");
        fflush(stdout);
        while(fgets(buffer, sizeof(buffer), stdin)!=NULL){
            size_t len = strlen(buffer);
            
            if (buffer[len - 1] == '\n')
                buffer[--len] = '\0';
            
            
            if(((len==HALF_YEAR)||(len==FULL_YEAR))&& ((strspn(buffer, "0123456789"))==len)){
                strcpy(editingPtr->year, buffer);
                break;
            }
            
            XPrintNoCarriageReturn("Enter year introduced: ");
            fflush(stdout);
        }
        
        
    }
    if((strcmp(command, "engine\0")==0)||(allEntered)){
        XPrint("––––––––––––––––––––––––––––––––––––");
        if(0>=(printf("Current car engine entered: %s\n",editingPtr->engine)))
            ErrorReport("EditCarInformation: printf failed");
        XPrint("––––––––––––––––––––––––––––––––––––");
        XPrintNoCarriageReturn("Enter new car engine: ");
        if(NULL==(fgets(editingPtr->engine, kSmall, stdin)))
            ErrorReport("EditCarInformation: fgets failed");
        ReplaceReturnAtEndOfString(editingPtr->engine);
    }
    
    
}
/************************************************/
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
/************************************************/
char AreYouSure( void ){
	char	command;
	
	do {
        XPrintNoCarriageReturn("Are you sure? [(yes=y)(no=n)]: ");
		if(0>=(scanf( "%c", &command )))
            ErrorReport("AreYouSure: scanf failed");
		Flush();
        command=tolower(command);
	}while ((command != 'n') && (command != 'y'));
    
    if('n'==command){writeNothing=false; return writeNothing;}
    else if('y'==command){writeNothing=true; return writeNothing;}
    else{ErrorReport("AreYouSure() failed");}
    
    return writeNothing;
}
/************************************************/
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
/************************************************/
void  ReplaceReturnAtEndOfString( char *theString ){
    theString[ strlen(theString) - 1] = '\0';
}
/************************************************/
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
/************************************************/
void CaseNonSensitive(char *string){
    int i;
    
    for (i=0; i<=(int)strlen(string); i++)
        string[i]=tolower(string[i]);
}
/************************************************/
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
/************************************************/