#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define maxN 90

struct citys{ // Structure holding the start and end points
    char node1;
    char node2;
};

struct  stack{  // Stack
    int sp;
    char node[maxN];
};

char Neighbour[255][255];
char pathString[255]; 
char longestWays[255][255];
void InterNode(char interN, struct stack *stck);
void findNeighbour();
void printNeighbour();
void pop(struct stack *stck);
void printLongestPaths();
void findLongestPaths();
void push(struct stack *stck, char node);
char otherNode(char targetNode, struct citys *lnkNode);
bool control(struct stack* stck, char sehir);
void initStk(stck)
struct stack *stck;
{
	int i;
    for (i = 0; i < maxN; i++)
        stck -> node[i] = ' ';
      stck -> sp = -1;
}
int entries = 30; // inputs
struct citys topo[30] = // MAPS
    {
        {'A', 'B'}, {'A', 'D'}, {'A', 'F'}, {'A', 'H'},
        {'B', 'C'}, {'B', 'R'}, {'B', 'J'}, {'B', 'I'},
		{'C', 'R'}, {'C', 'Q'}, {'C', 'D'}, 
        {'D', 'P'}, {'D', 'Q'}, {'D', 'E'},
        {'E', 'P'}, {'E', 'N'}, {'E', 'F'},
		{'F', 'N'}, {'F', 'M'}, {'F', 'G'},
        {'G', 'M'}, {'G', 'L'}, {'G', 'H'},
        {'H', 'L'}, {'H', 'K'}, {'H', 'I'},
        {'I', 'K'}, {'I', 'J'}
       
    };
char sourceNode = 'G' /* SourceNode */, destinationNode = 'M';/* Destination Node */
int reachTime; // WAYS

int main(){
	int sp;
    struct  stack stck;
    initStk(&stck);
	push(&stck, sourceNode);
    reachTime = 0; // Ways number 0
   	printf("All Roads Available :\n");
    InterNode(sourceNode, &stck); 
    if(reachTime ==0)
    printf("CITIES ARE NOT WRITTEN OR A WRONG SEARCH");
    printf("\nAll Ways Number = %d\n", reachTime); 
    printLongestPaths();
 	printf("Only three neighboring towns visit the city: \n");
	if(strlen(*Neighbour) == 0)
	printf("CITIES ARE NOT WRITTEN OR A WRONG SEARCH \n");
	printNeighbour();
	return 0; 
}
void push(struct stack *stck, char node) // Push 
{
    stck -> sp++; // Since it is -1, first increase and then add.
    stck -> node[stck -> sp] = node;   
}
bool control(struct stack* stck, char sehir){
    int i, stkN = stck -> sp;
    bool rtun = false;
    for (i = 0; i < stkN; i++){
        if (stck -> node[i] == sehir) {
            rtun = true;
            break;
        }
    }
    return rtun;
}
char otherNode(char targetNode, struct citys *lnkNode){
    return (lnkNode -> node1 == targetNode) ? lnkNode -> node2 : lnkNode -> node1; //Is it the first node that tries to reach?
}
void findLongestPaths(){ 
	if(strlen(pathString) > strlen(longestWays[0])){
		strcpy(longestWays[0],pathString);strcpy(longestWays[1],"");
	}else if(strlen(pathString) == strlen(longestWays[0])){
		int i = 0;for(; strlen(longestWays[i]); i++);
		strcpy(longestWays[i],pathString);strcpy(longestWays[i+1],"");
	}
}
void printLongestPaths(){  
	int i = 0,path = 1;
	printf("%c --> %c  \nLongest Ways:\n",sourceNode,destinationNode);
	for(; strlen(longestWays[i]); i++){
		int j;
		printf("Path:%d ",path++);
		for(j = 0; j < strlen(longestWays[i]) ; j++)printf("%c-->",longestWays[i][j]);
		printf("%c\n",longestWays[i][j]);
	}
}
void pop(struct stack *stck) // Pop 
{
	char node;
    int i, stkN = stck->sp;
	pathString[0] = '\0';
	printf("Path:%d ", reachTime+1);
    for (i = 0; i<=stkN; i++) {
        node = stck -> node[i];
		pathString[i] = node;
		if (i == 0){
            printf("%c", node);
    	}
        else if (i == stkN){
            printf("-->%c\n", node);
        }
        else{
			printf("-->%c", node);
	    }
    }
    pathString[i] = '\0'; 
    findNeighbour();
	findLongestPaths();
}
int ways=0;
void findNeighbour(){
	if(strlen(pathString) == 5){
	int city=0;
	for(city; city<5; city++){
		Neighbour[ways][city] = pathString[city];
	}
	ways++;
	}
}
void printNeighbour(){
		int city,ways,path = 1;
 	for(ways=0;ways<5;ways++){
	 for(city=0;city<5;city++){
 		if(Neighbour[ways][city] == 0)
 		break;
		printf("%c-->",Neighbour[ways][city]);
	 	if(city==4)
	 	printf("\n");
	 	}
	}
}
void InterNode(char interN, struct stack *stck) 
{
    char otherInterN;
    int i=0;
	int numInterN = 0;
    for (i = 0; i < entries; i++){
        if (topo[i].node1 != interN  && topo[i].node2 != interN){
			continue;
        }
        otherInterN = otherNode(interN, &topo[i]);
		numInterN++ ;
        if (otherInterN == stck -> node[stck -> sp-1]){
            continue;
        }      
        if (control(stck, otherInterN) == true){
            continue;
        }
        push(stck, otherInterN);
		if (otherInterN == destinationNode){
            pop(stck);
            reachTime++ ;
            stck -> sp-- ;
            continue;
        }
        else
            InterNode(otherInterN, stck);
    }
	 stck -> sp-- ;
}
